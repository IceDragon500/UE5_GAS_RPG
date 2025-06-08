// 我自己用来学习的试作品 -- 来自icedragon500


#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Aura/AuraLogChannels.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/PlayerInterface.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "PlayerController/AuraPlayerController.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();

	//这里直接将函数作为参数传入
	//调用函数指针
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength, GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Intelligence, GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Resilience, GetResilienceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Vigor, GetVigorAttribute);

	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Armor, GetArmorAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ArmorPenetration, GetArmorPenetrationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_BlockChance, GetBlockChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitChance, GetCriticalHitChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitDamage, GetCriticalHitDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitResistance, GetCriticalHitResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_HealthRegeneration, GetHealthRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ManaRegeneration, GetManaRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxMana, GetMaxManaAttribute);

	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Fire, GetFireResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Lightning, GetLightningResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Arcane, GetArcaneResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Physical, GetPhysicalResistanceAttribute);


	/*
	FAttributeSignature StrengthDelegate;
	StrengthDelegate.BindStatic(GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Strenght, StrengthDelegate);

	FAttributeSignature IntelligenceDelegate;
	IntelligenceDelegate.BindStatic(GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Intellingence, IntelligenceDelegate);
*/
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//REPNOTIFY_Always
	//Always Call the property's RepNotify function when it is received from the server
	//当从服务器接收到属性时，总是调用属性的RepNotify函数

	//REPNOTIFY_OnChanged
	//Only call the property's RepNotify function if it changes from the local value
	//只有当属性的本地值发生变化时，才调用属性的RepNotify函数

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, FireResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, LightningResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArcaneResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, PhysicalResistance, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& InData,
                                            FEffectProperties& OutProps) const
{
	OutProps.EffectContextHandle = InData.EffectSpec.GetContext();
	OutProps.SourceASC = OutProps.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(OutProps.SourceASC) && OutProps.SourceASC->AbilityActorInfo.IsValid() && OutProps.SourceASC->
		AbilityActorInfo->AvatarActor.IsValid())
	{
		OutProps.SourceAvatarActor = OutProps.SourceASC->AbilityActorInfo->AvatarActor.Get();
		OutProps.SourceController = OutProps.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (OutProps.SourceController == nullptr && OutProps.SourceAvatarActor != nullptr)
		{
			//如果上面Props.SourceController获取失败了，我们就把Props.SourceAvatarActor转成pawn再获取一次
			OutProps.SourceController = Cast<APawn>(OutProps.SourceAvatarActor)->GetController();
		}
		if (OutProps.SourceController)
		{
			OutProps.SourceCharacter = Cast<ACharacter>(OutProps.SourceController->GetPawn());
		}
	}
	if (InData.Target.AbilityActorInfo.IsValid() && InData.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		OutProps.TargetAvatarActor = InData.Target.AbilityActorInfo->AvatarActor.Get();
		OutProps.TargetController = InData.Target.AbilityActorInfo->PlayerController.Get();
		OutProps.TargetCharacter = Cast<ACharacter>(OutProps.TargetAvatarActor);
		OutProps.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OutProps.TargetAvatarActor);
	}
}

/**
 * 
 * @param FGameplayEffectModCallbackData是一个结构体
 * 里面包含了
 * const struct FGameplayEffectSpec&		EffectSpec;		// 修改器的规格The spec that the mod came from
 * struct FGameplayModifierEvaluatedData&	EvaluatedData;	// 将应用于目标的 “平面”/计算数据The 'flat'/computed data to be applied to the target
 * class UAbilitySystemComponent &Target;		// 我们打算应用的目标Target we intend to apply to
 *
 * 而在FGameplayModifierEvaluatedData中，包含了
 * FGameplayAttribute Attribute;/** 修改了什么属性What attribute was modified 
 */

void UAuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	/*
	 *从这里可以看出Data里面 或者是FGameplayEffectModCallbackData这个结构体里面
	 *包含了交互双方的很多信息，我们可以从里面取到我们需要用的数据
	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Max(GetHealth(), 0.f));
		//Data.EvaluatedData.Magnitude 这个可以显示每次变化了多少
	}
	*/
	FEffectProperties Props;

	SetEffectProperties(Data, Props);

	//死亡检测
	if (Props.TargetCharacter->Implements<UCombatInterface>() && ICombatInterface::Execute_IsDead(Props.TargetCharacter)) return;

	//这里做这个设置，是为了当补充了HP大于上限，而我们又处在被伤害的过程中，当伤害无法抵消掉补充时，界面上血量不会减少
	//相当于就是HP溢出了，伤害执行在了溢出的部分
	//但是我们想要的是，当我们HP到达最大HP的时候，一边补充HP一遍遭受伤害，也能及时的显示在界面上，以MaxHealth为准，而不是以一个溢出的值为准

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}

	//处理伤害
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		HandleInComingDamage(Props);
	}

	//得到了经验
	if (Data.EvaluatedData.Attribute == GetIncomingXPAttribute())
	{
		HandleIncomingXP(Props);
	}
}

void UAuraAttributeSet::HandleInComingDamage(const FEffectProperties Props)
{
	const float LocalIncomingDamage = GetIncomingDamage();
	SetIncomingDamage(0.f);
	if (LocalIncomingDamage > 0.f)
	{
		const float NewHealth = GetHealth() - LocalIncomingDamage;
		SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));

		const bool bFatal = NewHealth <= 0.f;//如果收到这次伤害死了
		if (bFatal)
		{//如果死了
			//死亡的时候 添加一个冲击力 让尸体看上去是被技能击飞的			
			if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor))
			{
				CombatInterface->Die(UAuraAbilitySystemLibrary::GetDamageImpulse(Props.EffectContextHandle));
			}
			//添加经验
			SendXPEvent(Props);
		}
		else//如果没死
		{
			FGameplayTagContainer TagsContainer;
			TagsContainer.AddTag(FAuraGameplayTags::Get().Effect_HitReact);
			Props.TargetASC->TryActivateAbilitiesByTag(TagsContainer);

			//收到了技能的伤害，然后添加一个冲击力，让受击的敌人后退一点点
			const FVector& KnockbackForce = UAuraAbilitySystemLibrary::GetKnockbackForce(Props.EffectContextHandle);
			if (!KnockbackForce.IsNearlyZero(1.f))
			{
				/**LaunchCharacter
				 * 为角色设置一个待处理的发射速度。该速度将在角色移动组件的下一次更新时被处理，
				 * 并将角色状态设置为"下落"状态。触发OnLaunched事件。
				 * @PARAM LaunchVelocity 要赋予该角色的速度
				 * @PARAM bXYOverride 若为true，将替换而非累加角色速度的XY部分
				 * @PARAM bZOverride 若为true，将替换而非累加角色速度的Z轴分量
				 */
				Props.TargetCharacter->LaunchCharacter(KnockbackForce, true, true);
			}
		}


		const bool bBlockHit = UAuraAbilitySystemLibrary::IsBlockHit(Props.EffectContextHandle);
		const bool bCriticalHit = UAuraAbilitySystemLibrary::IsCriticalHit(Props.EffectContextHandle);
		ShowFloatingText(Props, LocalIncomingDamage, bBlockHit, bCriticalHit);

		if (UAuraAbilitySystemLibrary::IsSuccessfulDebuff(Props.EffectContextHandle))
		{
			// Handle Debuff
			Debuff(Props);
		}
	}
}

