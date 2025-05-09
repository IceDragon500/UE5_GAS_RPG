// 我自己用来学习的试作品 -- 来自icedragon500


#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

FString UAuraGameplayAbility::GetDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>%s,</><Level>%d</>"), L"默认Default Ability Name 默认Default Ability Name 默认Default Ability Name 默认Default Ability Name 默认Default Ability Name 默认Default Ability Name 默认Default Ability Name 默认Default Ability Name 默认Default Ability Name", Level);
}

FString UAuraGameplayAbility::GetNextLevelDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>%s,</><Level>%d</>"), L"下一个等级的信息NextLevel Ability Name 下一个等级的信息NextLevel Ability Name 下一个等级的信息NextLevel Ability Name 下一个等级的信息NextLevel Ability Name 下一个等级的信息NextLevel Ability Name 下一个等级的信息NextLevel Ability Name 下一个等级的信息NextLevel Ability Name 下一个等级的信息NextLevel Ability Name", Level);
}


FString UAuraGameplayAbility::GetLockedDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>Spell Locked Until Level:</><Level>%d</>"), Level);
}