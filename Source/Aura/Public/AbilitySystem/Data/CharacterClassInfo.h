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

	//设置角色的主要属性 力量 智力 活力 体力
	UPROPERTY(EditDefaultsOnly, Category = "角色主要属性")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;

	//设置角色一进入游戏，默认的攻击能力
	UPROPERTY(EditDefaultsOnly, Category = "角色主要属性")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "角色主要属性")
	FScalableFloat XPReward = FScalableFloat();
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
	UPROPERTY(EditDefaultsOnly, Category = "角色属性打包")
	TMap<ECharacterClass, FCharacterClassDefaultInfo> CharacterClassInfoMap;

	//用来从存档中读取主要属性，应用于Aura
	UPROPERTY(EditDefaultsOnly, Category = "公共属性")
	TSubclassOf<UGameplayEffect> PrimaryAttributes_SetByCaller;

	//所有Enemy类型都共用一套公共属性
	UPROPERTY(EditDefaultsOnly, Category = "公共属性")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	//用来从存档中读取次要属性，应用于Aura
	UPROPERTY(EditDefaultsOnly, Category = "公共属性")
	TSubclassOf<UGameplayEffect> SecondaryAttributes_Infinite;

	//所有Enemy类型都共用一套公共属性
	UPROPERTY(EditDefaultsOnly, Category = "公共属性")
	TSubclassOf<UGameplayEffect> VitalAttributes;

	FCharacterClassDefaultInfo GetCLassDefaultInfo(ECharacterClass CharacterClass);

	//这里保存Enemy中的命中特效之类的东西，让每个角色都拥有相同的一套逻辑，使用GameplayEffect来触发
	UPROPERTY(EditDefaultsOnly, Category = "公共属性")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;

	//设置计算公式里面的一些系数，让其与等级挂钩
	UPROPERTY(EditDefaultsOnly, Category = "公共属性")
	TObjectPtr<UCurveTable> DamageCalculationCoefficients;
	
protected:
private:
};
