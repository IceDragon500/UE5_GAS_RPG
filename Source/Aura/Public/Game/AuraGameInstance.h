// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AuraGameInstance.generated.h"

/**
 * 游戏运行的实例
 * 我们用来保存玩家
 */
UCLASS()
class AURA_API UAuraGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FName PlayerStartTag = FName("");

	UPROPERTY()
	FString LoadSlotName = FString("");

	UPROPERTY()
	int32 LoadSlotIndex = 0;

protected:


private:

	
};
