// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HighlightInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)//添加BlueprintType，这样可以在蓝图中使用，从而不需要在C++上进行操作
class UHighlightInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IHighlightInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	void HighlightActor();

	UFUNCTION(BlueprintNativeEvent)
	void UnHighlightActor();
};
