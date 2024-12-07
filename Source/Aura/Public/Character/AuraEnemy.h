// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

#define CUSTOM_DEPTH_RED 250
#define CUSTOM_DEPTH_BLUE 251
#define CUSTOM_DEPTH_TAN 252

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase , public IEnemyInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();
	
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;
	
	
protected:
private:
	
};
