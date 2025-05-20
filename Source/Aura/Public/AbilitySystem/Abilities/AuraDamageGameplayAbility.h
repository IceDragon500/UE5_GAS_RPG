#pragma once

#include "AuraAbilityTypes.h"
#include "AuraGameplayAbility.h"
#include "Interaction/CombatInterface.h"
#include "AuraDamageGameplayAbility.generated.h"

UCLASS()
class AURA_API UAuraDamageGameplayAbility: public UAuraGameplayAbility
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);
	
	FDamageEffectParams MakeDamageEffectParamsFromClassDefault(AActor* TargetActor = nullptr) const;
	
protected:
	
	//设置对目标造成效果的GameEffect
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "属性设置|发射物属性设置")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	//303讲中被移除
	//UPROPERTY(EditDefaultsOnly, Category="属性设置|DamageType")
	//TMap<FGameplayTag, FScalableFloat> DamageTypes;

	UPROPERTY(EditDefaultsOnly, Category="属性设置|DamageType")
	FGameplayTag DamageType;

	UPROPERTY(EditDefaultsOnly, Category="属性设置|DamageType")
	FScalableFloat Damage;

	//Debuff概率
	UPROPERTY(EditDefaultsOnly, Category="属性设置|DamageType")
	float DebuffChance = 20;

	//Debuff伤害
	UPROPERTY(EditDefaultsOnly, Category="属性设置|DamageType")
	float DebuffDamage = 5.f;

	//Debuff伤害间隔时间
	UPROPERTY(EditDefaultsOnly, Category="属性设置|DamageType")
	float DebuffFrequency = 1.f;

	//Debuff持续时间
	UPROPERTY(EditDefaultsOnly, Category="属性设置|DamageType")
	float DebuffDuration = 5.f;

	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const;

	//303讲中被移除
	//float GetDamageByDamageType(float InLevel, const FGameplayTag& DamageType);
	
private:
	
};
