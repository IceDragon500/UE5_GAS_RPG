// 我自己用来学习的试作品 -- 来自icedragon500


#include "AbilitySystem/Abilities/Electrocute.h"

FString UElectrocute::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);

	if (Level == 1)
	{
		return FString::Printf(TEXT(
			"<Title>ELECTROCUTE</>\n"
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			"<Default>connecting with the target, repeatedly causing</>"
			"<Damage>%d</><Default> lightning damage with a chance to stun</>\n\n"

		), Level, ManaCost, Cooldown, ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
			"<Title>ELECTROCUTE</>\n"
			"<Small>Level: </>""<Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			"<Default>Emits a beam of lightning , propagating to %d additional targets nearby</>"
			"<Damage>%d</><Default> "
			"lightning damage with a chance to stun</>\n"
		), Level, ManaCost, Cooldown, FMath::Min(Level, MaxNumShockTargets), ScaledDamage);
	}
}

FString UElectrocute::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);

	return FString::Printf(TEXT(
		"<Title>NEXT LEVEL:</>\n"
		"<Small>Level: </>""<Level>%d</>\n"
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
		"<Default>Emits a beam of lightning , propagating to %d additional targets nearby</>"
		"<Damage>%d</><Default> "
		"lightning damage with a chance to stun</>\n"
	), Level, ManaCost, Cooldown, FMath::Min(Level, MaxNumShockTargets), ScaledDamage);
}
