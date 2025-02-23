// 我自己用来学习的试作品 -- 来自icedragon500


#include "AuraAssetManager.h"

#include "AuraGameplayTags.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine)
	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FAuraGameplayTags::InitializeNativeGameplayTags();
}