void UAuraAttributeSet::HandleIncomingXP(FEffectProperties Props)
{
	const float LocalIncomingXP = GetIncomingXP();
	SetIncomingXP(0.f);
	UE_LOG(LogAura, Log, TEXT("得到了经验 %f"), LocalIncomingXP);


	if (Props.SourceCharacter && Props.SourceCharacter->Implements<UPlayerInterface>() && Props.SourceCharacter->
		Implements<UCombatInterface>())
	{
		const int32 CurrentLevel = ICombatInterface::Execute_GetPlayerLevel(Props.SourceCharacter);
		const int32 CurrentXP = IPlayerInterface::Execute_GetXP(Props.SourceCharacter);

		const int32 NewLevel = IPlayerInterface::Execute_FindLevelForXP(
			Props.SourceCharacter, CurrentXP + LocalIncomingXP);
		const int32 NumOfLevelUps = NewLevel - CurrentLevel;

		if (NumOfLevelUps > 0)
		{
			const int32 AttributePointReward = IPlayerInterface::Execute_GetAttributePointsReward(
				Props.SourceCharacter, CurrentLevel);
			const int32 SpellPointsReward = IPlayerInterface::Execute_GetSpellPointsReward(
				Props.SourceCharacter, CurrentLevel);

			IPlayerInterface::Execute_AddToPlayerLevel(Props.SourceCharacter, NumOfLevelUps);
			IPlayerInterface::Execute_AddToAttributePoints(Props.SourceCharacter, AttributePointReward);
			IPlayerInterface::Execute_AddToSpellPoints(Props.SourceCharacter, SpellPointsReward);

			bTopOffHealth = true;
			bTopOffMana = true;

			IPlayerInterface::Execute_LevelUp(Props.SourceCharacter);
		}

		IPlayerInterface::Execute_AddToXP(Props.SourceCharacter, LocalIncomingXP);
	}
}

void UAuraAttributeSet::Debuff(const FEffectProperties Props)
{
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	
	FGameplayEffectContextHandle EffectContext = Props.SourceASC->MakeEffectContext();
	EffectContext.AddSourceObject(Props.SourceAvatarActor);

	const FGameplayTag DamageType = UAuraAbilitySystemLibrary::GetDamageType(Props.EffectContextHandle);
	const float DebuffDamage = UAuraAbilitySystemLibrary::GetDebuffDamage(Props.EffectContextHandle);
	const float DebuffDuratioin = UAuraAbilitySystemLibrary::GetDebuffDuration(Props.EffectContextHandle);
	const float DebuffFrequency = UAuraAbilitySystemLibrary::GetDebuffFrequency(Props.EffectContextHandle);

	FString DebuffName = FString::Printf(TEXT("DynamicDebuff_%s"), *DamageType.ToString());
	UGameplayEffect* Effect = NewObject<UGameplayEffect>(GetTransientPackage(), FName(DebuffName));

	Effect->DurationPolicy = EGameplayEffectDurationType::HasDuration;//设置持续时间的类型，这里设置为有限的时间
	Effect->Period = DebuffFrequency;
	Effect->DurationMagnitude = FScalableFloat(DebuffDuratioin);

	//编译会提示InheritableOwnedTagsContainer已经弃用
	//Effect->InheritableOwnedTagsContainer.AddTag(GameplayTags.DamageTypesToDebuffs[DamageType]);

	//下面这个是上面这个逻辑符合5.4的写法
	FInheritedTagContainer TagContainer = FInheritedTagContainer();
	UTargetTagsGameplayEffectComponent& Component = Effect->FindOrAddComponent<UTargetTagsGameplayEffectComponent>();

	const FGameplayTag DebuffTag = GameplayTags.DamageTypesToDebuffs[DamageType];
	TagContainer.Added.AddTag(DebuffTag);

	if (DebuffTag.MatchesTagExact(GameplayTags.Debuff_Stun))
	{
		TagContainer.Added.AddTag(GameplayTags.Player_Block_InputHeld);
		TagContainer.Added.AddTag(GameplayTags.Player_Block_InputPressed);
		TagContainer.Added.AddTag(GameplayTags.Player_Block_InputReleased);
		TagContainer.Added.AddTag(GameplayTags.Player_Block_InputCursorTrace);
	}
	
	Component.SetAndApplyTargetTagChanges(TagContainer);

	Effect->StackingType = EGameplayEffectStackingType::AggregateBySource;
	Effect->StackLimitCount = 1;

	const int32 Index = Effect->Modifiers.Num();
	Effect->Modifiers.Add(FGameplayModifierInfo());
	FGameplayModifierInfo& ModifierInfo = Effect->Modifiers[Index];

	ModifierInfo.ModifierMagnitude = FScalableFloat(DebuffDamage);
	ModifierInfo.ModifierOp = EGameplayModOp::Additive;
	ModifierInfo.Attribute = UAuraAttributeSet::GetIncomingDamageAttribute();

	FGameplayEffectSpec* MutableSpec = new FGameplayEffectSpec(Effect, EffectContext, 1.f);
	if (MutableSpec)
	{
		FAuraGameplayEffectContext* AuraContext = static_cast<FAuraGameplayEffectContext*>(MutableSpec->GetContext().Get());
		TSharedPtr<FGameplayTag> DebuffDamageType = MakeShareable(new FGameplayTag(DamageType));
		AuraContext->SetDamageType(DebuffDamageType);
	}

	Props.TargetASC->ApplyGameplayEffectSpecToSelf(*MutableSpec);
}

