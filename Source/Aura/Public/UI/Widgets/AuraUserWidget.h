// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

	
protected:
	UFUNCTION(BlueprintImplementableEvent)//该功能可以在Blueprint或Level Blueprint图中实现
	void WidgetControllerSet();
private:
};
