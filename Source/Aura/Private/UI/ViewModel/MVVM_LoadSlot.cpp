// 我自己用来学习的试作品 -- 来自icedragon500


#include "UI/ViewModel/MVVM_LoadSlot.h"

void UMVVM_LoadSlot::InitializeSlot()
{
	SetWidgetSwitcherIndex.Broadcast(1);
}

void UMVVM_LoadSlot::SetLoadSlotName(FString slotName)
{
	UE_MVVM_SET_PROPERTY_VALUE(LoadSlotName, slotName);
}
