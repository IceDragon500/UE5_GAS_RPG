// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/AuraCharacterBase.h"
#include "Components/WidgetComponent.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
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
	
	//高亮选中的目标
	virtual void HighlightActor() override;
	//取消高亮选中的目标
	virtual void UnHighlightActor() override;

	virtual int32 GetPlayerLevel() override;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
	
protected:

	virtual void BeginPlay() override;

	//初始化角色的AbilitySystemComponent
	virtual void InitAbilityActorInfo() override;

	//初始化角色的属性值
	virtual void InitializeDefaultAttributes() const override;

	//角色等级
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="角色|属性")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="角色|属性")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	//血条Widget设置
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="角色|属性")
	TObjectPtr<UWidgetComponent> HealthBar;
	
private:
	
	
	
};
