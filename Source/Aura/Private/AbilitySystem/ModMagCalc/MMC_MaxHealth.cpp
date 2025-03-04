// 我自己用来学习的试作品 -- 来自icedragon500


#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	//定义对Vigor属性的捕获规则

	//1. 绑定到UAuraAttributeSet中的Vigor属性
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	//2. 从Target（效果施加的目标，通常是角色自身）捕获属性值
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	//3. 设为false表示实时捕获属性值，而非快照。
	VigorDef.bSnapshot = false;

	//注册需要捕获的属性列表，这里是VigorDef
	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from souce and target
	//从源和目标收集标签

	// 1. 获取标签和评估参数
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	// 2. 捕获 Vigor 属性值
	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluateParameters, Vigor);
	Vigor = FMath::Max<float>(Vigor, 0.0f);

	// 3. 获取玩家等级
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	// 4. 计算公式
	return 80.f + 2.5f * Vigor + 10.f * PlayerLevel;

}
