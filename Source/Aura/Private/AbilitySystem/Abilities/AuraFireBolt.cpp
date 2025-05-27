// 我自己用来学习的试作品 -- 来自icedragon500


#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);

	if (Level == 1)
	{
		return FString::Printf(TEXT(
			"<Title>FIRE BOLT</>\n"
			"<Small>Level:</><Level>%d</>\n"
			"<Small>ManaCost:</><ManaCost>%.1f</>\n"
			"<Small>Cooldown :</><Cooldown>%.1f</>\n\n"
			"<Default>Launched a bolt of fire, exploding on impact and dealing</>"
			"<Damage>%d</><Default> fire damage with a chance to burn</>\n\n"

		), Level, ManaCost, Cooldown, ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
			"<Title>FIRE BOLT</>\n"
			"<Small>Level:</>""<Level>%d</>\n"
			"<Small>ManaCost:</><ManaCost>%.1f</>\n"
			"<Small>Cooldown :</><Cooldown>%.1f</>\n\n"
			"<Default>Launched %d bolt of fire, exploding on impact and dealing</>"
			"<Damage>%d</><Default> "
			"fire damage with a chance to burn</>\n"
		), Level, ManaCost, Cooldown, FMath::Min(Level, MaxNumProjectiles), ScaledDamage);
	}
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);

	return FString::Printf(TEXT(
		"<Title>NEXT LEVEL:</>\n"
		"<Small>Level:</>""<Level>%d</>\n"
		"<Small>ManaCost:</><ManaCost>%.1f</>\n"
		"<Small>Cooldown :</><Cooldown>%.1f</>\n\n"
		"<Default>Launched %d bolt of fire, exploding on impact and dealing</>"
		"<Damage>%d</><Default> "
		"fire damage with a chance to burn</>\n"
	), Level, ManaCost, Cooldown, FMath::Min(Level, MaxNumProjectiles), ScaledDamage);
}

void UAuraFireBolt::SpwanProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag,
                                     bool bOverridePitch, float PitchOverride, AActor* HomingTarget)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();

	if (!bIsServer)
	{
		return;
	}

	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), SocketTag);

	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();

	if (bOverridePitch) Rotation.Pitch = PitchOverride;

	const FVector Forward = Rotation.Vector();

	TArray<FVector> Directions = UAuraAbilitySystemLibrary::EvenlyRotatedVectors(Forward, FVector::UpVector, ProjectileSpread, NumProjectiles);
	TArray<FRotator> Rotations = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, ProjectileSpread, NumProjectiles);

	for (const FRotator& Rot : Rotations)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rot.Quaternion());

		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn //定义了用于处理以下情况的可用策略：当角色生成时，它穿透了阻挡碰撞。
	);

	
		Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefault(nullptr);


		Projectile->FinishSpawning(SpawnTransform);
	}
}
