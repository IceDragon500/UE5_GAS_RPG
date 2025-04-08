// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayAbility.h"
#include "AuraSummonAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraSummonAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations();

	UFUNCTION(BlueprintPure, Category="Summoning")
	TSubclassOf<APawn> GetRandomMinionClass();
	
	//会生成的小怪数量
	UPROPERTY(EditAnywhere, Category="Summoning")
	int32 NumMinions = 5;

	//需要生成的小怪Pawn类
	UPROPERTY(EditDefaultsOnly, Category="Summoning")
	TArray<TSubclassOf<APawn>> MinionClasses;

	//生成小怪距离角色最近的距离
	UPROPERTY(EditDefaultsOnly, Category="Summoning")
	float MinSpawnDistance = 50.f;

	//生成小怪距离角色最远的距离
	UPROPERTY(EditDefaultsOnly, Category="Summoning")
	float MaxSpawnDistance = 250.f;

	//生成怪物的角度，生成在角色正前方XX度
	//计算的时候，取得角色向前的向量，然后/2 得到正前方的开始的方向向量
	UPROPERTY(EditDefaultsOnly, Category="Summoning")
	float SpawnSpread = 90;


protected:
	
private:
	
};
