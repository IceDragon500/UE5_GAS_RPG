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

	/**
	 * 按下删除按钮，执行删除存档的逻辑
	 */
	UFUNCTION(BlueprintCallable)
	void DeleteButtonPressed();

	/**
	 * 按下游戏开始按钮，切换关卡到第一关
	 */
	UFUNCTION(BlueprintCallable)
	void PlayButtonPressed();

	void LoadData();

protected:
	

private:

	UPROPERTY()
	TMap<int32, UMVVM_LoadSlot*> LoadSlots;//存档位合集

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> LoadSlot_0;//界面上第一个存档位

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> LoadSlot_1;//界面上第二个存档位

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> LoadSlot_2;//界面上第三个存档位

	UPROPERTY()
	UMVVM_LoadSlot* SelectedSlot;//当前选中的存档位 yes, it can be a tobjectptr rather than a raw pointer 是的，它可以是一个对象而不是一个原始指针
	
};
