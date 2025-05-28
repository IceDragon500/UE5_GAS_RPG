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

	//用来获取所有者的PlayerController
	UFUNCTION(BlueprintCallable)
	void StoreOwnerPlayerController();
protected:

	UPROPERTY(BlueprintReadWrite)
	FVector MouseHitLocation;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AActor> MouseHitActor;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APlayerController> OwnerPlayerController;
private:
	
};
