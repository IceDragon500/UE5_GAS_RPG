// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "AuraPassiveAbility.h"
#include "LifeSiphon.generated.h"

/**
 * 生命虹吸
 * 用来梳理技能描述
 */
UCLASS()
class AURA_API ULifeSiphon : public UAuraPassiveAbility
{
	GENERATED_BODY()
	
public:
	//获取当前技能描述
	virtual FString GetDescription(int32 Level) override;
	//获取下一级的技能描述
	virtual FString GetNextLevelDescription(int32 Level) override;
};
