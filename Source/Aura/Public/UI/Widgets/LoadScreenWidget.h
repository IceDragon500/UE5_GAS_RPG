﻿// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API ULoadScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	/**
	 * 在蓝图中实现这个方法，使用蓝图初始化控件，也可以在C++中调用这个方法
	 * 构建屏幕视图模型
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BlueprintInitializeWidget();

protected:
	

private:

	
};
