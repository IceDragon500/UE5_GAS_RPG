// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AbilityInfo.generated.h"

class UGameplayAbility;

USTRUCT(BlueprintType)
struct FAuraAbilityInfo
{
	GENERATED_BODY()

	//Ability技能Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta =(DisplayName = "Ability技能Tag"))
	FGameplayTag AbilityTag = FGameplayTag();

	//技能对应的按键Tag
	UPROPERTY(BlueprintReadOnly, meta =(DisplayName = "技能对应的按键Tag"))
	FGameplayTag InputTag= FGameplayTag();

	//技能初始状态Tag
	UPROPERTY(BlueprintReadOnly, meta =(DisplayName = "技能初始状态Tag"))
	FGameplayTag StatusTag= FGameplayTag();

	//技能的冷却Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta =(DisplayName = "技能的冷却Tag"))
	FGameplayTag CooldownTag= FGameplayTag();

	//技能类型Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta =(DisplayName = "技能类型Tag"))
	FGameplayTag AbilityType= FGameplayTag();

	//技能的图标
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta =(DisplayName = "技能的图标"))
	TObjectPtr<const UTexture2D> Icon = nullptr;

	//技能的背景图
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta =(DisplayName = "技能的背景图"))
	TObjectPtr<UMaterialInterface> BackgroundMaterial = nullptr;

	//技能的等级要求
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta =(DisplayName = "技能的等级要求"))
	int32 LevelRequirement = 1;

	//技能类
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta =(DisplayName = "技能类GA"))
	TSubclassOf<UGameplayAbility> Ability;
	
};



/**
 * 
 */
UCLASS()
class AURA_API UAbilityInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	TArray<FAuraAbilityInfo> AbilityInformation;

 	
	FAuraAbilityInfo FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound = false) const;
};
