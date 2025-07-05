// 我自己用来学习的试作品 -- 来自icedragon500


#include "UI/ViewModel/MVVM_LoadSlot.h"

void UMVVM_LoadSlot::InitializeSlot()
{
	SetWidgetSwitcherIndex.Broadcast(2);
}

void UMVVM_LoadSlot::SetLoadSlotName(FString SlotName)
{
	UE_MVVM_SET_PROPERTY_VALUE(LoadSlotName, SlotName);
}

void UMVVM_LoadSlot::SetPlayerName(FString inName)
{
	UE_MVVM_SET_PROPERTY_VALUE(PlayerName, inName);
}

void UMVVM_LoadSlot::SetSlotIndex(FString inIndex)
{
	UE_MVVM_SET_PROPERTY_VALUE(SlotIndex, inIndex);
}
