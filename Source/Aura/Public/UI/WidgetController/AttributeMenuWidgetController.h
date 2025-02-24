#pragma once

#include "AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

UCLASS(BlueprintType, Blueprintable)
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
public:

	//将回调绑定到依赖项
	//继承自UAuraWidgetController
	virtual void BindCallbacksToDependencies() override;
	
	
	virtual void BroadcastInitialValues() override;
	
protected:
private:
	
};
