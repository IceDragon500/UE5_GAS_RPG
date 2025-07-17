// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "AuraPassiveAbility.h"
#include "HaloOfProtection.generated.h"

/**
 * 保护光环
 * 用来处理技能描述
 */
UCLASS()
class AURA_API UHaloOfProtection : public UAuraPassiveAbility
{
	GENERATED_BODY()

public:
	//获取当前技能描述
	virtual FString GetDescription(int32 Level) override;
	//获取下一级的技能描述
	virtual FString GetNextLevelDescription(int32 Level) override;
};
