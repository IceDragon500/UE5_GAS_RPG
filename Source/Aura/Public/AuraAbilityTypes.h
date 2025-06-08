#pragma once

#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FDamageEffectParams
{
	GENERATED_BODY()

	FDamageEffectParams(){}

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UObject> WorldContextObject = nullptr;

	//设置伤害相关的GameplayEffect类
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> DamageGameplayEffectClass = nullptr;

	//发起者的AbilitySystem组件
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> SourceAbilitySystemComponent;

	//受害者的AbilitySystem组件
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> TargetAbilitySystemComponent;

	//基础伤害值
	UPROPERTY(BlueprintReadWrite)
	float BaseDamage = 0.f;

	//Ability技能等级
	UPROPERTY(BlueprintReadWrite)
	float AbilityLevel = 1.f;

	//伤害类型
	UPROPERTY(BlueprintReadWrite)
	FGameplayTag DamageType = FGameplayTag();

	//Debuff概率
	UPROPERTY(BlueprintReadWrite)
	float DebuffChance = 0.f;

	//Debuff伤害值
	UPROPERTY(BlueprintReadWrite)
	float DebuffDamage = 0.f;

	//Debuff持续时间
	UPROPERTY(BlueprintReadWrite)
	float DebuffDuration = 0.f;

	//Debuff伤害间隔时间
	UPROPERTY(BlueprintReadWrite)
	float DebuffFrequency = 0.f;

	//死亡后击飞尸体的冲击量
	UPROPERTY(BlueprintReadWrite)
	float DeathImpulseMagnitude = 0.f;

	//死亡后击飞尸体的方向
	UPROPERTY(BlueprintReadWrite)
	FVector DeathImpulse = FVector::ZeroVector;

	//技能击飞目标的动量
	UPROPERTY(BlueprintReadWrite)
	float KnockbackForceMagnitude = 0.f;

	//技能击飞目标的概率
	UPROPERTY(BlueprintReadWrite)
	float KnockbackChance = 0.f;

	//技能击飞目标的方向
	UPROPERTY(BlueprintReadWrite)
	FVector KnockbackForce = FVector::ZeroVector;

	
};


USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:

	bool IsCriticalHit() const { return bIsCriticalHit; }//是否暴击
	bool IsBlockedHit() const { return bIsBlockedHit; }//是否被格挡伤害
	bool IsSuccessfullDebuff() const { return bIsSuccessfulDebuff; }//是否成功添加了debuff
	float GetDebuffDamage() const { return DebuffDamage; }//获取debuff的伤害
	float GetDebuffDuration() const { return DebuffDuration; }//获取debuff的持续时间
	float GetDebuffFrequency() const { return DebuffFrequency; }//获取debuff的伤害间隔时间
	TSharedPtr<FGameplayTag> GetDamageType() const { return DamageType; }//获取debuff的类型
	FVector GetDeathImpulse() const { return DeathImpulse; }//获取死亡时冲击量
	FVector GetKnockbackForce() const { return KnockbackForce; }//获取受伤害时被击退量

	void SetCriticalHit(bool bInIsCriticalHit)  { bIsCriticalHit = bInIsCriticalHit; }//设置是否被暴击
	void SetBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }//设置是否被格挡伤害
	void SetIsSuccessfulDebuff(bool bInIsDebuff) { bIsSuccessfulDebuff = bInIsDebuff; }//设置是否被应用debuff
	void SetDebuffDamage(float InDamage) { DebuffDamage = InDamage; }//设置debuff的伤害
	void SetDebuffDuration(float InDuration) { DebuffDuration = InDuration; }//设置debuff的持续时间
	void SetDebuffFrequency(float InFreq) { DebuffFrequency = InFreq; }//设置debuff伤害间隔时间
	void SetDamageType(TSharedPtr<FGameplayTag> InDamageType) { DamageType = InDamageType; }//设置debuff的伤害类型
	void SetDeathImpulse(const FVector& Impulse) { DeathImpulse = Impulse; }//设置死亡时的冲击量
	void SetKnockbackForce(const FVector& InForce) { KnockbackForce = InForce; }//设置收到伤害时的冲击量

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

	//死亡后击飞尸体的方向
	UPROPERTY()
	FVector DeathImpulse = FVector::ZeroVector;

	//技能击飞目标的方向
	UPROPERTY()
	FVector KnockbackForce = FVector::ZeroVector;

private:
	
};

//153课
//这是我们实现自定义游戏玩法所需的一个微妙但非常重要的细节
template<>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext> : TStructOpsTypeTraitsBase2<FAuraGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,// 启用自定义网络序列化 必须在FAuraGameplayEffectContext中实现NetSerialize()方法
		WithCopy = true// 启用深拷贝支持  必须实现Duplicate()方法
	};
};