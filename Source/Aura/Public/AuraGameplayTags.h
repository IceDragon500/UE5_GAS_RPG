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

	FGameplayTag Attributes_Secondary_Armor; //护甲
	FGameplayTag Attributes_Secondary_ArmorPenetration; //护甲穿透
	FGameplayTag Attributes_Secondary_BlockChance; //格挡几率
	FGameplayTag Attributes_Secondary_CriticalHitChance; //致命一击
	FGameplayTag Attributes_Secondary_CriticalHitDamage; //重击伤害
	FGameplayTag Attributes_Secondary_CriticalHitResistance; //暴击抗性
	FGameplayTag Attributes_Secondary_HealthRegeneration; //生命恢复
	FGameplayTag Attributes_Secondary_ManaRegeneration; //法力恢复
	FGameplayTag Attributes_Secondary_MaxHealth; //最大生命值
	FGameplayTag Attributes_Secondary_MaxMana; //最大法力值

	/**
	 * 抗性Tag
	 */
	FGameplayTag Attributes_Resistance_Fire; //火焰抗性
	FGameplayTag Attributes_Resistance_Lightning;
	FGameplayTag Attributes_Resistance_Arcane;
	FGameplayTag Attributes_Resistance_Physical;

	//经验
	FGameplayTag Attributes_Meta_IncomingXP;

	/**
	 * Debuff Tag
	 */
	FGameplayTag Debuff_Burn;//自身开始燃烧
	FGameplayTag Debuff_Stun;//眩晕
	FGameplayTag Debuff_Arcane;//奥术Debuff
	FGameplayTag Debuff_Physical;//物理伤害Debuff

	FGameplayTag Debuff_Chance;//debuff的概率
	FGameplayTag Debuff_Damage;//debuff的伤害值
	FGameplayTag Debuff_Duration;//debuff的持续时间
	FGameplayTag Debuff_Frequency;//debuff伤害的间隔时间、频率

	/**
	 * 输入Tag
	 */
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	FGameplayTag InputTag_Passive_1;
	FGameplayTag InputTag_Passive_2;

	/**
	 * 伤害类型Tag
	 */
	FGameplayTag Damage;
	FGameplayTag Damage_Fire; //火焰伤害
	FGameplayTag Damage_Lightning; //闪电伤害
	FGameplayTag Damage_Arcane; //奥术伤害
	FGameplayTag Damage_Physical; //物理伤害

	//怪物的攻击方式
	FGameplayTag Abilities_Attack; //怪物正常攻击
	FGameplayTag Abilities_Summon; //怪物使用召唤技能

	FGameplayTag Abilities_None;

	//怪物受到攻击产生的受击动作Tag
	FGameplayTag Abilities_HitReact;
	//受到攻击产生的攻击特效粒子
	FGameplayTag Effect_HitReact;

	//技能的几种状态
	FGameplayTag Abilities_Status_Locked; //被锁定
	FGameplayTag Abilities_Status_Eligible; //具备条件的
	FGameplayTag Abilities_Status_Unlocked; //解锁的
	FGameplayTag Abilities_Status_Equipped; //已被装备的

	//技能的类型
	FGameplayTag Abilities_Type_Offensive; //攻击技能
	FGameplayTag Abilities_Type_Passive; //被动技能
	FGameplayTag Abilities_Type_None; //未分类的技能

	//FireBolt技能
	FGameplayTag Abilities_Fire_FireBolt;
	FGameplayTag Cooldown_Fire_FireBolt;

	//Lighting技能
	FGameplayTag Abilities_Lighting_Electrocute;
	FGameplayTag Cooldown_Lighting_Electrocute;

	//Arcane技能
	FGameplayTag Abilities_Arcane_ArcaneShards;
	FGameplayTag Cooldown_Arcane_ArcaneShards;

	//FireBlast技能
	FGameplayTag Abilities_Fire_FireBlast;
	FGameplayTag Cooldown_Fire_FireBlast;
	
	//武器Socket的几种Tag
	FGameplayTag CombatSocket_Weapon; //表示有武器Mesh，Socket在武器上
	FGameplayTag CombatSocket_RightHand; //表示Socket在右手上 右手攻击
	FGameplayTag CombatSocket_LeftHand; //表示Socket在左手上 左手攻击
	FGameplayTag CombatSocket_Trail;

	//表示几种攻击动画的Tag
	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;

	//发射火球的MontageTag
	FGameplayTag Event_Montage_FireBolt;
	//发射电击的MontageTag
	FGameplayTag Event_Montage_Electrocute;
	//发射岩石碎片的MontageTag
	FGameplayTag Event_Montage_ArcaneShards;

	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;
	TMap<FGameplayTag, FGameplayTag> DamageTypesToDebuffs;


	//用于按键状态之间的互斥检测
	FGameplayTag Player_Block_InputPressed;//按下
	FGameplayTag Player_Block_InputHeld;//按下不放
	FGameplayTag Player_Block_InputReleased;//松开
	FGameplayTag Player_Block_InputCursorTrace;//停止鼠标射线检测

	//被动技能 用来实现游戏中不可见的被动效果
	
	FGameplayTag Abilities_Passive_ListenForEvent;

	//被动技能 用来实现游戏中可见的被动效果
	FGameplayTag Abilities_Passive_HaloOfProtection;//保护光环
	FGameplayTag Abilities_Passive_LifeSiphon;//生命虹吸
	FGameplayTag Abilities_Passive_ManaSiphon;//法力虹吸

	/**
	 * GameplayCue
	 * 游戏技能队列
	 */
	FGameplayTag GameplayCue_FireBlast;
	

protected:

private:
	static FAuraGameplayTags GameplayTags;
};
