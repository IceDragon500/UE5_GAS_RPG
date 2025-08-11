// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

//Effect应用策略
UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,//在重叠开始的时候应用
	ApplyOnEndOverlap,//在重叠结束的时候应用
	DoNotApply//不应用
};

//Effect移除策略
UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemovalOnEndOverlap,//在重叠结束的时候移除
	DoNotRemoval//不移除
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

public:

	AAuraEffectActor();

	virtual void Tick(float DeltaSeconds) override;

	//这里是举例说明 如果出入引用 并且在蓝图左侧，需要加入UPARAM(ref)来表示将引用是为参数

	UFUNCTION(BlueprintCallable)
	void SetPlayerName(FString PlayerName, int32 PlayerLevel);

	UFUNCTION(BlueprintCallable)
	void SetPlayerLevel(UPARAM(ref)FString& PlayerName, int32 PlayerLevel);


protected:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	FVector CalculatedLocation;

	UPROPERTY(BlueprintReadWrite)
	FRotator CalculatedRotation;

	//是否触发旋转
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="属性设置", meta = (DisplayName = "是否触发旋转"))
	bool bRotates = false;

	//旋转速率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="属性设置")
	float RotationRate = 45.f;

	//是否进行正弦上下波动
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="属性设置", meta = (DisplayName = "是否进行正弦上下波动"))
	bool bSinusoidalMovement = false;

	/**
	 * 开始进行正弦上下波动
	 */
	UFUNCTION(BlueprintCallable)
	void StartSinusoidalMovement();

	/**
	 * 开始进行旋转
	 */
	UFUNCTION(BlueprintCallable)
	void StartRotation();
	
	//正弦上下波动幅度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="属性设置", meta = (DisplayName = "正弦上下波动幅度"))
	float SineAmplitude = 1.f;

	//正弦上下波动周期
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="属性设置", meta = (DisplayName = "正弦上下波动周期度"))
	float SinePeriodConstant = 1.f; //2π

	//道具的初始位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="属性设置")
	FVector InitialLocation = FVector(0, 0, 0);

	//将Effect应用给目标
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);


	//开始重叠的方法
	//这段对应在蓝图中使用了蓝图的调用方法
	//这个用在了火焰伤害上，放置之后，在一个范围内持续造成伤害
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	//结束重叠的方法
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
	//是否在效果结束后摧毁
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="属性设置", meta = (DisplayName = "是否在效果结束后摧毁"))
	bool bDestroyOnEffectApplication = false;

	//是否对敌人应用这个效果
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="属性设置", meta = (DisplayName = "是否对敌人应用这个效果"))
	bool bApplyEffectsToEnemies = false;

	//直接作用的GameplayEffect
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="属性设置")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	//设置直接作用的
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="属性设置" )
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	//周期作用的GameplayEffect
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="属性设置")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="属性设置" )
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	//无限持续作用的GameplayEffect
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="属性设置")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="属性设置" )
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="属性设置" )
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemovalOnEndOverlap;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	//用来这是MakeOutgoingSpec中的Level
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="属性设置" )
	float ActorLevel = 1.f;

private:


	//用来更新正弦运动的运行时间
	float RunningTime = 0.f;

	void ItemMovement(float DeltaTime);
};
