// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

//用这个宏，可以自动帮我们生成 getAttribute get set init 4行代码
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

//弹幕提示
//GS基类当中本来就有一个PostAttriobuteChange的函数，直接从写这个函数多播就行了啊
//教程中使用函数指针来代替委托
//DECLARE_DELEGATE_RetVal(FGameplayAttribute, FAttributeSignature);

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	
	UPROPERTY()
	AController* SourceController = nullptr;
	
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	
	UPROPERTY()
	AController* TargetController = nullptr;
	
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
	
};

//typedef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;

template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();

	//返回在参与者通道生命周期内复制的属性
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	//用来做Clamp功能的函数
	//This function is meant to enforce things like "Health = Clamp(Health, 0, MaxHealth)" and NOT things like "trigger this extra thing if damage is applied, etc".
	//这个函数是用来执行“生命值= Clamp（生命值，0,MaxHealth）”之类的内容，而不是“如果施加伤害就触发这个额外的东西，等等”之类的内容。
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	/**
	 *	Called just after a GameplayEffect is executed to modify the base value of an attribute. No more changes can be made.
	 *	在GameplayEffect执行后调用，修改属性的基本值。不能再做任何更改。
	 *	Note this is only called during an 'execute'. E.g., a modification to the 'base value' of an attribute. It is not called during an application of a GameplayEffect, such as a 5 ssecond +10 movement speed buff.
	 *	注意，这只在‘执行’期间调用。例如，修改属性的“基本值”。它不会在GameplayEffect的应用过程中被调用，比如5秒+10的移动速度buff。
	 */
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


	//Called just after any modification happens to an attribute
	//在属性发生任何修改之后调用
	//PostAttributeChange的触发更加的敏感，也就是更耗性能
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;


	//这是使用委托的方式
	//TMap<FGameplayTag, FAttributeSignature> TagsToAttributes;


	//这里使用了很高级的函数指针
	//95课. Mapping Tags to Attributes
	//16分钟开始
	//这里涉及到了函数指针  泛型编程
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

	//TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FunctionPointer;

	/**
	 * Primary Attributes
	 * 主属性
	 * 我们使用DataTable来生成下面4个属性  但是这个不是我们主要的方式
	 * 我们可以在UAttributeSet.h中可以找到FAttributeMetaData的定义
	 * DataTable that allows us to define meta data about attributes. Still a work in progress.
	 * DataTable，它允许我们定义关于属性的元数据。这项工作仍在进行中。
	 * 我们也可以查看到对应的结构体
	 *
	 * 我们继续使用Gameplay Effect来初始化数据
	 * 我们转到AuraCharacterBase.h中
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "属性值|主要属性")
	//力量
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);//见最顶上的注释，用一个宏来代替生成4行代码
	
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "属性值|主要属性")
	//智力
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "属性值|主要属性")
	//韧性
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "属性值|主要属性")
	//活力
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

	//当前生命值
	//在构造函数中被初始化
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "属性值|主要属性")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	//当前法力值
	//在构造函数中被初始化
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "属性值|主要属性")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana)
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	/**
	 * Secondary Attributes
	 * 次要属性
	 */

	//Armor 护甲 受韧性Res影响 减少收到的伤害
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "属性值|次要属性")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	//Armor Pentration 护甲穿透 受韧性Res影响，会让伤害忽略一定比例的护甲，并增加了致命一击的几率
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPentration, Category = "属性值|次要属性")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);

	UFUNCTION()
	void OnRep_ArmorPentration(const FGameplayAttributeData& OldArmorPentration) const;

	//Block Chance 格挡几率 受护甲Armor影响 会让收到的伤害减半
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "属性值|次要属性")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

	//Critical Hit Chance 致命一击 受护甲穿透Armor Pentration影响 几率使伤害和暴击加成加倍
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "属性值|次要属性")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

	//Critical Hit Damage 重击伤害 受护甲穿透Armor Pentration影响 当出现致命一击时的额外伤害
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "属性值|次要属性")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

	//Critical Hit Resistance 暴击抗性 受护甲Armor影响 降低敌人致命一击的几率
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "属性值|次要属性")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance);

	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;

	//Health Regeneration 生命恢复 受活力Viger影响 提高每秒生命值恢复量
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "属性值|次要属性")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

	//Mana Regeneration 法力恢复 受影响智力Int 提高每秒法力值恢复量
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "属性值|次要属性")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);

	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;

	//Max Health 最大生命值 受活力Vig影响 提高最大生命值
	//在构造函数中被初始化
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "属性值|次要属性")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	//Max Manan 最大法力值 受智力Int影响 提高最大法力值
	//在构造函数中被初始化
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "属性值|次要属性")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana)
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	/*
	 * Resistance Attributes
	 * 抗性属性设置
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireResistance, Category = "属性值|抗性属性")
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, FireResistance)
	
	UFUNCTION()
	void OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LightningResistance, Category = "属性值|抗性属性")
	FGameplayAttributeData LightningResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, LightningResistance)
	
	UFUNCTION()
	void OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArcaneResistance, Category = "属性值|抗性属性")
	FGameplayAttributeData ArcaneResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArcaneResistance)
	
	UFUNCTION()
	void OnRep_ArcaneResistance(const FGameplayAttributeData& OldArcaneResistance) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalResistance, Category = "属性值|抗性属性")
	FGameplayAttributeData PhysicalResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, PhysicalResistance)
	
	UFUNCTION()
	void OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance) const;

/*
 * meta Attributes
 */
	
	//计算即将到来的伤害
	UPROPERTY(BlueprintReadOnly, Category="属性值|Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IncomingDamage);

	//计算即将到来的伤害
	UPROPERTY(BlueprintReadOnly, Category="属性值|Meta Attributes")
	FGameplayAttributeData IncomingXP;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IncomingXP);

protected:
private:
	/**
	 * 使用传入的Data 来填充Props
	 * @param Data 
	 * @param Props 
	 */
	void SetEffectProperties(const FGameplayEffectModCallbackData& InData, FEffectProperties& OutProps) const;

	/**
	 * 处理即将到来的伤害
	 * @param Props 
	 */
	void HandleInComingDamage(const FEffectProperties Props);
	
	void HandleIncomingXP(const FEffectProperties Props);

	void Debuff(const FEffectProperties Props);

	/**
	 * 显示伤害文字
	 * @param Props 里面包含Target 和 Sources的gameplay effect信息 
	 * @param Damage 伤害数值
	 * @param bBlockHit 是否阻挡伤害
	 * @param bCriticalHit 是否暴击
	 */
	void ShowFloatingText(const FEffectProperties& Props, float Damage, bool bBlockHit, bool bCriticalHit);

	/**
	 * 发送获得经验的事件
	 * @param Props
	 */
	void SendXPEvent(const FEffectProperties& Props);

	bool bTopOffHealth = false;
	bool bTopOffMana = false;
};
