// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

class USaveGame;
class UMVVM_LoadSlot;
class UCharacterClassInfo;
class UAbilityInfo;
class ULoadScreenSaveGame;
/**
 * 
 */
UCLASS()
class AURA_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, Category = "属性设置|Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;

	UPROPERTY(EditDefaultsOnly, Category = "属性设置|Character Class Defaults")
	TObjectPtr<UAbilityInfo> AbilityInfo;

	void SaveSlotData(UMVVM_LoadSlot* LoadSlot, int32 SlotIndex);

	/**
	 * 读取存档
	 * @param SlotName 传入存档的名称
	 * @param SlotIndex 传入存档的序号
	 * @return 
	 */
	ULoadScreenSaveGame* GetSaveSlotData(const FString& SlotName, int32 SlotIndex) const;

	/**
	 * 删除存档
	 * @param SlotName 传入的存档名称
	 * @param SlotIndex 传入存档的序号
	 */
	static void DeleteSlot(const FString& SlotName, int32 SlotIndex);

	void TravelToMap(UMVVM_LoadSlot* Slot);

	UPROPERTY(EditDefaultsOnly, Category = "属性设置")
	TSubclassOf<USaveGame> LoadScreenSaveGameClass;

	//初始地图的名称
	UPROPERTY(EditDefaultsOnly, Category = "属性设置")
	FString DefaultMapName;

	//初始地图
	UPROPERTY(EditDefaultsOnly, Category = "属性设置")
	TSoftObjectPtr<UWorld> DefaultMap;

	/**
	 * 地图合集  组合方式为：
	 * 地图名称+地图
	 */
	UPROPERTY()
	TMap<FString, TSoftObjectPtr<UWorld>> Maps;

	/**
	 * 返回这个玩家从默认执行中生成的“最佳”玩家开始寻找一个随机的未被占用的位置
	 * @param Player 是我们为其选择playerstart的控制器
	 * @return 
	 */
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	
protected:

	virtual void BeginPlay() override;
private:
};
