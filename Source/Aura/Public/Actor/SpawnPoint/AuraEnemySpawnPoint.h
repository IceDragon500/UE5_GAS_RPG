// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Engine/TargetPoint.h"
#include "AuraEnemySpawnPoint.generated.h"

enum class ECharacterClass : uint8;
class AAuraEnemy;
/**
 * 设计 在指定的点位生成指定的敌人
 */
UCLASS()
class AURA_API AAuraEnemySpawnPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	
	/**
	 * 在指定的位置生成敌人
	 */
	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

	//需要生成的敌人蓝图类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="属性设置")
	TSubclassOf<AAuraEnemy>  EnemyClass;

	//需要生成敌人的数量
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="属性设置")
	int32 EnemyLevel {1};

	//默认生成敌人的类型：战士、射手、巫师
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="属性设置")
	ECharacterClass CharacterClass {ECharacterClass::Warrior};

protected:


private:

};
