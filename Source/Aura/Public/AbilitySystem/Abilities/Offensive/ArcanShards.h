﻿// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "ArcanShards.generated.h"

/**
 * ArcanShards 奥术岩石
 * 用来处理技能描述 还有岩石的数量
 */
UCLASS()
class AURA_API UArcanShards : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()

public:
	//获取当前技能描述
	virtual FString GetDescription(int32 Level) override;
	//获取下一级的技能描述
	virtual FString GetNextLevelDescription(int32 Level) override;

	//产生最大的岩石数量
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxNumShards = 11;

protected:

private:
};
