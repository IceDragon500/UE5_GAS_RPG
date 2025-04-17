// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//将获得的经验添加给PlayerState中的Level值
	UFUNCTION(BlueprintNativeEvent)
	void AddToXP(int32 InXP);

	//处理角色升级时的一些逻辑，比如播放特效，增加属性点之类的逻辑
	UFUNCTION(BlueprintNativeEvent)
	void LevelUp();
};
