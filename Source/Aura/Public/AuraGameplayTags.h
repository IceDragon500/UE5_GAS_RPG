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
 FGameplayTag Attributes_Primary_Strength;
 FGameplayTag Attributes_Primary_Intelligence;
 FGameplayTag Attributes_Primary_Resilience;
 FGameplayTag Attributes_Primary_Vigor; 
 
 FGameplayTag Attributes_Secondary_Armor;//护甲
 FGameplayTag Attributes_Secondary_ArmorPenetration;//护甲穿透
 FGameplayTag Attributes_Secondary_BlockChance;//格挡几率
 FGameplayTag Attributes_Secondary_CriticalHitChance;//致命一击
 FGameplayTag Attributes_Secondary_CriticalHitDamage;//重击伤害
 FGameplayTag Attributes_Secondary_CriticalHitResistance;//暴击抗性
 FGameplayTag Attributes_Secondary_HealthRegeneration;//生命恢复
 FGameplayTag Attributes_Secondary_ManaRegeneration;//法力恢复
 FGameplayTag Attributes_Secondary_MaxHealth;//最大生命值
 FGameplayTag Attributes_Secondary_MaxMana;//最大法力值

 FGameplayTag InputTag_LMB;
 FGameplayTag InputTag_RMB;
 FGameplayTag InputTag_1;
 FGameplayTag InputTag_2;
 FGameplayTag InputTag_3;
 FGameplayTag InputTag_4;
 
protected:
 
private:
 static FAuraGameplayTags GameplayTags;
 
};
