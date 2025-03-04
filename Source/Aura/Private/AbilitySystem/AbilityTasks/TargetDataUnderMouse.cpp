// 我自己用来学习的试作品 -- 来自icedragon500


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();

	if(bIsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(
			SpecHandle,
			ActivationPredictionKey).AddUObject(this, &UTargetDataUnderMouse::OnTargetDataReplicatedCallback);

		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
		if(!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
	
	
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	// 1. 创建预测窗口（减少网络延迟带来的视觉问题）
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	
	// 2. 获取玩家控制器及鼠标命中结果
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	// 3. 封装目标数据
	FGameplayAbilityTargetDataHandle DataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = CursorHit;
	DataHandle.Add(Data);

	FGameplayTag ApplicationTag;

	//ServerSetReplicatedTargetData 是 Unreal Engine 5 (UE5) 中用于网络游戏开发的一个函数，
	//特别与能力系统（Gameplay Ability System, 简称 GAS）相关。
	//这个函数的主要作用是将客户端上的目标数据复制到服务器，确保所有参与游戏的客户端和服务器端保持同步。
	
	//AbilityHandle: 这是一个处理标识符，用来唯一标识一个特定的游戏能力（ability）。通过这个句柄，可以对游戏中具体的能力进行操作。
	//AbilityOriginalPredictionKey: 预测键值，用于解决网络游戏中可能出现的命令执行顺序问题。它帮助在不同的客户端之间协调能力的执行顺序，以确保游戏状态的一致性。
	//ReplicatedTargetDataHandle: 这是包含目标数据的句柄。在使用GAS时，当你选择或指定一个目标（比如敌人），这些信息被打包进这个句柄中，并从客户端发送到服务器。
	//ApplicationTag: 标签，用于标记该能力的应用场景或者条件。这有助于根据标签快速查找或过滤能力。
	//CurrentPredictionKey: 当前预测键值，与上述的原始预测键值类似，但代表的是当前请求的预测键值。

	// 4. 发送数据到服务器
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		ApplicationTag,AbilitySystemComponent->ScopedPredictionKey
		);

	//ShouldBroadcastAbilityTaskDelegates 是 Gameplay Ability System 插件中用于确保能力（ability）任务的委托（delegates）仅在特定条件下广播的一个方法。
	//这个方法主要用于防止当能力或能力任务已经结束或者不再活动时还尝试执行某些操作，从而避免潜在的错误和不一致的游戏状态。

	//返回值: bool 类型，表示是否应该广播委托。如果返回 true，则意味着可以安全地广播；如果返回 false，则表明不应该进行广播，通常是因为能力已经不再是激活状态。
	//使用场景: 在实现自定义能力或能力任务时，尤其是在你计划触发一些事件或回调时，你应该首先调用 ShouldBroadcastAbilityTaskDelegates() 来确认当前能力仍处于活动状态。这有助于保证只有在适当的情况下才会执行后续代码，维护了游戏逻辑的一致性和稳定性。

	// 5. 广播委托（本地立即响应）
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
	
}

void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,
	FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
