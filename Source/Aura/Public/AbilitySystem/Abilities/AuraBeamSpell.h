// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AuraBeamSpell.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraBeamSpell : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	//用来获取鼠标点击命中的结果
	void StoreMouseDataInfo(const FHitResult& HitResult);

	//用来获取所有者的Character变量
	UFUNCTION(BlueprintCallable)
	void StoreOwnerVariables();

	/**
	 * 检查从武器到鼠标点击之间是否有Enemy存在
	 * @param BeamTargetLocation 鼠标点击的坐标
	 */
	UFUNCTION(BlueprintCallable)
	void TraceFirstTarget(const FVector& BeamTargetLocation);

	UFUNCTION(BlueprintCallable)
	void StoreAdditionalTargets(TArray<AActor*>& OutAdditionalTargets);

	UFUNCTION(BlueprintImplementableEvent)
	void PrimaryTargetDied(AActor* DeadActor);

	UFUNCTION(BlueprintImplementableEvent)
	void AdditionalTargetDied(AActor* DeadActor);
	
protected:

	//鼠标点击的坐标
	UPROPERTY(BlueprintReadWrite)
	FVector MouseHitLocation;

	//鼠标点击的Actor
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AActor> MouseHitActor;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APlayerController> OwnerPlayerController;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ACharacter> OwnerCharacter;

	//电击目标周围的检测范围
	UPROPERTY(EditDefaultsOnly)
	float MaxShockRadius = 200.f;
	
	//同时可以被电击的敌人数量
	UPROPERTY(EditDefaultsOnly)
	int32 MaxNumShockTargets = 5;
private:
	
};
