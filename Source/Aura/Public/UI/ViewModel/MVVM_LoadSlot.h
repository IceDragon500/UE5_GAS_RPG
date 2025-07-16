// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Game/LoadScreenSaveGame.h"
#include "MVVM_LoadSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetWidgetSwitcherIndex, int32, WidgetSwitcherIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnableSelectSlotButton, bool, bEnable);

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

	UPROPERTY(BlueprintAssignable)
	FEnableSelectSlotButton EnableSelectSlotButton;

	/**
	 * 初始化Slot
	 */
	void InitializeSlot();
	
	void SetLoadSlotName(FString SlotName);
	FString GetLoadSlotName() const { return LoadSlotName; }
	
	void SetPlayerName(FString inName);
	FString GetPlayerName() const { return PlayerName; }

	void SetPlayerLevel(int32 inLevel);
	int32 GetPlayerLevel() const { return PlayerLevel; }
	
	void SetSlotIndex(int32 inIndex);
	int32 GetSlotIndex() const { return SlotIndex; }

	void SetMapName(FString inName);
	FString GetMapName() const { return MapName; }

	void SetSlotStatus(ESaveSlotStatus inStatus);

	void SetPlayerStartTag(FName inName);
	FName GetPlayerStartTag() const { return PlayerStartTag; }

protected:




private:

	//被保存的存档名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess=true))
	FString LoadSlotName = FString();

	//保存的角色名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess=true))
	FString PlayerName = FString();

	//保存的角色名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess=true))
	int32 PlayerLevel = 1;

	//保存的存档位序号
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess=true))
	int32 SlotIndex = 0;

	//保存的地图名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess=true))
	FString MapName = FString();

	/**
	 * 存档位的状态
	 * 0：空存档  1：输入名称 2：已有存档
	 */
	UPROPERTY(meta=(AllowPrivateAccess=true))
	TEnumAsByte<ESaveSlotStatus> SlotStatus;
	
	FName PlayerStartTag = FName();

	
};
