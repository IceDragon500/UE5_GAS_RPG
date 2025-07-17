// 我自己用来学习的试作品 -- 来自icedragon500


#include "AbilitySystem/Abilities/Offensive/ArcanShards.h"

FString UArcanShards::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);

	if (Level == 1)
	{
		return FString::Printf(TEXT(
			"<Title>Arcane Shards</>\n"
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			"<Default>Summon shards of arcane energy causing radial damage of</>"
			"<Damage>%d</><Default>Shards damage with a chance to 击飞</>\n\n"

		), Level, ManaCost, Cooldown, ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
			"<Title>Arcane Shards</>\n"
			"<Small>Level: </>""<Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			"<Default>Summon %d shards of arcane energy causing radial damage of</>"
			"<Damage>%d</><Default> "
			"Shards damage with a chance to 击飞</>\n"
		), Level, ManaCost, Cooldown, FMath::Min(Level, MaxNumShards), ScaledDamage);
	}
}

FString UArcanShards::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);

	return FString::Printf(TEXT(
		"<Title>NEXT LEVEL:</>\n"
		"<Small>Level: </>""<Level>%d</>\n"
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
		"<Default>Summon %d shards of arcane energy causing radial damage of</>"
		"<Damage>%d</><Default> "
		"Shards damage with a chance to 击飞</>\n"
	), Level, ManaCost, Cooldown, FMath::Min(Level, MaxNumShards), ScaledDamage);
}
