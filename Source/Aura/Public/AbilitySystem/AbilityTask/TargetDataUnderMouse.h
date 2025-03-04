// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature, const FGameplayAbilityTargetDataHandle&, DataHandle);



/**
 * 
 */
UCLASS()
class AURA_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()

public:

	//BlueprintCallable: 这个关键字意味着该函数可以在蓝图中被调用。这意味着你可以通过蓝图编辑器来使用这个函数，极大地增强了开发的灵活性
	//Category = "Ability Task": 设置了该函数在蓝图中的分类
	//HidePin = "OwningAbility"：指示在蓝图中隐藏名为 OwningAbility 的输入引脚。这是为了简化蓝图的视觉复杂度。
	//DefaultToSelf = "OwningAbility"：表示如果未指定 OwningAbility 参数，则默认使用调用该函数的对象自身作为此参数的值
	//BlueprintInternalUseOnly：表明该函数仅打算在内部蓝图逻辑中使用，并不会暴露给最终用户或外部系统
	//DisplayName  如果希望函数在蓝图中不使用函数名作为名称，可以使用这个来重新命名
	
	UFUNCTION(BlueprintCallable, Category = "Ability Task", meta = (DisplayName = "TargetDataUnderMouse", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = true))
	static UTargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature ValidData;
	
protected:
private:

	virtual void Activate() override;

	//预测窗口 (FScopedPredictionWindow)：用于客户端预测，减少延迟带来的卡顿。
	//获取鼠标命中结果：通过 GetHitResultUnderCursor 获取光标下的碰撞信息。
	//封装数据：将命中结果包装为 FGameplayAbilityTargetDataHandle。
	//服务器同步：通过 ServerSetReplicatedTargetData 将数据发送到服务器。
	//委托广播：本地客户端立即触发委托，处理视觉或逻辑反馈。
	void SendMouseCursorData();

	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag);
	
};
