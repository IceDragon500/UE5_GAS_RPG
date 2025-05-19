// 我自己用来学习的试作品 -- 来自icedragon500


#include "AbilitySystem/Abilities/AuraFireBolt.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			"<Title>FIRE BOLT</>\n"
			"<Small>Level:</><Level>%d</>\n"
			"<Small>ManaCost:</><ManaCost>%.1f</>\n"
			"<Small>Cooldown :</><Cooldown>%.1f</>\n\n"
			"<Default>Launched a bolt of fire, exploding on impact and dealing</>"
			"<Damage>%d</><Default> fire damage with a chance to burn</>\n\n"

		), Level, ManaCost, Cooldown, ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
			"<Title>FIRE BOLT</>\n"
			"<Small>Level:</>""<Level>%d</>\n"
			"<Small>ManaCost:</><ManaCost>%.1f</>\n"
			"<Small>Cooldown :</><Cooldown>%.1f</>\n\n"
			"<Default>Launched %d bolt of fire, exploding on impact and dealing</>"
			"<Damage>%d</><Default> "
			"fire damage with a chance to burn</>\n"
		), Level, ManaCost, Cooldown, FMath::Min(Level, MaxNumProjectiles), ScaledDamage);
	}
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	
	return FString::Printf(TEXT(
			"<Title>NEXT LEVEL:</>\n"
			"<Small>Level:</>""<Level>%d</>\n"
			"<Small>ManaCost:</><ManaCost>%.1f</>\n"
			"<Small>Cooldown :</><Cooldown>%.1f</>\n\n"
			"<Default>Launched %d bolt of fire, exploding on impact and dealing</>"
			"<Damage>%d</><Default> "
			"fire damage with a chance to burn</>\n"
		), Level, ManaCost, Cooldown, FMath::Min(Level, MaxNumProjectiles), ScaledDamage);
}
