// 我自己用来学习的试作品 -- 来自icedragon500


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLoNotFound) const
{
	for (const FAuraAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}

	if (bLoNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("在AttributeTag找不到[%s]内容"), *AttributeTag.ToString());
	}
	return FAuraAttributeInfo();
}
