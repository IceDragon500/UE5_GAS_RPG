// 我自己用来学习的试作品 -- 来自icedragon500


#include "AbilitySystem/Abilities/Passive/ManaSiphon.h"

FString UManaSiphon::GetDescription(int32 Level)
{
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			"<Title>ManaSiphon</>\n"
			"<Small>Level: </><Level>%d</>\n"
			"<Default>Summon shards of arcane energy causing radial damage of</>\n\n"

		), Level);
	}
	else
	{
		return FString::Printf(TEXT(
			"<Title>ManaSiphon</>\n"
			"<Small>Level: </>""<Level>%d</>\n"
			"<Default>Summon shards of arcane energy causing radial damage of</>"
		), Level);
	}
}

FString UManaSiphon::GetNextLevelDescription(int32 Level)
{
	return FString::Printf(TEXT(
		"<Title>NEXT LEVEL:</>\n"
		"<Small>Level: </>""<Level>%d</>\n"
		"<Default>Summon  shards of arcane energy causing radial damage of</>"
	), Level);
}
