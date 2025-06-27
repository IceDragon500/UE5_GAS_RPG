// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "AuraAbilityTypes.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "NiagaraSystem.h"
#include "AuraProjectile.generated.h"


class UProjectileMovementComponent;

UCLASS()
class AURA_API AAuraProjectile : public AActor
{
	GENERATED_BODY()

public:
	AAuraProjectile();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))//ExposeOnSpawn:指定属性是否应该暴露在类类型的Spawn Actor上
	FDamageEffectParams DamageEffectParams;
	//FGameplayEffectSpecHandle DamageEffectSpecHandle;

	UPROPERTY()
	TObjectPtr<USceneComponent> HomingTargetSceneComponent;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnHit();
	
	virtual void Destroyed() override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	//生命周期
	UPROPERTY(EditDefaultsOnly, Category= "命中设置", meta = (DisplayName = "生命周期"))
	float LifeSpan = 15.f;
    
    bool bHit = false;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	//击中特效
	UPROPERTY(EditAnywhere, Category= "命中设置", meta = (DisplayName = "击中特效"))
	TObjectPtr<UNiagaraSystem> ImpactEffect;
	
	//击中特效
	UPROPERTY(EditAnywhere, Category= "命中设置", meta = (DisplayName = "击中音效"))
	TObjectPtr<USoundBase> ImpactSound;

	//飞行音效
	UPROPERTY(EditAnywhere, Category= "命中设置", meta = (DisplayName = "飞行音效"))
	TObjectPtr<USoundBase> LoopingSound;

	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponent;

	
	
};
