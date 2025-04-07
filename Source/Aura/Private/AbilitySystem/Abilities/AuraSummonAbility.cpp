// 我自己用来学习的试作品 -- 来自icedragon500


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Misc/TextFilterExpressionEvaluator.h"

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
		const FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);
		SpawnLocations.Add(ChosenSpawnLocation);
		//UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(),Location,Location+Direction*MaxSpawnDistance,4.f,FLinearColor::Red,3.f);
		DrawDebugSphere(GetWorld(), ChosenSpawnLocation, 10.0f, 20, FColor::Yellow, false, 3.f);
	}
	
	return SpawnLocations;
}
