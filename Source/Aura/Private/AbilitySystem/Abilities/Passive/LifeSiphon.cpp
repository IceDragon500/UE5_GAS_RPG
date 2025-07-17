// 我自己用来学习的试作品 -- 来自icedragon500


#include "AbilitySystem/Abilities/Passive/LifeSiphon.h"

FString ULifeSiphon::GetDescription(int32 Level)
{
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			"<Title>LifeSiphon</>\n"
			"<Small>Level: </><Level>%d</>\n"
			"<Default>Summon shards of arcane energy causing radial damage of</>\n\n"

		), Level);
	}
	else
	{
		return FString::Printf(TEXT(
			"<Title>LifeSiphon</>\n"
			"<Small>Level: </>""<Level>%d</>\n"
			"<Default>Summon shards of arcane energy causing radial damage of</>"
		), Level);
	}
}

FString ULifeSiphon::GetNextLevelDescription(int32 Level)
{
	return FString::Printf(TEXT(
		"<Title>NEXT LEVEL:</>\n"
		"<Small>Level: </>""<Level>%d</>\n"
		"<Default>Summon  shards of arcane energy causing radial damage of</>"
	), Level);
}
