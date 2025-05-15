// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayTags.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSpellGlobeSelectedSignature, bool, bSpendPointsButtonEnabled, bool, bEqupiButtonEnabled, FString, DescriptionString, FString, NextLevelDescriptionString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitForEquipSelectionSignature, const FGameplayTag&, AbilityType);

/**
 * 被选中的技能
 * Ability : 表示能力Tag本身
 * Status : 表示当前能力的状态Tag
 */
struct FSelectedAbility
{
	FGameplayTag Ability = FGameplayTag();//表示能力Tag本身
	FGameplayTag Status = FGameplayTag();//表示当前能力的状态Tag
	
};
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API USpellMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:

	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerStatChangedSignature SpellPointsChanged;//广播技能点数

	UPROPERTY(BlueprintAssignable)
	FSpellGlobeSelectedSignature SpellGlobeSelectedDelegate;

	UPROPERTY(BlueprintAssignable)
	FWaitForEquipSelectionSignature WaitForEquipDelegate;

	UPROPERTY(BlueprintAssignable)
	FWaitForEquipSelectionSignature StopWaitForEquipDelegate;

	//选中技能框
	UFUNCTION(BlueprintCallable)
	void SpellGlobeSelected(const FGameplayTag& AbilityTag);

	//按下技能点数按钮
	UFUNCTION(BlueprintCallable)
	void SpendPointButtonPressed();

	//取消选中技能框
	UFUNCTION(BlueprintCallable)
	void GlobeDeselect();

	//按下装备技能按钮
	UFUNCTION(BlueprintCallable)
	void EquipButtonPressed();

	UFUNCTION(BlueprintCallable)
	void SpellRowGlobePressed(const FGameplayTag& SlotTag, const FGameplayTag& AbilityType);

	void OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& InputTagSlot, const FGameplayTag& PreviousSlot);
	
protected:
	
private:
	
	static void ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints, bool& bShouldEnableSpellPointsButton, bool& bShouldEnableEquipButton);
	
	FSelectedAbility SelectedAbility = {FAuraGameplayTags::Get().Abilities_None, FAuraGameplayTags::Get().Abilities_Status_Locked};
	
	int32 CurrentSpellPoints = 0;

	bool bWaitingForEquipSelection = false;
	
	FGameplayTag SelectedSlot;
};