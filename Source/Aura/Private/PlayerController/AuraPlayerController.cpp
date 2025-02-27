// 我自己用来学习的试作品 -- 来自icedragon500


#include "PlayerController/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit);
	if(!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	/**
	 * Cursor光标的追踪接口有以下几种情况
	 * a LastActor 和 ThisActor都是null  说明鼠标没有指到Enemy，不需要有操作
	 * b LastActor是Null 和 ThisActor有效 说明鼠标指到了Enemy，需要执行ThisActor打开高亮的操作
	 * c LastActor有效 和 ThisActor是Null 说明鼠标从Enemy身上移走了，需要执行LastActor关闭高亮的操作
	 * d 两个Actor都有效，这时候我们需要判断一下这两个是否一致，如果两个不一致，说明鼠标很快从一个敌人移动到另外一个敌人身上了，我们需要关闭LastActor高亮，打开ThisActor高亮
	 * e 如果一致，说明在鼠标一直在一个Enemy身上，不需要有操作
	 */

	if(LastActor == nullptr)//LastActor是无效的
	{
		if(ThisActor != nullptr)//ThisActor有效的
		{
			//B情况
			ThisActor->HighlightActor();
		}
		//else ThisActor也是无效 A情况
	}
	else //LastActor是有效的
	{
		if(ThisActor == nullptr)//ThisActor无效的
		{
			//C情况
			LastActor->UnHighlightActor();
		}
		else//ThisActor有效的
		{
			//D情况
			if(LastActor != ThisActor)
			{
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			//else E情况 就不写了
		}
	}
	

}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	/*
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
	}
	*/
}

void AAuraPlayerController::AbilityInputTagRelease(FGameplayTag InputTag)
{
	if(GetASC() == nullptr ) return;
	GetASC()->AbilityInputTagReleased(InputTag);
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if(GetASC() == nullptr ) return;
	GetASC()->AbilityInputTagHeld(InputTag);
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if(AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent =Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//当你非常确定某个条件必须为真，并且希望在违反该条件时立即停止程序以进行调试时，可以使用check
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}
	
	bShowMouseCursor = true;//是否显示鼠标光标
	DefaultMouseCursor = EMouseCursor::Default;//默认情况下显示的鼠标光标类型

	FInputModeGameAndUI InputModeDate;
	InputModeDate.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);//设置视窗的鼠标锁定行为
	InputModeDate.SetHideCursorDuringCapture(false);//是否在鼠标按下导致的临时鼠标捕获期间隐藏光标
	SetInputMode(InputModeDate);

	
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	/* 原有的增强输入绑定
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	*/

	//现在我们使用继承之后的方法来进行绑定
	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	
	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	AuraInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagRelease, &ThisClass::AbilityInputTagHeld);

	

	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Roatation = GetControlRotation();
	const FRotator YawRotation(0.f, Roatation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* ControllPawn = GetPawn<APawn>())
	{
		ControllPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControllPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
