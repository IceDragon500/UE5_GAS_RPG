// 我自己用来学习的试作品 -- 来自icedragon500


#include "Game/LoadScreenSaveGame.h"

FSavedMap ULoadScreenSaveGame::GetSavedMapWithMapName(const FString& InMapName)
{
	for (FSavedMap Map : SavedMaps)
	{
		if (Map.MapAssetName == InMapName)
		{
			return Map;
		}
	}

	return FSavedMap();
}

bool ULoadScreenSaveGame::HasMap(const FString& InMapName)
{
	for (FSavedMap Map : SavedMaps)
	{
		if (Map.MapAssetName == InMapName)
		{
			return true;
		}
	}
	return false;
}
