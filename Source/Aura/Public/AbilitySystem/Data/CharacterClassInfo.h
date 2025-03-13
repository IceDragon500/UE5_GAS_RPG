// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

//确定Enemy的类型
UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Elementalist,
	Warrior,
	Ranger
};

//将主要属性打包成一个结构体
USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Class Default")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;
	
};



/**
 * 
 */
UCLASS()
class AURA_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()
public:

	//将Enemy的类型 和 主要属性 打包成一个Map进行管理，这样可以一一对应
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TMap<ECharacterClass, FCharacterClassDefaultInfo> CharacterClassInfoMap;

	//所有Enemy类型都共用一套公共属性
	UPROPERTY(EditDefaultsOnly, Category = "公共属性")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	//所有Enemy类型都共用一套公共属性
	UPROPERTY(EditDefaultsOnly, Category = "公共属性")
	TSubclassOf<UGameplayEffect> VitalAttributes;

	FCharacterClassDefaultInfo GetCLassDefaultInfo(ECharacterClass CharacterClass);

	//这里保存Enemy中的命中特效之类的东西，让每个角色都拥有相同的一套逻辑，使用GameplayEffect来触发
	UPROPERTY(EditDefaultsOnly, Category = "公共属性")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilites;

	//设置计算公式里面的一些系数，让其与等级挂钩
	UPROPERTY(EditDefaultsOnly, Category = "公共属性")
	TObjectPtr<UCurveTable> DamageCalculationCoefficients;
	
protected:
private:
};
