// 我自己用来学习的试作品 -- 来自icedragon500


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	//获得向前的向量
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	//获得角色的坐标
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	//用生成角度/小怪数量 得到每个怪物占用多少个角度
	//例如，5个怪物在角色前方一个大角度展开为一个扇形
	const float DeltaSpread = SpawnSpread / NumMinions;

	//把向前的向量Forward，向右旋转指定角度
	const FVector RightOfSpread = Forward.RotateAngleAxis(SpawnSpread / 2.f, FVector::UpVector);
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread / 2.f, FVector::UpVector);

	TArray<FVector> SpawnLocations;
	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult,
			ChosenSpawnLocation + FVector(0.f, 0.f, 500.f),
			ChosenSpawnLocation - FVector(0.f, 0.f, 500.f),
			ECC_Visibility
			);

		if(HitResult.bBlockingHit)
		{
			ChosenSpawnLocation = HitResult.ImpactPoint;
		}
		
		SpawnLocations.Add(ChosenSpawnLocation);
	}
	
	return SpawnLocations;
}

TSubclassOf<APawn> UAuraSummonAbility::GetRandomMinionClass()
{
	int32 Selection = FMath::RandRange(0, MinionClasses.Num() - 1);
	
	return MinionClasses[Selection];
}
