// 我自己用来学习的试作品 -- 来自icedragon500


#include "UI/ViewModel/MVVM_LoadSlot.h"

void UMVVM_LoadSlot::InitializeSlot()
{
	const int32 WidgetSwitchIndex = SlotStatus.GetValue();
	SetWidgetSwitcherIndex.Broadcast(WidgetSwitchIndex);
}

void UMVVM_LoadSlot::SetLoadSlotName(FString SlotName)
{
	UE_MVVM_SET_PROPERTY_VALUE(LoadSlotName, SlotName);
}

void UMVVM_LoadSlot::SetPlayerName(FString inName)
{
	UE_MVVM_SET_PROPERTY_VALUE(PlayerName, inName);
}

void UMVVM_LoadSlot::SetPlayerLevel(int32 inLevel)
{
	UE_MVVM_SET_PROPERTY_VALUE(PlayerLevel, inLevel);
}

void UMVVM_LoadSlot::SetSlotIndex(int32 inIndex)
{
	UE_MVVM_SET_PROPERTY_VALUE(SlotIndex, inIndex);
}

void UMVVM_LoadSlot::SetMapName(FString inName)
{
	UE_MVVM_SET_PROPERTY_VALUE(MapName, inName);
}

void UMVVM_LoadSlot::SetSlotStatus(ESaveSlotStatus inStatus)
{
	SlotStatus = inStatus;
}

void UMVVM_LoadSlot::SetPlayerStartTag(FName inName)
{
	PlayerStartTag = inName;
}
