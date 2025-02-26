// 我自己用来学习的试作品 -- 来自icedragon500


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputAction(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FAuraInputAction& Action : AbilityInputActions)
	{
		if(Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if(bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("在InputTag[%s],找不到东西[%s]"), *GetNameSafe(this) ,*InputTag.ToString());
	}

	return nullptr;
}
