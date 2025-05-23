#pragma once

#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FDamageEffectParams
{
	GENERATED_BODY()

	FDamageEffectParams(){}

	UPROPERTY()
	TObjectPtr<UObject> WorldContextObject = nullptr;
	
	UPROPERTY()
	TSubclassOf<UGameplayEffect> DamageGameplayEffectClass = nullptr;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceAbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetAbilitySystemComponent;

	UPROPERTY()
	float BaseDamage = 0.f;

	UPROPERTY()
	float AbilityLevel = 1.f;

	UPROPERTY()
	FGameplayTag DamageType = FGameplayTag();

	//Debuff概率
	UPROPERTY()
	float DebuffChance = 0.f;

	//Debuff伤害
	UPROPERTY()
	float DebuffDamage = 0.f;

	//Debuff伤害间隔时间
	UPROPERTY()
	float DebuffDuration = 0.f;

	//Debuff持续时间
	UPROPERTY()
	float DebuffFrequency = 0.f;

	//死亡冲量
	UPROPERTY()
	float DeathImpulseMagnitude = 0.f;

	//死亡冲量
	UPROPERTY()
	FVector DeathImpulse = FVector::ZeroVector;
};


USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:

	bool IsCriticalHit() const { return bIsCriticalHit; }
	bool IsBlockedHit() const { return bIsBlockedHit; }
	bool IsSuccessfullDebuff() const { return bIsSuccessfulDebuff; }
	float GetDebuffDamage() const { return DebuffDamage; }
	float GetDebuffDuration() const { return DebuffDuration; }
	float GetDebuffFrequency() const { return DebuffFrequency; }
	TSharedPtr<FGameplayTag> GetDamageType() const { return DamageType; }
	FVector GetDeathImpulse() const { return DeathImpulse; }

	void SetCriticalHit(bool bInIsCriticalHit)  { bIsCriticalHit = bInIsCriticalHit; }
	void SetBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }
	void SetIsSuccessfulDebuff(bool bInIsDebuff) { bIsSuccessfulDebuff = bInIsDebuff; }
	void SetDebuffDamage(float InDamage) { DebuffDamage = InDamage; }
	void SetDebuffDuration(float InDuration) { DebuffDuration = InDuration; }
	void SetDebuffFrequency(float InFreq) { DebuffFrequency = InFreq; }
	void SetDamageType(TSharedPtr<FGameplayTag> InDamageType) { DamageType = InDamageType; }
	void SetDeathImpulse(const FVector& Impulse) { DeathImpulse = Impulse; }

	/** Returns the actual struct used for serialization, subclasses must override this! */
	/* 返回序列化所用的实际结构体，子类必须重载该结构体 */
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FAuraGameplayEffectContext* Duplicate() const
	{
		FAuraGameplayEffectContext* NewContext = new FAuraGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	/** Custom serialization, subclasses must override this */
	/* 自定义序列化，子类必须重载该功能 */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

protected:

	//是否有暴击
	UPROPERTY()
	bool bIsCriticalHit = false;

	//是否被阻挡了伤害
	UPROPERTY()
	bool bIsBlockedHit = false;

	//是否成功附加了Debuff
	UPROPERTY()
	bool bIsSuccessfulDebuff = false;

	//Debuff的伤害
	UPROPERTY()
	float DebuffDamage = 0.f;

	//Debuff的持续时间
	UPROPERTY()
	float DebuffDuration = 0.f;

	//Debuff的间隔时间
	UPROPERTY()
	float DebuffFrequency = 0.f;

	//伤害类型
	TSharedPtr<FGameplayTag> DamageType;

	//死亡冲击向量
	UPROPERTY()
	FVector DeathImpulse = FVector::ZeroVector;

private:
	
};

//153课
//这是我们实现自定义游戏玩法所需的一个微妙但非常重要的细节
template<>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext> : TStructOpsTypeTraitsBase2<FAuraGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};