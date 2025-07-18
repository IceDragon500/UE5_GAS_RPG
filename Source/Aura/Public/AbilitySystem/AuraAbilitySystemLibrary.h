// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "AuraAbilityTypes.h"
#include "Data/CharacterClassInfo.h"
#include "Game/LoadScreenSaveGame.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraAbilitySystemLibrary.generated.h"

class AAuraHUD;
class USpellMenuWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * 通过传入目标Object，来获得Widget相关参数 和 HUD控制
	 * @param WorldContextObject 
	 * @param OutWCParams 
	 * @param OutAuraHUD 
	 * @return 
	 */
	UFUNCTION(BlueprintPure, Category = "角色控制|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static bool MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWCParams, AAuraHUD*& OutAuraHUD);
	
	/**
	 * 通过传入的Actor，来获得OverlayWidgetController
	 * @param WorldContextObject 
	 * @return 
	 */
	UFUNCTION(BlueprintPure, Category = "角色控制|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	/**
	 * 传入对应的角色Actor 获得AttributeMenuWidgetController，就是获得属性面板的控制
	 * @param WorldContextObject 传入对应的角色Actor
	 * @return 
	 */
	UFUNCTION(BlueprintPure, Category = "角色控制|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	/**
	 * 传入对应的角色Actor 获得SpellMenuWidgetController，就是获得技能面板的控制
	 * @param WorldContextObject 
	 * @return 
	 */
	UFUNCTION(BlueprintPure, Category = "角色控制|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static USpellMenuWidgetController* GetSpellMenuWidgetController(const UObject* WorldContextObject);

	/**
	 * 通过传入角色的Actor、角色职业信息、等级、ASC
	 * 来创建角色对应的3个属性表
	 * @param WorldContextObject 传入角色Actor
	 * @param CharacterClass 传入角色的职业信息
	 * @param Level 角色登记
	 * @param ASC 角色的AbilitySystemComponent
	 */
	UFUNCTION(BlueprintCallable, Category = "角色控制|CharacterClassInfo")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);

	/**
	 * 通过读取存档中的内容来初始化属性Attribute
	 * @param WorldContextObject 传入角色Actor
	 * @param ASC 角色的AbilitySystemComponent
	 * @param SaveGame 包含角色属性信息的存档
	 */
	UFUNCTION(BlueprintCallable, Category = "角色控制|CharacterClassInfo")
	static void InitializeDefaultAttributesFromSaveData(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ULoadScreenSaveGame* SaveGame);

	/**
	 * 给角色赋予初始的Ability 
	 * @param WorldContextObject 
	 * @param ASC 
	 * @param CharacterClass 
	 */
	UFUNCTION(BlueprintCallable, Category = "角色控制|CharacterClassInfo")
	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass);

	/**
	 * 获取存储在GameMode中的CharacterClassInfo结构体
	 * @param WorldContextObject 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category = "角色控制|CharacterClassInfo")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	/**
	 * 获取存储在GameMode中的AbilityInfo
	 * @param WorldContextObject 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category = "角色控制|CharacterClassInfo")
	static UAbilityInfo* GetAbilityInfo(const UObject* WorldContextObject);

//---------effect context getters-----------------------------------
	
	/**
	 * 传入一个GameplayEffectContextHandle  来检查伤害是否需要计算BlockHit
	 * @param EffectContextHandle 
	 * @return 
	 */
	UFUNCTION(BlueprintPure, Category = "角色控制|GameplayEffects")
	static  bool IsBlockHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "角色控制|GameplayEffects")
	static  bool IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "角色控制|GameplayEffects")
	static  float GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "角色控制|GameplayEffects")
	static  float GetDebuffDuration(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "角色控制|GameplayEffects")
	static  float GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "角色控制|GameplayEffects")
	static  FGameplayTag GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "角色控制|GameplayEffects")
	static  FVector GetDamageImpulse(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "角色控制|GameplayEffects")
	static  FVector GetKnockbackForce(const FGameplayEffectContextHandle& EffectContextHandle);

	/**
	 * 传入一个GameplayEffectContextHandle  来检查伤害是否需要计算CriticalHit
	 * @param EffectContextHandle 
	 * @return 
	 */
	UFUNCTION(BlueprintPure, Category = "角色控制|GameplayEffects")
	static  bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "角色控制|GameplayEffects")
	static bool IsRaidalDamage(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "角色控制|GameplayEffects")
	static float GetRadialDamageInnerRadius(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "角色控制|GameplayEffects")
	static float GetRadialDamageOuterRadius(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "角色控制|GameplayEffects")
	static FVector GetRadialDamageOrigin(const FGameplayEffectContextHandle& EffectContextHandle);

