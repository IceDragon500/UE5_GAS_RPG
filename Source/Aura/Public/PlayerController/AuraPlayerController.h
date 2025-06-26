// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "Actor/MagicCircle.h"
#include "GameFramework/PlayerController.h"
#include "Input/AuraInputConfig.h"
#include "UI/Widgets/DamageTextComponent.h"

#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class UAuraAbilitySystemComponent;
class USplineComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();

	//专门用于处理与玩家输入相关的逻辑
	//只在玩家控制器活跃时才会被调用
	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool bBlockHit, bool bCriticalHit);

	UFUNCTION(BlueprintCallable)
	void ShowMagicCircle(UMaterialInterface* DecalMaterial = nullptr);
	
	UFUNCTION(BlueprintCallable)
	void HideMagicCircle();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


	
	
private:

	UPROPERTY(EditAnywhere, Category="属性设置|输入设置")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category="属性设置|输入设置")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="属性设置|输入设置")
	TObjectPtr<UInputAction> ShiftAction;

	void ShiftPressed() { IsShiftPressed = true; };
	void ShiftReleased() { IsShiftPressed = false; };
	//Shift键是否按下
	bool IsShiftPressed = false;

	void Move(const FInputActionValue& InputActionValue);

	//鼠标指向追踪的逻辑
	void CursorTrace();

	//当前鼠标指向的目标
	IEnemyInterface* LastActor;
	//鼠标最后一次指向的目标
	IEnemyInterface* ThisActor;

	FHitResult CursorHit;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagRelease(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
	UPROPERTY(EditDefaultsOnly, Category="属性设置|输入设置")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UAuraAbilitySystemComponent* GetASC();

	//保存鼠标点击的位置
	FVector CachedDestinaion = FVector::ZeroVector;

	//
	float FollowTime = 0.f;

	//短按的时间范围
	float ShortPressThreshold = 0.5f;

	//是否在自动行走
	bool bAutoRunning = false;

	bool bTargeting = false;

	//自动行走的半径
	UPROPERTY(EditDefaultsOnly, Category="属性设置|自动行走")
	float AutoRunAcceptanceRadius = 50.f;

	//标记行走的样条线
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	//鼠标点击特效
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraSystem> ClickNiagaraSystem;

	void AutoRun();

	//设置伤害文本显示的类
	UPROPERTY(EditDefaultsOnly, Category="属性设置|伤害文本")
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;

	//设置鼠标上显示的贴画类 用来表示技能释放的范围
	UPROPERTY(EditDefaultsOnly, Category="属性设置|技能范围显示")
	TSubclassOf<AMagicCircle> MagicCircleClass;

	UPROPERTY()
	TObjectPtr<AMagicCircle> MagicCircle;

	void UpdateMagicCircleLocation();
	
};
