// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "AuraDamageGameplayAbility.h"
#include "Actor/AuraProjectile.h"
#include "AuraProjectileSpell.generated.h"

/**
 * 设计了一个射弹技能
 * 类似火球术，发射一个火球
 */
UCLASS()
class AURA_API UAuraProjectileSpell : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()
	
public:
	
protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	//将设置的发射物蓝图生成
	UFUNCTION(BlueprintCallable, Category= "属性设置|发射物属性设置")
	void SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag);

	//设置需要抛出的对象，是一个BP蓝图
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "属性设置|发射物属性设置")
	TSubclassOf<AAuraProjectile> ProjectileClass;
	
private:

	
};
