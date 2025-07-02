// 我自己用来学习的试作品 -- 来自icedragon500


#include "UI/HUD/LoadScreenHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/ViewModel/MVVM_LoadScreen.h"
#include "UI/Widgets/LoadScreenWidget.h"

void ALoadScreenHUD::BeginPlay()
{
	Super::BeginPlay();

	LoadScreenViewModel = NewObject<UMVVM_LoadScreen>(this, LoadScreenViewModelClass);
	LoadScreenViewModel->InitializeLoadSlots();

	LoadScreenWidget = CreateWidget<ULoadScreenWidget>(GetWorld(), LoadScreenWidgetClass);
	LoadScreenWidget->AddToViewport();

	LoadScreenWidget->BlueprintInitializeWidget();

	

	//以下内容教程里面没有
	//这段是对应在蓝图里面 GetPlayerController->SetInputModeUIOnly 这两个节点的逻辑
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetWidgetToFocus(LoadScreenWidget->TakeWidget());
	GetOwningPlayerController()->SetInputMode(InputMode);
	GetOwningPlayerController()->SetShowMouseCursor(true);

	

	
	
}
