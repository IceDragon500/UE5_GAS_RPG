// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/AuraCharacterBase.h"
#include "Components/WidgetComponent.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"

class UBehaviorTree;
class AAuraAIController;

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
	
	//重新设置Controller
	virtual void PossessedBy(AController* NewController) override;
	
	//高亮选中的目标
	virtual void HighlightActor() override;
	//取消高亮选中的目标
	virtual void UnHighlightActor() override;

	virtual int32 GetPlayerLevel() override;

	virtual void Die() override;

	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category="角色|命中反应")
	bool bHitReacting = false;

	//基础移动速度
	UPROPERTY(EditAnywhere, Category="角色|属性", meta = (DisplayName = "基础移动速度"))
	float BaseWalkSpeed = 250.f;

	//尸体存在时间
	UPROPERTY(EditAnywhere, Category="角色|属性", meta = (DisplayName = "尸体存在时间"))
	float LifeSpan = 5.f;

	//保存当前攻击的目标
	UPROPERTY(BlueprintReadWrite, Category="角色|属性", meta = (DisplayName = "攻击目标"))
	TObjectPtr<AActor> CombatTarget;
	
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

	UPROPERTY(EditAnywhere, Category="角色|AI行为")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AAuraAIController> AuraAIController;
	
private:
	
	
	
};
