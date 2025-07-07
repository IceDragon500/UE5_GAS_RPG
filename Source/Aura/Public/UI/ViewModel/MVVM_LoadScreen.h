// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MVVM_LoadSlot.h"
#include "MVVM_LoadScreen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSlotSelected);

/**
 * UMVVM_LoadScreen 用来处理存档界面上的数据操作逻辑
 * 我们用TObjectPtr<UMVVM_LoadSlot> LoadSlot_0  来表示界面上设置的3个存档对象
 * 用Slot为其编号，从0至2，表示3个存档
 * 使用void NewSlotButtonPressed() void NewGameButtonPressed() void SelectSlotButtonPressed()
 * 来表示存档界面上三个按钮按下之后的逻辑
 */
UCLASS()
class AURA_API UMVVM_LoadScreen : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	void InitializeLoadSlots();

	UPROPERTY(BlueprintAssignable)
	FSlotSelected SelectSlot;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMVVM_LoadSlot> LoadSlotViewModelClass;

	UFUNCTION(BlueprintPure)
	UMVVM_LoadSlot* GetLoadSlotViewModelByIndex(int32 Index);

	/**
	 * 按钮功能：创建新的存档
	 * @param EnteredName 传入角色名称
	 * @param Slot 传入Slot的序号
	 */
	UFUNCTION(BlueprintCallable)
	void NewSlotButtonPressed(UPARAM(ref)FString& EnteredName, int32 Slot);

	/**
	 * 按钮功能：新游戏按钮
	 * @param Slot 
	 */
	UFUNCTION(BlueprintCallable)
	void NewGameButtonPressed(int32 Slot);

	/**
	 * 按钮功能：选择存档按钮
	 * @param Slot 
	 */
	UFUNCTION(BlueprintCallable)
	void SelectSlotButtonPressed(int32 Slot);

	void LoadData();

protected:
	

private:

	UPROPERTY()
	TMap<int32, UMVVM_LoadSlot*> LoadSlots;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> LoadSlot_0;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> LoadSlot_1;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> LoadSlot_2;
	
};
