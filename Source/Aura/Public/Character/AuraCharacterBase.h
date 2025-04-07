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

	/* combat interface */
	//处理死亡是应该做的事情，这里
	virtual void Die() override;
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetActor_Implementation() override;
	virtual TArray<FTaggedMontage> GetAttackMontages_Implementation() override;
	virtual UNiagaraSystem* GetBloodEffect_Implementation() override;
	virtual FTaggedMontage GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag) override;
	/* combat interface end */
		
	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath();

	UPROPERTY(EditAnywhere, Category="角色|Combat", meta =(DisplayName = "设置Montage和对应的Tags"))
	TArray<FTaggedMontage> AttackMontages;

protected:

	virtual void BeginPlay() override;

	//设置角色使用的武器
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "角色|Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	//武器的SocketName
	UPROPERTY(EditAnywhere, Category= "角色|Combat", meta =(DisplayName = "武器的SocketName"))
	FName WeaponTipSocketName;
	
	//左手的SocketName
	UPROPERTY(EditAnywhere, Category= "角色|Combat", meta =(DisplayName = "左手的SocketName"))
	FName LeftHandSocketName;

	//右手的SocketName
	UPROPERTY(EditAnywhere, Category= "角色|Combat", meta =(DisplayName = "右手的SocketName"))
	FName RightHandSocketName;

	//尾部的SocketName
	UPROPERTY(EditAnywhere, Category= "角色|Combat", meta =(DisplayName = "尾部的SocketName"))
	FName TrailSocketName;

	bool bDead = false;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	//用来初始化主要属性
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="角色|属性", meta =(DisplayName = "主要属性表"))
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	//用来初始化次要属性
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="角色|属性")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	//用来初始化 Vital 至关重要！的属性值
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="角色|属性")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	//创建GameplayEffect的方式
	void ApplyEffetToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;

	//对属性进行初始化
	//增加了一个注释
	//没有问题
	virtual void InitializeDefaultAttributes() const;

	void AddCharacterAbilities();

	/*
	 * 溶解特效
	 */

	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* WeaponDynamicMaterialInstance);

	//角色被击败后，溶解的特效纹理
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="角色|属性")
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	//角色使用的武器，被击败后，溶解的特效纹理
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="角色|属性")
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;

	//角色被击中的出血效果
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="角色|属性")
	UNiagaraSystem* BloodEffect;

	//死亡音效
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="角色|属性")
	USoundBase* DeathSound;
private:

	virtual void InitAbilityActorInfo();

	//起始属性集
	UPROPERTY(EditAnywhere, Category="角色|属性")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	//收集动画
	UPROPERTY(EditAnywhere, Category="角色|属性")
	TObjectPtr<UAnimMontage> HitReactMontage;

public:
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return Weapon; }
	


};
