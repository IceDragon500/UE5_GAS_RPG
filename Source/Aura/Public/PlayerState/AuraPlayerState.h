// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class ULevelUpInfo;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /*StatValue*/)

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;

	FOnPlayerStatChanged OnXPChangedDelegate;
	FOnPlayerStatChanged OnLevelChangedDelegate;
	FOnPlayerStatChanged OnAttributePointsChangedDelegate;
	FOnPlayerStatChanged OnSpellPointsChangedDelegate;

	FORCEINLINE int32 GetXP() const { return XP; }
	void SetXP(int32 InXP);
	void AddToXP(int32 InXP);
	
	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	void SetLevel(int32 InLevel);
	void AddToLevel(int32 InLevel);

	FORCEINLINE int32 GetPlayerAttributePoints() const { return AttributePoints; }
	void SetAttributePoints(int32 InAttributePoints);
	void AddToAttributePoints(int32 InAttributePoints);
	
	FORCEINLINE int32 GetPlayerSpellPoints() const { return SpellPoints; }
	void SetSpellPoints(int32 InSpellPoints);
	void AddToSpellPoints(int32 InSpellPoints);
	
	
protected:

	//玩家的ASC创建
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	//玩家的属性集
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:

	//玩家等级
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level = 1;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	//玩家经验
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_XP)
	int32 XP = 0;
	
	UFUNCTION()
	void OnRep_XP(int32 OldXP);

	//玩家属性点
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_AttributePoints)
	int32 AttributePoints = 0;

	UFUNCTION()
	void OnRep_AttributePoints(int32 OldAttributePoints);

	//玩家属性点
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_SpellPoints)
	int32 SpellPoints = 0;

	UFUNCTION()
	void OnRep_SpellPoints(int32 OldSpellPoints);

	
};
