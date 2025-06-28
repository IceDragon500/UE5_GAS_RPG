// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "Actor/AuraProjectile.h"
#include "AuraFireBall.generated.h"

UCLASS()
class AURA_API AAuraFireBall : public AAuraProjectile
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void StarOutgoingTimeline();

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AActor> ReturnActor;

	//用来处理火球爆炸的伤害
	UPROPERTY(blueprintReadWrite)
	FDamageEffectParams ExplosionDamageParams;

protected:

	virtual void BeginPlay() override;

	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	//在蓝图上调用，用来清空IgnoreList里面的Actor 这一段来自于368课下面的评论
	UFUNCTION(BlueprintCallable)
	void EmptyIgnoreList();

	virtual void OnHit() override;

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> IgnoreList;

	

private:
	
};