void UAuraAttributeSet::SendXPEvent(const FEffectProperties& Props)
{
	if (Props.TargetCharacter->Implements<UCombatInterface>())
	{
		const int32 TargetLevel = ICombatInterface::Execute_GetPlayerLevel(Props.TargetCharacter);
		/**
		 * 注意，看下面
		 * 我们在通过接口获取角色类的时候 如果按照下面的方式获取，会报错
		 * const ECharacterClass TargetClass = CombatInterface->GetCharacterClass();
		 * 因为GetCharacterClass()方法是通过继承接口的类实现的，我们不能直接在接口类中调用
		 * 如果我们需要在接口类中使用，则需要使用Execute_的版本
		 * 如下：
		 */
		const ECharacterClass TargetClass = ICombatInterface::Execute_GetCharacterClass(Props.TargetCharacter);

		const int32 XPReward = UAuraAbilitySystemLibrary::GetXPRewardForClassAndLevel(
			Props.TargetCharacter, TargetClass, TargetLevel);

		const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
		FGameplayEventData Playload;
		Playload.EventTag = GameplayTags.Attributes_Meta_IncomingXP;
		Playload.EventMagnitude = XPReward;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Props.SourceCharacter,
		                                                         GameplayTags.Attributes_Meta_IncomingXP, Playload);
	}
}

void UAuraAttributeSet::ShowFloatingText(const FEffectProperties& Props, float Damage, bool bBlockHit,
                                         bool bCriticalHit)
{
	if (Props.SourceCharacter != Props.TargetCharacter)
	{
		if (AAuraPlayerController* PlayerController = Cast<AAuraPlayerController>(Props.SourceCharacter->Controller))
		{
			PlayerController->ShowDamageNumber(Damage, Props.TargetCharacter, bBlockHit, bCriticalHit);
			return;
		}
		if (AAuraPlayerController* PlayerController = Cast<AAuraPlayerController>(Props.TargetCharacter->Controller))
		{
			PlayerController->ShowDamageNumber(Damage, Props.TargetCharacter, bBlockHit, bCriticalHit);
		}
	}
}

void UAuraAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetMaxHealthAttribute() && bTopOffHealth)
	{
		SetHealth(GetMaxHealth());
		bTopOffHealth = false;
	}

	if (Attribute == GetMaxManaAttribute() && bTopOffMana)
	{
		SetMana(GetMaxHealth());
		bTopOffMana = false;
	}
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	//GAMEPLAYATTRIBUTE_REPNOTIFY的解释：
	//当你有一个属性需要在网络环境中同步（例如，在服务器和客户端之间同步角色的生命值），你通常会使用这个宏来自动处理属性变化的通知。
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}

void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldStrength);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldIntelligence);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resilience, OldResilience);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, OldVigor);
}

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Armor, OldArmor);
}

void UAuraAttributeSet::OnRep_ArmorPentration(const FGameplayAttributeData& OldArmorPentration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorPenetration, OldArmorPentration);
}

void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BlockChance, OldBlockChance);
}

void UAuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void UAuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UAuraAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}

void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void UAuraAttributeSet::OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, FireResistance, OldFireResistance);
}

void UAuraAttributeSet::OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, LightningResistance, OldLightningResistance);
}

void UAuraAttributeSet::OnRep_ArcaneResistance(const FGameplayAttributeData& OldArcaneResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArcaneResistance, OldArcaneResistance);
}

void UAuraAttributeSet::OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, PhysicalResistance, OldPhysicalResistance);
}