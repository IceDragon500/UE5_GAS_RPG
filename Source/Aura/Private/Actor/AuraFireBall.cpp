// 我自己用来学习的试作品 -- 来自icedragon500


#include "Actor/AuraFireBall.h"



AAuraFireBall::AAuraFireBall()
{
	PrimaryActorTick.bCanEverTick = false;
}


void AAuraFireBall::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraFireBall::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}


void AAuraFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

