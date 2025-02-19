// 我自己用来学习的试作品

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract) //Abstract表示这一个抽象类，不能直接实例化
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:

	AAuraCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:

	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, Category= "角色|Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	//用来初始化主要属性
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	//用来初始化次要属性
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	//创建GameplayEffect的方式
	void ApplyEffetToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;

	//对属性进行初始化
	//增加了一个注释
	//没有问题
	void InitializeDefaultAttributes() const;

private:

	virtual void InitAbilityActorInfo();

public:
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return Weapon; }
	


};
