// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "AuraAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;

UCLASS()
class AURA_API AAuraAIController : public AAIController
{
	GENERATED_BODY()

public:
	
	AAuraAIController();
	virtual void Tick(float DeltaTime) override;

protected:
	
	virtual void BeginPlay() override;

	//我们使用AIController自带的Blackboard 就不重新创建UBlackboardComponent组件了
	
	//行为树
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComp;

private:

	
};
