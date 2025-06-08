// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "AuraAbilityTypes.h"
#include "AuraGameplayAbility.h"
#include "Interaction/CombatInterface.h"
#include "AuraDamageGameplayAbility.generated.h"

UCLASS()
class AURA_API UAuraDamageGameplayAbility: public UAuraGameplayAbility
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

	/**
	 * 基于当前技能配置和上下文环境，构建伤害效果参数容器
	 * 
	 * 此函数是伤害系统的核心装配器，自动从以下来源收集数据：
	 * 1. 技能类默认属性（CDO）中配置的伤害参数
	 * 2. 当前技能实例的运行时状态（能力等级、施法者信息）
	 * 3. 目标角色的位置信息（用于计算物理效果方向）
	 * 
	 * 关键装配逻辑：
	 * - 基础伤害值通过曲线表(Damage)根据当前能力等级动态计算
	 * - 物理效果向量(DeathImpulse/KnockbackForce)自动计算为：
	 *     [从施法者指向目标的45度仰角方向] * [配置的力度标量]
	 * - 当目标无效时，物理向量保持为零向量（安全后备）
	 * 
	 * 使用场景：
	 * 1. 技能激活时装配参数：在ApplyDamage前调用
	 * 2. 伤害预览系统：结合UI显示预计伤害值
	 * 3. 服务器/客户端同步：生成网络可复制的参数包
	 * 
	 * 示例：
	 * // 在技能执行阶段调用
	 * const FDamageEffectParams Params = MakeDamageEffectParamsFromClassDefault(TargetActor);
	 * UAuraAbilitySystemLibrary::ApplyDamageEffect(Params);
	 * 
	 * @param TargetActor 伤害目标角色（可空）
	 * @return 完全装配的伤害参数容器，可直接传递给ApplyDamageEffect
	 * 
	 * @注意 函数内包含安全校验：当TargetActor无效时跳过方向计算
	 * @注意 物理向量计算使用标准化方向，确保力度标量保持设计值
	 * @注意 返回结构体包含蓝图可访问参数，支持视觉化编程
	 */
	UFUNCTION(BlueprintPure)
	FDamageEffectParams MakeDamageEffectParamsFromClassDefault(AActor* TargetActor = nullptr) const;

	UFUNCTION(BlueprintPure)
	float GetDamageAtLevel()  const;
	
protected:
	
	//设置对目标造成效果的GameEffect
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "属性设置|发射物属性设置")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	//303讲中被移除
	//UPROPERTY(EditDefaultsOnly, Category="属性设置|DamageType")
	//TMap<FGameplayTag, FScalableFloat> DamageTypes;

	UPROPERTY(EditDefaultsOnly, Category="属性设置|DamageType")
	FGameplayTag DamageType;

	UPROPERTY(EditDefaultsOnly, Category="属性设置|DamageType")
	FScalableFloat Damage;

	//Debuff概率
	UPROPERTY(EditDefaultsOnly, Category="属性设置|DamageType")
	float DebuffChance = 20;

	//Debuff伤害
	UPROPERTY(EditDefaultsOnly, Category="属性设置|DamageType")
	float DebuffDamage = 5.f;

	//Debuff伤害间隔时间
	UPROPERTY(EditDefaultsOnly, Category="属性设置|DamageType")
	float DebuffFrequency = 1.f;

	//Debuff持续时间
	UPROPERTY(EditDefaultsOnly, Category="属性设置|DamageType")
	float DebuffDuration = 5.f;

	//死亡后击飞尸体的冲击量
	UPROPERTY(EditDefaultsOnly, Category="属性设置|DamageType")
	float DeathImpulseMagnitude = 9000.f;
	
	//命中目标后对目标的冲击量
	UPROPERTY(EditDefaultsOnly, Category="属性设置|DamageType")
	float KnockbackForceMagnitude = 9000.f;

	//命中目标后击飞目标的概率
	UPROPERTY(EditDefaultsOnly, Category="属性设置|DamageType")
	float KnockbackChance = 0.f;

	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const;

	//303讲中被移除
	//float GetDamageByDamageType(float InLevel, const FGameplayTag& DamageType);
	
private:
	
};
