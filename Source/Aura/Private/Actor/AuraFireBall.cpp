// 我自己用来学习的试作品 -- 来自icedragon500


#include "Actor/AuraFireBall.h"
#include "Components/AudioComponent.h"
#include "GameplayCueManager.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"


void AAuraFireBall::BeginPlay()
{
	Super::BeginPlay();
	StarOutgoingTimeline();
}

void AAuraFireBall::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValidOverlap(OtherActor)) return;

	if (IgnoreList.Contains(OtherActor))
	{
		return;
	}

	if(HasAuthority())
	{
		if(UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			const FVector DeathImpulse = GetActorForwardVector() * DamageEffectParams.DeathImpulseMagnitude;
			DamageEffectParams.DeathImpulse = DeathImpulse;
			
			DamageEffectParams.TargetAbilitySystemComponent = TargetASC;
			UAuraAbilitySystemLibrary::ApplyDamageEffect(DamageEffectParams);
		}
		IgnoreList.Add(OtherActor);
	}
}

void AAuraFireBall::EmptyIgnoreList()
{
	IgnoreList.Empty();
}

void AAuraFireBall::OnHit()
{
	if (GetOwner() != nullptr)
	{
		FGameplayCueParameters CueParameters;
		CueParameters.Location = GetActorLocation();
		UGameplayCueManager::ExecuteGameplayCue_NonReplicated(
			GetOwner(),
			FAuraGameplayTags::Get().GameplayCue_FireBlast,
			CueParameters);
	}
	
	
	if(LoopingSoundComponent)
	{
		LoopingSoundComponent->Stop();
		LoopingSoundComponent->DestroyComponent();
	}

	bHit = true;
}
