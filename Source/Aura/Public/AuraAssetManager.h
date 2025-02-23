// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:

	static UAuraAssetManager& Get();
protected:

	//开始初始加载，从initializeobjectrereferences中调用
	//在开始的时候初始化GameplayTags相关的内容
	virtual void StartInitialLoading() override;

	
private:
};
