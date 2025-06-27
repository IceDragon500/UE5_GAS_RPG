// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AuraFireBlast.generated.h"

class AAuraFireBall;
/**
 * 
 */
UCLASS()
class AURA_API UAuraFireBlast : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()
public:
	
	//获取当前技能描述
	virtual FString GetDescription(int32 Level) override;
	//获取下一级的技能描述
	virtual FString GetNextLevelDescription(int32 Level) override;

	UFUNCTION(BlueprintCallable)
	TArray<AAuraFireBall*> SpawnFireBalls();
	
protected:

	//最大火球数量
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxNumFireBalls = 12;
	
	
private:

	//最大火球数量
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAuraFireBall> FireBallClass;
	
};
