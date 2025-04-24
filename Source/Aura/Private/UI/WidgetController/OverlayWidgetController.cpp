// 我自己用来学习的试作品 -- 来自icedragon500


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "PlayerState/AuraPlayerState.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	OnHealthChanged.Broadcast(GetAuraAttributeSet()->GetHealth());
	OnMaxHealthChanged.Broadcast(GetAuraAttributeSet()->GetMaxHealth());
	OnManaChanged.Broadcast(GetAuraAttributeSet()->GetMana());
	OnMaxManaChanged.Broadcast(GetAuraAttributeSet()->GetMaxMana());

	//GetGameplayAttributeValueChangeDelegate 注册属性值何时更改
	
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	GetAuraPS()->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);
	AuraPlayerState->OnLevelChangedDelegate.AddLambda([this](int32 NewLevel)
	{
		OnPlayerLevelChangedDelegate.Broadcast(NewLevel);
	});

	//GetGameplayAttributeValueChangeDelegate : 注册属性值何时更改
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAttributeSet()->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAttributeSet()->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAttributeSet()->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAttributeSet()->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		});

	if (GetAuraASC())
	{
		if (GetAuraASC()->bStartupAbilitiesGiven)
		{
			BroadcastAbilityInfo();
		}
		else
		{
			GetAuraASC()->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::BroadcastAbilityInfo);
		}
		

		
		GetAuraASC()->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (auto Tag: AssetTags)
			{
				/*
				 * 我们这里需要做一个检查，检查传入的Tag是否都是Message下面的消息
				 */
				
				/*
				 * 例如 我们让Tag = Message.HealthPotion
				 * "Message.HealthPotion".MatchesTag("Message") 就会返回ture
				 * "Message".MatchesTag("Message.HealthPotion") 就会返回false
				 * 检查前者是否在后者的包含中
				 * 如果两者都不在一个前后包含中，那肯定是false
				 * 如果两者都在一个层级前后，后面级别比前面高，那就是true，低 就是false
				 * 
				 * 上面的例子中， Message包含了HealthPotioin，Message是HealthPotioin的上级
				 * 所以检查Message.HealthPotion是否在Message中，是在的
				 * 反之，检查Message是否在Message.HealthPotion中，是不在的
				 */

				//RequestGameplayTag : 获取与 TagName 对应的 FGameplayTag 如果未找到，则返回空值
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if(Tag.MatchesTag(MessageTag))
				{
					FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					if(Row != nullptr) MessageWidgetRowDelegate.Broadcast(*Row);
				}
				
			}
		});
	}
}
 
void UOverlayWidgetController::OnXPChanged(int32 NewXP)
{
	ULevelUpInfo* LevelUpInfo = GetAuraPS()->LevelUpInfo;
	checkf(LevelUpInfo, TEXT("找不到LevelUpInfo的信息"));


	int32 Level = LevelUpInfo->FindLevelForXp(NewXP);
	int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num();

	if (Level <= MaxLevel && Level > 0)
	{
		//当前等级需要的经验值
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInformation[Level].LevelUpRequirement;
		//达到上一等级需要的经验值
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInformation[Level - 1].LevelUpRequirement;

		const int32 DeletaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;

		const int32 XPForThisLevel = NewXP - PreviousLevelUpRequirement;

		/**
		 * 注意 这里涉及到一个类型转换
		 * 因为如果先计算整数除以整数，如果结果小于1，比如0.xxx，会得到结果直接为0
		 * 所以我们需要先将两个整数转成浮点，再进行除法计算
		 * 错误的写法：
		 * static_cast<float>(XPForThisLevel / DeletaLevelRequirement);
		 */
		const float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeletaLevelRequirement);

		OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
	}
}
