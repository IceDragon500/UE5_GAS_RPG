// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "Checkpoint.h"
#include "MapEntrance.generated.h"

UCLASS()
class AURA_API AMapEntrance : public ACheckpoint
{
	GENERATED_BODY()

public:
	AMapEntrance(const FObjectInitializer& ObjectInitializer);

	/*Highlight Interface*/
	virtual void HighlightActor_Implementation() override;
	/*End Highlight Interface*/

	/*Save Interface*/
	virtual void LoadActor_Implementation() override;
	/*End Save Interface*/

	//前往的下个地图
	UPROPERTY(EditAnywhere, Category= "属性设置")
	TSoftObjectPtr<UWorld> DestinationMap;

	//前往的下个地图，玩家出现的起始点
	UPROPERTY(EditAnywhere, Category= "属性设置")
	FName DestinationPlayerStartTag;

protected:
	
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	
private:
	
	
};
