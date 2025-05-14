#pragma once

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
	
protected:
	
	//设置对目标造成效果的GameEffect
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "属性设置|发射物属性设置")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	
	UPROPERTY(EditDefaultsOnly, Category="属性设置|DamageType")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;

	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const;

	float GetDamageByDamageType(float InLevel, const FGameplayTag& DamageType);
	
private:
	
};
