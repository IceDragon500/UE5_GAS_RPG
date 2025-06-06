// 我自己用来学习的试作品 -- 来自icedragon500


#include "AbilitySystem/Abilities/AuraBeamSpell.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

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

void UAuraBeamSpell::StoreOwnerVariables()
{
	if (CurrentActorInfo)//这里CurrentActorInfo里面的PlayerController是个弱指针TWeakObjectPtr 所以这需要先检查一下CurrentActorInfo是否有效
	{
		OwnerPlayerController = CurrentActorInfo->PlayerController.Get();//使用弱指针给普通指针赋值，需要用到Get方法
		OwnerCharacter = Cast<ACharacter>(CurrentActorInfo->AvatarActor);
	}
	
}

void UAuraBeamSpell::TraceFirstTarget(const FVector& BeamTargetLocation)
{
	check(OwnerCharacter)
	if (OwnerCharacter->Implements<UCombatInterface>())
	{
		if (USkeletalMeshComponent* Weapon = ICombatInterface::Execute_GetWeapon(OwnerCharacter))
		{
			TArray<AActor*> ActorToIgnore;
			ActorToIgnore.Add(OwnerCharacter);
			FHitResult HitResult;
			const FVector SocketLocatioin = Weapon->GetSocketLocation(FName("TipSocket"));
			UKismetSystemLibrary::SphereTraceSingle(
				OwnerCharacter,
				SocketLocatioin,
				BeamTargetLocation,
				10.f,
				TraceTypeQuery1,
				false,
				ActorToIgnore,
				EDrawDebugTrace::ForDuration,
				HitResult,
				true);

			if (HitResult.bBlockingHit)
			{
				MouseHitLocation = HitResult.ImpactPoint;
				MouseHitActor = HitResult.GetActor();
			}
		}
	}
	
}

void UAuraBeamSpell::StoreAdditionalTargets(TArray<AActor*>& OutAdditionalTargets)
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
	ActorsToIgnore.Add(MouseHitActor);
	
	TArray<AActor*> OverlappingActors;
	
	UAuraAbilitySystemLibrary::GetLivePlayersWithRadius(
		GetAvatarActorFromActorInfo(),
		OverlappingActors,
		ActorsToIgnore,
		MaxShockRadius,
		MouseHitActor->GetActorLocation());

	//int32 NumAddtionalTargets = FMath::Min(GetAbilityLevel() - 1, MaxNumShockTargets);

	int32 NumAddtionalTargets = MaxNumShockTargets;

	UAuraAbilitySystemLibrary::GetClosestTargets(NumAddtionalTargets, OverlappingActors, OutAdditionalTargets, MouseHitActor->GetActorLocation());
}
