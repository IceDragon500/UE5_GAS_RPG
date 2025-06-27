// 我自己用来学习的试作品 -- 来自icedragon500


#include "Actor/AuraFireBall.h"


void AAuraFireBall::BeginPlay()
{
	Super::BeginPlay();
	StarOutgoingTimeline();
}

void AAuraFireBall::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}