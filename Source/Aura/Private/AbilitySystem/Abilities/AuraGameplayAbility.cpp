// 我自己用来学习的试作品 -- 来自icedragon500


#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

#include "AbilitySystem/AuraAttributeSet.h"

FString UAuraGameplayAbility::GetDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>%s,</><Level>%d</>"), L"默认Default Ability Name 默认Default Ability Name 默认Default Ability Name 默认Default Ability Name 默认Default Ability Name 默认Default Ability Name 默认Default Ability Name 默认Default Ability Name 默认Default Ability Name", Level);
}

FString UAuraGameplayAbility::GetNextLevelDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>%s,</><Level>%d</>"), L"下一个等级的信息NextLevel Ability Name 下一个等级的信息NextLevel Ability Name 下一个等级的信息NextLevel Ability Name 下一个等级的信息NextLevel Ability Name 下一个等级的信息NextLevel Ability Name 下一个等级的信息NextLevel Ability Name 下一个等级的信息NextLevel Ability Name 下一个等级的信息NextLevel Ability Name", Level);
}


FString UAuraGameplayAbility::GetLockedDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>Spell Locked Until Level:</><Level>%d</>"), Level);
}

float UAuraGameplayAbility::GetManaCost(int32 InLevel) const
{
	float ManaCost = 0.0f;
	if (const UGameplayEffect* CostEffect = GetCostGameplayEffect())
	{
		for (auto Mod : CostEffect->Modifiers)
		{
			if (Mod.Attribute == UAuraAttributeSet::GetManaAttribute())
			{
				Mod.ModifierMagnitude.GetStaticMagnitudeIfPossible(InLevel, ManaCost);
				break;
			}
		}
	}
	return ManaCost;
}

float UAuraGameplayAbility::GetCooldown(int32 InLevel) const
{
	float Cooldown = 0.0f;
	if (const UGameplayEffect* CooldownEffect = GetCooldownGameplayEffect())
	{
		CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(InLevel, Cooldown);
		
	}
	return Cooldown;
}
