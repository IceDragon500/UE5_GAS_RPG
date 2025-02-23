// 我自己用来学习的试作品 -- 来自icedragon500


#include "AuraGameplayTags.h"

#include "AssetTypeCategories.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attribute_Primary_Strenght = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strenght"), FString("力量"));
	GameplayTags.Attribute_Primary_Intellingence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intellingence"), FString("智力"));
	GameplayTags.Attribute_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"), FString("活力"));
	GameplayTags.Attribute_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"), FString("体力"));
	
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("减少伤害，提高格挡几率"));
	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"), FString("护甲穿透 受韧性Res影响，会让伤害忽略一定比例的护甲，并增加了致命一击的几率"));
	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"), FString("格挡几率 受护甲Armor影响 会让收到的伤害减半"));
	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"), FString("致命一击 受护甲穿透Armor Pentration影响 几率使伤害和暴击加成加倍"));
	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"), FString("重击伤害 受护甲穿透Armor Pentration影响 当出现致命一击时的额外伤害"));
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"), FString("暴击抗性 受护甲Armor影响 降低敌人致命一击的几率"));
	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"), FString("生命恢复 受活力Viger影响 提高每秒生命值恢复量"));
	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"), FString("法力恢复 受影响智力Int 提高每秒法力值恢复量"));
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), FString("最大生命值 受活力Vig影响 提高最大生命值"));
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"), FString("最大法力值 受智力Int影响 提高最大法力值"));
}
