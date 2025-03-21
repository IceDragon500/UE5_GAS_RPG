// 我自己用来学习的试作品 -- 来自icedragon500


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	//Super::BroadcastInitialValues();

	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());

	//GetGameplayAttributeValueChangeDelegate 注册属性值何时更改
	
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
		[this, AuraAttributeSet](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this, AuraAttributeSet](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		});

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
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
		}
		);
}