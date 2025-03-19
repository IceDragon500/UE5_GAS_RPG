// 我自己用来学习的试作品 -- 来自icedragon500


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));
	
}



void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	//忽略标记为Enemy的敌人
	if(TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies) return;
	
	/* 使用接口获得AbilitySystemComponent的方法
	IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(Target);

	if(ASCInterface)
	{
		ASCInterface->GetAbilitySystemComponent();
	}
	*/

	//尝试获取进入区域的角色身上是否有ability system component
	//这里展示了不用接口的方式获得AbilitySystemComponent的方法
	//以下是将EffectSpec设置给目标Target的ASC的标准方法：

	//我们获取到目标的ASC
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);//尝试查找角色上的能力系统组件，将使用AbilitySystemInterface或退回到组件搜索
	if(TargetASC == nullptr) return;

	//检查传入的GE文件是否有效，这个需要注意设置蓝图上的GameplayEffect文件，如果没有设置这里会报错
	check(GameplayEffectClass);

	
	//1、我们创建一个FGameplayEffectContextHandle
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	
	//2、我们创建一个FGameplayEffectSpecHandle，我们通过TargetASC->MakeOutgoingSpec来获取到这个
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
	
	//3、我们需要用ApplyGameplayEffectSpecToSelf将EffectSpec设置在Target的ASC上
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	//我们从数据引用的角度去查看这个EffectSpecHandle的DurationType是否是Infinite
	//就是检查一下这个EffectSpec是否设置的是无限时长的效果
	//等于是用C++的方式去寻找这个属性在编辑器里面是怎么设置的
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	
	//我们保存一下指定角色的TargetASC和ActiveEffectHandle，相当于就是把进入这个区域的不同aura character保存了下来 这样避免了重复计算
	if(bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemovalOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}

	if(!bIsInfinite)
	{
		Destroy();
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	//忽略标记为Enemy的敌人
	if(TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies) return;
	
	if(InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if(InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	//忽略标记为Enemy的敌人
	if(TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies) return;
	
	if(InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if(InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	//当离开区域的时候移除角色相关效果 GameplayEffect
	if(InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemovalOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if(!IsValid(TargetASC)) return;

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for(TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
		{
			//对于每个HandlePair，如果它的Value（即UAbilitySystemComponent*）与TargetASC相匹配
			//则调用RemoveActiveGameplayEffect方法从目标能力系统组件中移除相应的游戏效果，并将该效果句柄添加到HandlesToRemove列表中
			if(TargetASC == HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		//遍历HandlesToRemove列表，从中移除所有已标记为移除的效果句柄，确保这些效果不会继续作用于目标角色或对象
		for(FActiveGameplayEffectHandle Handle : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}
