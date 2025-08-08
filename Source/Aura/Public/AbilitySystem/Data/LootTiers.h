// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LootTiers.generated.h"

USTRUCT(BlueprintType)
struct FLootItem
{
	GENERATED_BODY()

	//需要生成的蓝图类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "属性设置|Spawing")
	TSubclassOf<AActor> LootClass;

	//生成的概率
	UPROPERTY(EditAnywhere, Category = "属性设置|Spawing")
	float ChanceToSpawn = 0.f;

	//生成的最大数量
	UPROPERTY(EditAnywhere, Category = "属性设置|Spawing")
	int32 MaxNumberToSpawn = 1;

	//是否覆盖掉落道具本生的等级值
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "属性设置|Spawing")
	bool bLootLevelOverride = true;
	
};


/**
 * 
 */
UCLASS()
class AURA_API ULootTiers : public UDataAsset
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	TArray<FLootItem> GetLootItems();
	
	UPROPERTY(EditDefaultsOnly, Category = "属性设置|Spawing")
	TArray<FLootItem> LootItems;
};
