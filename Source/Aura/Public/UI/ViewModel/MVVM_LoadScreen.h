// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MVVM_LoadSlot.h"
#include "MVVM_LoadScreen.generated.h"

/**
 *BlueprintPure
 * 该函数不会以任何方式影响所属对象，并且可以在蓝图或级别蓝图图中执行
 */
UCLASS()
class AURA_API UMVVM_LoadScreen : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	void InitializeLoadSlots();

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
