// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /* AssetTags*/);
DECLARE_MULTICAST_DELEGATE(FAbilitiesGiven)
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FAbilityStatusChanged, const FGameplayTag& /* AbilityTags*/, const FGameplayTag& /* StatusTags*/);

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

	FAbilityStatusChanged AbilityStatusChanged;

	// 添加角色能力
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InAbilities);

	// 添加角色被动效果
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InPassiveAbilities);
	
	// 标记是否已经赋予了初始能力
	bool bStartupAbilitiesGiven = false;

	// 处理能力输入标签按住事件
	void AbilityInputTagHeld(const FGameplayTag& InputTag);

	// 处理能力输入标签释放事件
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	// 遍历每个能力并执行委托
	void ForEachAbility(const FForEachAbility& Delegate);

	// 从能力规格中获取能力标签
	FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);

	// 从能力规格中获取输入标签
	FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);

	//从能力规格中获取当前状态信息Status
	static FGameplayTag GetStatusFromSpec(const FGameplayAbilitySpec& AbilitySpec);

	//检查是否可以从指定的AbilityTag来查询是否有Spec
	FGameplayAbilitySpec* GetSpecFromAbilityTag(const FGameplayTag& AbilityTag);

	void UpgradeAttribute(const FGameplayTag& AttributeTag);

	UFUNCTION(Server, Reliable)
	void ServerUpgradeAttribute(const FGameplayTag& AttributeTag);

	void UpdateAbilityStatuses(int32 Level);
	
protected:

	virtual void OnRep_ActivateAbilities() override;

	// 客户端效果应用函数
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

	UFUNCTION(Client, Reliable)
	void ClientupdateAbilityStatus(const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag);
private:
	
};