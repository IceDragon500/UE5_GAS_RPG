// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /* AssetTags*/);
DECLARE_MULTICAST_DELEGATE(FAbilitiesGiven)
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FAbilityStatusChanged, const FGameplayTag& /* AbilityTags*/, const FGameplayTag& /* StatusTags*/,  int32 /* Level*/);
DECLARE_MULTICAST_DELEGATE_FourParams(FAbilityEquipped, const FGameplayTag& /*AbilityTag*/, const FGameplayTag&/* Status*/, const FGameplayTag& /* InputTagSlot*/, const FGameplayTag& /*PreviousSlot*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FDeactivatePassiveAbility, const FGameplayTag&/*AbilityTag*/);

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	// 设置能力角色信息
	void AbilityActorInfoSet();

	// 效果资产标签的多播委托
	FEffectAssetTags EffectAssetTags;

	// 能力赋予的多播委托
	FAbilitiesGiven AbilitiesGivenDelegate;

	//能力状态的多播
	FAbilityStatusChanged AbilityStatusChanged;

	FAbilityEquipped AbilityEquipped;

	FDeactivatePassiveAbility DeactivatePassiveAbility;

//-----角色初始化-------------------------
	// 添加角色能力
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InAbilities);

	// 添加角色被动效果
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InPassiveAbilities);
	
	// 标记是否已经赋予了初始能力
	bool bStartupAbilitiesGiven = false;
	
//-----按键相关-------------------------
	//处理能力输入标签按下事件
	void AbilityInputTagPressed(const FGameplayTag& InputTag);

	// 处理能力输入标签按住事件
	void AbilityInputTagHeld(const FGameplayTag& InputTag);

	// 处理能力输入标签释放事件
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	// 遍历每个能力并执行委托
	void ForEachAbility(const FForEachAbility& Delegate);


//-----从Spec中获取需要的信息-------------------------
	// 从能力规格中获取能力标签
	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);

	// 从能力规格中获取输入标签
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);

	//从能力规格中获取当前状态信息Status
	static FGameplayTag GetStatusFromSpec(const FGameplayAbilitySpec& AbilitySpec);

	//从AbilityTag中获取AbilityStatus
	FGameplayTag GetStatusFromAbilityTag(const FGameplayTag& AbilityTag);

	//从AbilityTag中获取InputTag
	FGameplayTag GetSlotFromAbilityTag(const FGameplayTag& AbilityTag);

	//检查当前这个技能槽是否是空的
	bool SlotIsEmpty(const FGameplayTag& Slot);

	//检查传入的技能AbilitySpec，是否有对应的按键槽位Slot
	static bool AbilityHasSlot(const FGameplayAbilitySpec& AbilitySpec, const FGameplayTag& Slot);
	
	static bool AbilityHasAnySlot(const FGameplayAbilitySpec& AbilitySpec);

	//通过按键槽位的Tag来获得对应按键技能的Spec
	FGameplayAbilitySpec* GetSpecWithSlot(const FGameplayTag& Slot);

	//判断技能是否是被动技能
	bool IsPassiveAbility(const FGameplayAbilitySpec& AbilitySpec) const;

	/**
	 * 给AbilitySpec分配一个按键槽位Slot
	 * @param AbilitySpec 需要分配的Spec
	 * @param Slot 需要指定到的按键槽位
	 */
	static void AssignSlotToAbility(FGameplayAbilitySpec& AbilitySpec, const FGameplayTag& Slot);
	
//-----从Spec中获取需要的信息-------------------------
	//检查是否可以从指定的AbilityTag来查询是否有Spec
	FGameplayAbilitySpec* GetSpecFromAbilityTag(const FGameplayTag& AbilityTag);

	//更新属性点
	void UpgradeAttribute(const FGameplayTag& AttributeTag);

	//服务器端 更新属性点
	UFUNCTION(Server, Reliable)
	void ServerUpgradeAttribute(const FGameplayTag& AttributeTag);

	/**
	 * 更新Ability的状态
	 * 更新当Ability不满足等级、满足等级未升级，满足等级已升级3种状态
	 * 这3中状态改变技能在界面上图标的样式
	 */
	void UpdateAbilityStatuses(int32 Level);

	UFUNCTION(Server, Reliable)
	void ServerSpendSpellPoint(const FGameplayTag& AbilityTag);

	UFUNCTION(Server, Reliable)
	void ServerEquipAbility(const FGameplayTag& AbilityTag, const FGameplayTag& InputTagSlot);

	UFUNCTION(Client, Reliable)
	void ClientEquipAbility(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& InputTagSlot, const FGameplayTag& PreviousSlot);
	
	bool GetDescriptionsByAbilityTag(const FGameplayTag& AbilityTag, FString& OutDescription, FString& OutNextLevelDescription);

	//移除一个指定的FGameplayAbilitySpec上面的InputTag
	static void ClearSlot(FGameplayAbilitySpec* Spec);

	//具有指定InputTag的Slot（技能槽）如果有，就把他清除
	//当前指定按键上对应如果有技能，则把这个技能清除掉
	void ClearAbilitiesOfSlot(const FGameplayTag& Slot);

	static bool AbilityHasSlot(FGameplayAbilitySpec* Spec, const FGameplayTag& Slot);
	
protected:

	virtual void OnRep_ActivateAbilities() override;

	// 客户端效果应用函数
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

	UFUNCTION(Client, Reliable)
	void ClientupdateAbilityStatus(const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, int32 AbilityLevel);
private:
	
};