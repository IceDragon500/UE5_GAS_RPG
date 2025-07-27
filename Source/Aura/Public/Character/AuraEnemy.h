// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/AuraCharacterBase.h"
#include "Components/WidgetComponent.h"
#include "Interaction/EnemyInterface.h"
#include "Interaction/HighlightInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"

class UBehaviorTree;
class AAuraAIController;

/**
 * 这里定义一个Enemy的数据结构类型，这样可以在UE中使用表格管理所有怪物类型的设置
 */
USTRUCT(BlueprintType)
struct FEnemyDataRow : public FTableRowBase
{
	GENERATED_BODY()

	//基础速度
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float WalkSpeed = 250;
	
	//尸体保留时间
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BodyRunTime = 5;
	
	//等级
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Level = 1;
	
	//角色职业类型
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECharacterClass CharacterClass = ECharacterClass::Warrior;
	
	//主要属性表
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	
	//次要属性表
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	
	//衍生属性表
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	
};

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase , public IEnemyInterface, public IHighlightInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();
	
	//重新设置Controller
	virtual void PossessedBy(AController* NewController) override;

	/** Highlight Interface */
	virtual void HighlightActor_Implementation() override;//高亮选中的目标
	virtual void UnHighlightActor_Implementation() override;//取消高亮选中的目标
	/** end Highlight Interface */

	/** Combat Interface */
	virtual int32 GetPlayerLevel_Implementation() override;
	virtual void Die(const FVector& DeathImpulse) override;
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;
	/** end Combat Interface */

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category="角色|命中反应")
	bool bHitReacting = false;
	
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

	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;

	//角色等级
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="角色|属性")
	int32 Level = 1;
	

	//血条Widget设置
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="角色|属性")
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, Category="角色|AI行为")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AAuraAIController> AuraAIController;
	
private:
	
	
	
};
