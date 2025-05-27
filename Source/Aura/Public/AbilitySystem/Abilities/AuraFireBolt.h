// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "AuraFireBolt.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraFireBolt : public UAuraProjectileSpell
{
	GENERATED_BODY()

public:
	//获取当前技能描述
	virtual FString GetDescription(int32 Level) override;
	//获取下一级的技能描述
	virtual FString GetNextLevelDescription(int32 Level) override;

	/**
	 * 生成发射物/生成发射的火球
	 * @param ProjectileTargetLocation 目标的位置
	 * @param SocketTag 起点的位置
	 * @param bOverridePitch 是否覆盖抛射物（Projectile）的俯仰角（Pitch）
	 * @param PitchOverride 抛射物的俯仰角
	 * @param HomingTarget 追踪的目标
	 */
	UFUNCTION(BlueprintCallable)
	void SpwanProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride, AActor* HomingTarget);
	
protected:

	//多个抛射物在水平上最大的夹角
	UPROPERTY(EditDefaultsOnly, Category = "FireBolt")
	float ProjectileSpread = 90.f;

	//最大抛射物数量
	UPROPERTY(EditDefaultsOnly, Category = "FireBolt")
	int32 NumProjectiles = 5;
	
private:
	
};
