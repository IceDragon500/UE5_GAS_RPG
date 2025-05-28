// 我自己用来学习的试作品 -- 来自icedragon500


#include "AbilitySystem/Abilities/AuraBeamSpell.h"

void UAuraBeamSpell::StoreMouseDataInfo(const FHitResult& HitResult)
{
	if (HitResult.bBlockingHit)
	{
		MouseHitLocation = HitResult.ImpactPoint;
		MouseHitActor = HitResult.GetActor();
		
	}
	else
	{
		//这里如果失败了，则取消激活Ability，传入的几个参数都是GameAbility类自带的
		EndAbility(CurrentSpecHandle, CurrentActorInfo,CurrentActivationInfo, true, false);
	}
}

void UAuraBeamSpell::StoreOwnerPlayerController()
{
	if (CurrentActorInfo)//这里CurrentActorInfo里面的PlayerController是个弱指针TWeakObjectPtr 所以这需要先检查一下CurrentActorInfo是否有效
	{
		OwnerPlayerController = CurrentActorInfo->PlayerController.Get();//使用弱指针给普通指针赋值，需要用到Get方法
	}
	
}
