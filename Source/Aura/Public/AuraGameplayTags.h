// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * AuraGameplayTags
 *
 * Singleton containing native Gameplay Tags
 * 包含原生玩法标签的单例
 */
struct FAuraGameplayTags
{
public:
 static const FAuraGameplayTags& Get() { return GameplayTags; }
 
 //初始化GameplayTags
 //创建原生的GameplayTags
 static void InitializeNativeGameplayTags();
 
protected:
 
private:
 static FAuraGameplayTags GameplayTags;
 
};
