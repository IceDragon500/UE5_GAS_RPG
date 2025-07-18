// 我自己用来学习的试作品 -- 来自icedragon500


#include "UI/ViewModel/MVVM_LoadScreen.h"

#include "Game/AuraGameInstance.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UMVVM_LoadScreen::InitializeLoadSlots()
{
	LoadSlot_0 = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
	LoadSlot_0->SetLoadSlotName(FString("LoadSlot_0"));
	LoadSlot_0->SetSlotIndex(0);
	LoadSlots.Add(0, LoadSlot_0);
	
	LoadSlot_1 = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
	LoadSlot_1->SetLoadSlotName(FString("LoadSlot_1"));
	LoadSlot_1->SetSlotIndex(1);
	LoadSlots.Add(1, LoadSlot_1);
	
	LoadSlot_2 = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
	LoadSlot_2->SetLoadSlotName(FString("LoadSlot_2"));
	LoadSlot_2->SetSlotIndex(2);
	LoadSlots.Add(2, LoadSlot_2);
}

UMVVM_LoadSlot* UMVVM_LoadScreen::GetLoadSlotViewModelByIndex(int32 Index)
{
	return LoadSlots.FindChecked(Index);
}

void UMVVM_LoadScreen::NewSlotButtonPressed(FString& EnteredName, int32 Slot)
{
	AAuraGameModeBase* AuraGameMode =Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this)) ;
	LoadSlots[Slot]->SetMapName(AuraGameMode->DefaultMapName);
	LoadSlots[Slot]->SetPlayerName(EnteredName);
	LoadSlots[Slot]->SetPlayerLevel(1);
	LoadSlots[Slot]->SetSlotStatus(Taken);
	LoadSlots[Slot]->SetPlayerStartTag(AuraGameMode->DefaultPlayerStartTag);

	AuraGameMode->SaveSlotData(LoadSlots[Slot], Slot);
	LoadSlots[Slot]->InitializeSlot();

	UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(AuraGameMode->GetGameInstance());
	if (AuraGameInstance)
	{
		AuraGameInstance->LoadSlotName = LoadSlots[Slot]->GetLoadSlotName();
		AuraGameInstance->LoadSlotIndex = LoadSlots[Slot]->GetSlotIndex();
		AuraGameInstance->PlayerStartTag = AuraGameMode->DefaultPlayerStartTag;
	}
}

void UMVVM_LoadScreen::NewGameButtonPressed(int32 Slot)
{
	LoadSlots[Slot]->SetWidgetSwitcherIndex.Broadcast(1);
}

void UMVVM_LoadScreen::SelectSlotButtonPressed(int32 Slot)
{
	SelectSlot.Broadcast();
	
	for (const TTuple<int32, UMVVM_LoadSlot*> LoadSlot : LoadSlots)
	{
		if (LoadSlot.Key == Slot)
		{
			LoadSlot.Value->EnableSelectSlotButton.Broadcast(false);
		}
		else
		{
			LoadSlot.Value->EnableSelectSlotButton.Broadcast(true);
		}
	}

	SelectedSlot = LoadSlots[Slot];
	
}

void UMVVM_LoadScreen::DeleteButtonPressed()
{
	if (IsValid(SelectedSlot))
	{
		AAuraGameModeBase::DeleteSlot(SelectedSlot->GetLoadSlotName(), SelectedSlot->GetSlotIndex());
		SelectedSlot->SetSlotStatus(Vacant);
		SelectedSlot->InitializeSlot();
		SelectedSlot->EnableSelectSlotButton.Broadcast(true);
	}
	
}

void UMVVM_LoadScreen::PlayButtonPressed()
{
	AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));
	UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(AuraGameMode->GetGameInstance());
	AuraGameInstance->PlayerStartTag = SelectedSlot->GetPlayerStartTag();
	AuraGameInstance->LoadSlotName = SelectedSlot->GetLoadSlotName();
	AuraGameInstance->LoadSlotIndex = SelectedSlot->GetSlotIndex();
	
	if (IsValid(SelectedSlot))
	{
		AuraGameMode->TravelToMap(SelectedSlot);
	}
	
	
}

void UMVVM_LoadScreen::LoadData()
{
	AAuraGameModeBase* AuraGameModeBase = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));
	for (const TTuple<int32, UMVVM_LoadSlot*> LoadSlot : LoadSlots)
	{
		ULoadScreenSaveGame* SaveObject = AuraGameModeBase->GetSaveSlotData(LoadSlot.Value->GetLoadSlotName(), LoadSlot.Key);

		const FString PlayerName = SaveObject->PlayerName;
		const FString MapName = SaveObject->MapName;
		TEnumAsByte<ESaveSlotStatus> SaveSlotStatus = SaveObject->SaveSlotStatus;
		const FName PlayerStartTag = SaveObject->PlayerStartTag;
		const int32 PlayerLevel = SaveObject->Save_PlayerLevel;
		
		if (SaveObject)
		{
			LoadSlot.Value->SetSlotStatus(SaveSlotStatus);
			LoadSlot.Value->SetPlayerName(PlayerName);
			LoadSlot.Value->InitializeSlot();
			LoadSlot.Value->SetMapName(MapName);
			LoadSlot.Value->SetPlayerStartTag(PlayerStartTag);
			LoadSlot.Value->SetPlayerLevel(PlayerLevel);
		}
		
	}
}

