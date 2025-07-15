// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//将获得的经验添加给PlayerState中的Level值
	UFUNCTION(BlueprintNativeEvent)
	void AddToXP(int32 InXP);

	//获取当前经验值
	UFUNCTION(BlueprintNativeEvent)
	int32 GetXP() const;

	//通过经验来判断当前等级
	UFUNCTION(BlueprintNativeEvent)
	int32 FindLevelForXP(int32 InXP) const ;

	//通过等级查询对应的属性点数量
	UFUNCTION(BlueprintNativeEvent)
	int32 GetAttributePointsReward(int32 Level) const;

	//通过等级查询对应的技能点数量
	UFUNCTION(BlueprintNativeEvent)
	int32 GetSpellPointsReward(int32 Level) const;

	//给角色添加等级
	UFUNCTION(BlueprintNativeEvent)
	void AddToPlayerLevel(int32 InPlayerLevel);

	//得到当前角色的剩余属性点数
	UFUNCTION(BlueprintNativeEvent)
	int32 GetAttributePoints() const;

	//给角色添加属性点数
	UFUNCTION(BlueprintNativeEvent)
	void AddToAttributePoints(int32 InAttributePoints);

	//给角色添加技能点数
	UFUNCTION(BlueprintNativeEvent)
	void AddToSpellPoints(int32 InSpellPoints);

	//得到当前角色的剩余的技能点数
	UFUNCTION(BlueprintNativeEvent)
	int32 GetSpellPoints() const;

	//处理角色升级时的一些逻辑，比如播放特效，增加属性点之类的逻辑
	UFUNCTION(BlueprintNativeEvent)
	void LevelUp();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowMagicCircle(UMaterialInterface* DecalMaterial = nullptr);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HideMagicCircle();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SaveProgress(const FName& CheckpointTag);

};
