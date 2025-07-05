// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MVVM_LoadSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetWidgetSwitcherIndex, int32, WidgetSwitcherIndex);

/**
 * 
 */
UCLASS()
class AURA_API UMVVM_LoadSlot : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable)
	FSetWidgetSwitcherIndex SetWidgetSwitcherIndex;

	/**
	 * 初始化Slot
	 */
	void InitializeSlot();
	
	void SetLoadSlotName(FString SlotName);
	FString GetLoadSlotName() const { return LoadSlotName; }
	
	void SetPlayerName(FString inName);
	FString GetPlayerName() const { return PlayerName; }
	
	void SetSlotIndex(FString inIndex);
	FString GetSlotIndex() const { return SlotIndex; }

protected:




private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess=true))
	FString LoadSlotName = FString();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess=true))
	FString PlayerName = FString();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess=true))
	FString SlotIndex = FString();

	
};
