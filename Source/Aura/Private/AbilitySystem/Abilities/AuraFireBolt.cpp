// 我自己用来学习的试作品 -- 来自icedragon500


#include "AbilitySystem/Abilities/AuraFireBolt.h"

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
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-ProjectileSpread / 2.f, FVector::UpVector);
	const FVector RightOfSpread = Forward.RotateAngleAxis(ProjectileSpread / 2.f, FVector::UpVector);

	//NumProjectiles = FMath::Min(MaxNumProjectiles, GetAbilityLevel());
	

	if (NumProjectiles > 1)
	{
		const float DeltaSpread = ProjectileSpread / (NumProjectiles - 1);
		for (int32 i = 0; i < NumProjectiles; i++)
		{
			const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread*i, FVector::UpVector);
			const FVector Start = SocketLocation + FVector(0,0,10);
			UKismetSystemLibrary::DrawDebugArrow(
			GetAvatarActorFromActorInfo(),
			Start,
			Start + Direction * 100.f,
			5,
			FLinearColor::Red,
			120,
			2);
		}
	}
	else
	{
		//单个火球发射
		UKismetSystemLibrary::DrawDebugArrow(
			GetAvatarActorFromActorInfo(),
			SocketLocation,
			SocketLocation + Forward * 100.f,
			5,
			FLinearColor::Red,
			120,
			2);
		
	}
}
