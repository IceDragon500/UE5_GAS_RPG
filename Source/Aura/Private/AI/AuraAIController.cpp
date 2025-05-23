// 我自己用来学习的试作品 -- 来自icedragon500
/**
 * 1234567890
 * abcdefghijklmnopqrstuvwxyz
 */

#include "AI/AuraAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
AAuraAIController::AAuraAIController()
{
	//PrimaryActorTick.bCanEverTick = true;

	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("Blackboard");
	check(Blackboard);

	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTree");
	check(BehaviorTreeComp);
}

// Called when the game starts or when spawned
void AAuraAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAuraAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