//-----------effect context setters---------------------------------
	/**
	 * 传入FGameplayEffectContextHandle  来设置这个伤害是否需要计算BlockHit
	 * @param EffectContextHandle 
	 * @param IsInBlockHit 
	 */
	UFUNCTION(BlueprintCallable, Category = "角色控制|GameplayEffects")
	static void SetIsBlockHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool IsInBlockHit);

	/**
	 * 传入FGameplayEffectContextHandle  来设置这个伤害是否需要计算CriticalHit
	 * @param EffectContextHandle 
	 * @param IsInCriticalHit 
	 */
	UFUNCTION(BlueprintCallable, Category = "角色控制|GameplayEffects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool IsInCriticalHit);

	UFUNCTION(BlueprintCallable, Category = "角色控制|GameplayEffects")
	static void SetIsSuccessfulDebuff(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool IsSuccessfulDebuff);

	UFUNCTION(BlueprintCallable, Category = "角色控制|GameplayEffects")
	static void SetDebuffDamage(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDamageDebuff);

	UFUNCTION(BlueprintCallable, Category = "角色控制|GameplayEffects")
	static void SetDebuffDuration(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDebuffDuration);

	UFUNCTION(BlueprintCallable, Category = "角色控制|GameplayEffects")
	static void SetDebuffFrequency(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDebuffFrequency);

	UFUNCTION(BlueprintCallable, Category = "角色控制|GameplayEffects")
	static void SetDebuffDamageType(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FGameplayTag& InDamageType);

	UFUNCTION(BlueprintCallable, Category = "角色控制|GameplayEffects")
	static void SetDeathImpulse(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InImpulse);

	UFUNCTION(BlueprintCallable, Category = "角色控制|GameplayEffects")
	static void SetKnockbackForce(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InForce);

	UFUNCTION(BlueprintCallable, Category = "角色控制|GameplayEffects")
	static void SetIsRadialDamage(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsRadialDamage);

	UFUNCTION(BlueprintCallable, Category = "角色控制|GameplayEffects")
	static void SetRadialDamageInnerRadius(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InInnerRadius);

	UFUNCTION(BlueprintCallable, Category = "角色控制|GameplayEffects")
	static void SetRadialDamageOuterRadius(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InOuterRadius);

	UFUNCTION(BlueprintCallable, Category = "角色控制|GameplayEffects")
	static void SetRadialDamageOrigin(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InOrigin);

//-----------Gameplay Mechanics 游戏机制算法---------------------------------
	/**
	 * 尝试在一个指定点的球形范围内，获取到指定的Actor
	 * 用来作为武器上的攻击检测，从武器端点，设置一个球形，获取在这个球体中是否存在指定的Actor
	 * @param WorldContextObject  传入当前的角色
	 * @param OutOverlappingActors  传入一个Actor数组，将找到的Actor存储在这个数组中
	 * @param ActorToIgnore 传入一个应该被忽略的Actor
	 * @param Radius 球的半径大小
	 * @param SphereOrigin 球中心的位置 
	 */
	UFUNCTION(BlueprintCallable, Category = "角色控制|GameplayEffects")
	static void GetLivePlayersWithRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorToIgnore, float Radius, const FVector& SphereOrigin);

	/**
	 * 寻找离得最近的Actor
	 * @param MaxTargets 需要找到指定Actor最大的数量
	 * @param Actors 传入一个找到指定Actor的数组
	 * @param OutClosestTargets 剔除掉Actors中不需要的部分，作为OutClosestTargets结果传出
	 */
	UFUNCTION(BlueprintCallable, Category = "角色控制|GameplayEffects")
	static void GetClosestTargets(int32 MaxTargets, const TArray<AActor*>& Actors, TArray<AActor*>& OutClosestTargets, const FVector& Origin);

	/**
	 * 比较两个Actor是否为同一组 或者叫同一阵营
	 * @param FirstActor 
	 * @param SecondActor 
	 * @return 
	 */
	UFUNCTION(BlueprintPure, Category = "角色控制|GameplayEffects")
	static bool IsNotFriend(AActor* FirstActor, AActor* SecondActor);

	/**
	 * 创建一个伤害性的 Gameplay Effect (GE) 并应用到目标角色，同时支持物理效果（击退/死亡冲力）和减益效果（Debuff）的参数化配置。
	 * @param DamageEffectParams 被传入的Effect参数，参数来自一个自定义的结构体FDamageEffectParams
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|DamageEffect")
	static FGameplayEffectContextHandle ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|DamageEffect")
	static TArray<FRotator> EvenlySpacedRotators(const FVector& Forward, const FVector& Axis, float Spread, int32 NumRotators);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|DamageEffect")
	static TArray<FVector> EvenlyRotatedVectors(const FVector& Forward, const FVector& Axis, float Spread, int32 NumVectors);
	
	/**
	 * ECharacterClass中获取对应等级的经验（针对怪物）
	 * @param WorldContextObject 
	 * @param CharacterClass 传入怪物对应的ECharacterClass ，获取里面的FScalableFloat 曲线上的经验值
	 * @param CharacterLevel 传入怪物的等级
	 * @return 
	 */
	static int32 GetXPRewardForClassAndLevel(const UObject* WorldContextObject, ECharacterClass CharacterClass, int32 CharacterLevel);

	/**
	 * 设置DamageEffectParams参数集中，关于范围伤害的相关内容
	 * @param DamageEffectParams 传入需要设置的参数集
	 * @param bIsRadial 是否范围伤害
	 * @param InnerRadius 内径大小
	 * @param OuterRadius 外径大小
	 * @param Origin 中心坐标
	 */
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|DamageEffect")
	static void SetIsRadialDamageEffectParam(UPARAM(ref) FDamageEffectParams& DamageEffectParams, bool bIsRadial, float InnerRadius, float OuterRadius, FVector Origin);

	/**
	 * 设置DamageEffectParams参数集中，关于受击方向和力度相关内容
	 * @param DamageEffectParams 传入需要设置的参数集
	 * @param KnockbackDirection 需要飞出去的方向
	 * @param Magnitude 受击的力度，如果为0，则使用参数集中对应的力度
	 */
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|DamageEffect")
	static void SetKnockbackDirection(UPARAM(ref) FDamageEffectParams& DamageEffectParams,FVector KnockbackDirection, float Magnitude = 0.f);

	/**
	 * 设置DamageEffectParams参数集中，关于死亡击飞方向和力度相关内容
	 * @param DamageEffectParams 传入需要设置的参数集
	 * @param ImpulseDirection 需要飞出去的方向
	 * @param Magnitude 受击的力度，如果为0，则使用参数集中对应的力度
	 */
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|DamageEffect")
	static void SetDeathImpulseDirection(UPARAM(ref) FDamageEffectParams& DamageEffectParams,FVector ImpulseDirection, float Magnitude = 0.f);

	/**
	 * 设置DamageEffectParams参数集中，关于Target的AbilitySystemComponent
	 * @param DamageEffectParams 传入需要设置的参数集
	 * @param InASC 需要设置的AbilitySystemComponent
	 */
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|DamageEffect")
	static void SetTargetEffectParamASC(UPARAM(ref) FDamageEffectParams& DamageEffectParams,UAbilitySystemComponent* InASC);
	
protected:
private:
};
