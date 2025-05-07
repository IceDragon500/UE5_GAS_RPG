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

 FGameplayTag Attributes_Resistance_Fire;//火焰抗性
 FGameplayTag Attributes_Resistance_Lightning;
 FGameplayTag Attributes_Resistance_Arcane;
 FGameplayTag Attributes_Resistance_Physical;

 FGameplayTag Attributes_Meta_IncomingXP;

 FGameplayTag InputTag_LMB;
 FGameplayTag InputTag_RMB;
 FGameplayTag InputTag_1;
 FGameplayTag InputTag_2;
 FGameplayTag InputTag_3;
 FGameplayTag InputTag_4;
 FGameplayTag InputTag_Passive_1;
 FGameplayTag InputTag_Passive_2;

 FGameplayTag Damage;
 FGameplayTag Damage_Fire; //火焰伤害
 FGameplayTag Damage_Lightning; //闪电伤害
 FGameplayTag Damage_Arcane; //奥术伤害
 FGameplayTag Damage_Physical; //物理伤害

 FGameplayTag Abilities_Attack;
 FGameplayTag Abilities_Summon;
 
 FGameplayTag Abilities_None;
 
 FGameplayTag Abilities_HitReact;

 //技能的几种状态
 FGameplayTag Abilities_Status_Locked;//被锁定
 FGameplayTag Abilities_Status_Eligible;//具备条件的
 FGameplayTag Abilities_Status_Unlocked;//解锁的
 FGameplayTag Abilities_Status_Equipped;//已被装备的

 //技能的类型
 FGameplayTag Abilities_Type_Offensive;//攻击技能
 FGameplayTag Abilities_Type_Passive;//被动技能
 FGameplayTag Abilities_Type_None;//未分类的技能

 //FireBolt技能
 FGameplayTag Abilities_Fire_FireBolt;
 FGameplayTag Cooldown_Fire_FireBolt;

 //Lighting技能
 FGameplayTag Abilities_Lighting_Electrocute;
 FGameplayTag Cooldown_Lighting_Electrocute;


 FGameplayTag CombatSocket_Weapon;
 FGameplayTag CombatSocket_RightHand;
 FGameplayTag CombatSocket_LeftHand;
 FGameplayTag CombatSocket_Trail;

 FGameplayTag Montage_Attack_1;
 FGameplayTag Montage_Attack_2;
 FGameplayTag Montage_Attack_3;
 FGameplayTag Montage_Attack_4;

 TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;
 
 FGameplayTag Effect_HitReact;
 
protected:
 
private:
 static FAuraGameplayTags GameplayTags;
 
};

