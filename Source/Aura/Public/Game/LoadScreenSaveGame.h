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
	//存档的文件名称
	UPROPERTY()
	FString SlotName = FString();

	//存档的序号，从0开始
	UPROPERTY()
	int32 SlotIndex = 0;

	//玩家创建的角色名称
	UPROPERTY()
	FString PlayerName = FString("Default Name");

	//地图名称
	UPROPERTY()
	FString MapName = FString();

	//存档的状态
	UPROPERTY()
	TEnumAsByte<ESaveSlotStatus> SaveSlotStatus = Vacant;

	//是否是首次加载
	UPROPERTY()
	bool bFirstTimeLoadIn = true;

	//玩家起点的tag
	UPROPERTY()
	FName PlayerStartTag;

	/* player 需要保存的玩家数据*/

	//
	UPROPERTY()
	int32 Save_PlayerLevel = 1;

	//
	UPROPERTY()
	int32 Save_XP = 0;

	//
	UPROPERTY()
	int32 Save_SpellPoints = 0;

	//
	UPROPERTY()
	int32 Save_AttributePoints = 0;

	//
	UPROPERTY()
	float Save_Strength = 0;

	//
	UPROPERTY()
	float Save_Intelligence = 0;

	//
	UPROPERTY()
	float Save_Resilience = 0;

	//
	UPROPERTY()
	float Save_Vigor = 0;
	
	
protected:

private:

	
};
