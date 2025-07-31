// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
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
 * 指定的一个存档点Actor，我们需要保存他的FName，他的变换Transform，以及一个Bytes包含的数据结构
 * 在Bytes中，我们可以记录是否亮起 等等布尔信息
 * 将这些信息打包成一个结构体
 * 我们使用FName来区分每一个存档点
 * 重载了==运算符，用来判断两个结构体中保存的是否是同一个存档点
 * 甚至我们在这里 不仅可以保存存档前Actor，还可以保存其他类型的Actor
 */
USTRUCT(BlueprintType)
struct FSavedActor
{
	GENERATED_BODY()

	UPROPERTY()
	FName ActorName = FName();

	UPROPERTY()
	FTransform ActorTransform = FTransform();

	//从该Actor序列化的变量 进标记了保存游戏说明符的那些
	//Serialized variables from the actor, only those marked with SaveGame specifier
	UPROPERTY()
	TArray<uint8> Bytes;
};

inline bool operator==(const FSavedActor& Left, const FSavedActor& Right)
{
	return Left.ActorName == Right.ActorName;
}

/**
 * 将地图信息和地图上需要保存的Actor打包成一个结构体
 * 相当于保存了指定地图上存档点、开关门之类的所有信息
 */
USTRUCT(BlueprintType)
struct FSavedMap
{
	GENERATED_BODY()

	UPROPERTY()
	FString MapAssetName = FString();

	UPROPERTY()
	TArray<FSavedActor> SavedActors;
};

/**
 * 定义一个用来保存技能的结构体
 */
USTRUCT(BlueprintType)
struct FSavedAbility
{
	GENERATED_BODY()

	//技能类
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ClassDefaults")
	TSubclassOf<UGameplayAbility> GamepplayAbility;

	//技能对应的Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilityTag = FGameplayTag();

	//技能状态的Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilityStatus = FGameplayTag();

	//技能在按键上的Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilitySlot = FGameplayTag();

	//技能在按键上的Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilityType = FGameplayTag();

	//技能的等级
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 AbilityLevel = 0;
	
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
	FString PlayerName {FString("Default Name")};

	//地图名称，在游戏中的名称
	UPROPERTY()
	FString MapName {FString("Default MapName")};
	
	//地图名称，在UE资源里面的名称
	UPROPERTY()
	FString MapAssetName {FString("Default Map Asset Name")};

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

	//需要保存玩家等级
	UPROPERTY()
	int32 Save_PlayerLevel = 1;

	//需要保存玩家当前经验
	UPROPERTY()
	int32 Save_XP = 0;

	//需要保存玩家当前的属性点数
	UPROPERTY()
	int32 Save_SpellPoints = 0;

	//需要保存玩家当前的技能点数
	UPROPERTY()
	int32 Save_AttributePoints = 0;

	//需要保存玩家当前基础属性值
	UPROPERTY()
	float Save_Strength = 0;

	//需要保存玩家当前基础属性值
	UPROPERTY()
	float Save_Intelligence = 0;

	//需要保存玩家当前基础属性值
	UPROPERTY()
	float Save_Resilience = 0;

	//需要保存玩家当前基础属性值
	UPROPERTY()
	float Save_Vigor = 0;

	//需要保存玩家当前技能组（队列）
	UPROPERTY()
	TArray<FSavedAbility> SavedAbilities;

	//需要保存当前地图上的一系列信息
	UPROPERTY()
	TArray<FSavedMap> SavedMaps;

	/**
	 * 通过地图名称返回地图本身的引用
	 * @param InMapName 需要查询的地图名称
	 * @return 返回查找到的地图引用
	 */
	FSavedMap GetSavedMapWithMapName(const FString& InMapName);
	
	bool HasMap(const FString& InMapName);//检查当前保存的地图信息中，是否有指定的地图
	
protected:

private:

	
};
