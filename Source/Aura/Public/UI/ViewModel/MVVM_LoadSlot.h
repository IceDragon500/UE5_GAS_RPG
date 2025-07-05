// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Game/LoadScreenSaveGame.h"
#include "MVVM_LoadSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetWidgetSwitcherIndex, int32, WidgetSwitcherIndex);

/**
 * UMVVM_LoadSlot表示单独的一个存档数据
 * 我们在一个单独的存档上，有一些数据，我们需要在存档界面上显示PlayerName Level Map这些信息
 * 我们在这个类里面设置这些信息的操作方式
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

	void SetSlotStatus(ESaveSlotStatus inStatus);

protected:




private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess=true))
	FString LoadSlotName = FString();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess=true))
	FString PlayerName = FString();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess=true))
	FString SlotIndex = FString();

	UPROPERTY(meta=(AllowPrivateAccess=true))
	TEnumAsByte<ESaveSlotStatus> SlotStatus;

	
};
