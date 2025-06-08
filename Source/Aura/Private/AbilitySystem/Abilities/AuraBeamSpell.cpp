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
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}
}

void UAuraBeamSpell::StoreOwnerVariables()
{
	/**
	 * CurrentActorInfo 的解释如下：
	 *  这是关于使用此能力的实体的共享缓存信息。
	 *  例如：Actor*（角色指针）、MovementComponent*（移动组件指针）、AnimInstance（动画实例）等。
	 *  理想情况下，此信息为每个 Actor 分配一次，并被多个能力共享。
	 *  实际的结构体可以在具体游戏中被重写，以包含特定于游戏的数据。
	 *  （例如，派生类可能希望将其转换为 FMyGameAbilityActorInfo 类型）
	 *  mutable const FGameplayAbilityActorInfo* CurrentActorInfo;
	 *
	 *  mutable: 表示即使在 const 成员函数中，这个指针指向的内容也可以被修改（通常是指针本身不会被修改，但它指向的 FGameplayAbilityActorInfo 对象内部可能有可变状态）
	 * 
	 */
	
	if (CurrentActorInfo) //这里CurrentActorInfo里面的PlayerController是个弱指针TWeakObjectPtr 所以这需要先检查一下CurrentActorInfo是否有效
	{
		OwnerPlayerController = CurrentActorInfo->PlayerController.Get(); //使用弱指针给普通指针赋值，需要用到Get方法
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
				EDrawDebugTrace::None,
				HitResult,
				true);

			if (HitResult.bBlockingHit)
			{
				MouseHitLocation = HitResult.ImpactPoint;
				MouseHitActor = HitResult.GetActor();
			}
		}
	}
	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(MouseHitActor))
	{
		if (!CombatInterface->GetOnDeathDelegate().IsAlreadyBound(this, &UAuraBeamSpell::PrimaryTargetDied))
		{
			CombatInterface->GetOnDeathDelegate().AddDynamic(this, &UAuraBeamSpell::PrimaryTargetDied);
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

	int32 NumAddtionalTargets = FMath::Min(GetAbilityLevel() - 1, MaxNumShockTargets);

	//int32 NumAddtionalTargets = MaxNumShockTargets;

	UAuraAbilitySystemLibrary::GetClosestTargets(
		NumAddtionalTargets,
		OverlappingActors,
		OutAdditionalTargets,
		MouseHitActor->GetActorLocation());

	for (AActor* Target : OutAdditionalTargets)
	{
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(Target))
		{
			if (!CombatInterface->GetOnDeathDelegate().IsAlreadyBound(this, &UAuraBeamSpell::AdditionalTargetDied))
			{
				CombatInterface->GetOnDeathDelegate().AddDynamic(this, &UAuraBeamSpell::AdditionalTargetDied);
			}
		}
	}
}
