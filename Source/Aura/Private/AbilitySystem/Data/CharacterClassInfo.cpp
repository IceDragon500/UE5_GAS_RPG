// 我自己用来学习的试作品 -- 来自icedragon500


#include "AbilitySystem/Data/CharacterClassInfo.h"

FCharacterClassDefaultInfo UCharacterClassInfo::GetCLassDefaultInfo(ECharacterClass CharacterClass)
{
	return CharacterClassInfoMap.FindChecked(CharacterClass);
}
