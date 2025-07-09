// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LoadScreenSaveGame.generated.h"


UENUM(BlueprintType)
enum ESaveSlotStatus
{
	Vacant,  //空
	EnterName, //输入名称
	Taken //已读取
};

/**
 * ULoadScreenSaveGame用来处理数据保存，即 这里是具体的存档内容
 * 需要从这个读取之后 传递给MVVM的类，再由那个类，传递给界面
 */
UCLASS()
class AURA_API ULoadScreenSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString SlotName = FString();

	UPROPERTY()
	int32 SlotIndex = 0;

	UPROPERTY()
	FString PlayerName = FString("Default Name");

	UPROPERTY()
	FString MapName = FString();

	UPROPERTY()
	TEnumAsByte<ESaveSlotStatus> SaveSlotStatus = Vacant;

	UPROPERTY()
	FName PlayerStartTag;
	
protected:

private:

	
};
