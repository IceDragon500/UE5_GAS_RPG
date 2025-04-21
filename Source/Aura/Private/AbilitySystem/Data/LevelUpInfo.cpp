// 我自己用来学习的试作品 -- 来自icedragon500


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXp(int32 XP) const
{
	int32 Level = 1;
	bool bSearching = true;
	while (bSearching)
	{
		if (LevelUpInformation.Num() - 1 <= Level) return Level;

		/**
		 * 他这里有个问题
		 * 他这里用传入的经验值，循环对比每个等级需要的经验值，如果传入的经验值大于这个等级需要的经验值
		 * 他就进入下个循环检查下一个等级的经验值
		 *
		 * 例如 我从1级到11级，每级经验值都需要1800
		 * 这个时候我传入1800经验，按照我们预期的设计，应该会从1级升级到2级
		 * 但是按照他这个算法的逻辑，应该传入的经验值1800 都 >= 每级的需求，所以会一直循环，直至最后一级
		 * 这个不符合我们的需求
		 *
		 * 我们的需求是，传入的经验值+当前有的经验值，如果大于当前升级所需的经验值
		 * 需要先升级，然后扣除升级需要的经验值，再进入下一次循环进行对比
		 */
		if (XP >= LevelUpInformation[Level].LevelUpRequirement)
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}
	}
	return Level;
}


int32 ULevelUpInfo::FindLevelForXp_2(int32 XP) const
{
	int32 Level = 1;
	int32 TotalRequiredXP = 0; // 累计经验值

	// 从索引 1 开始遍历（对应等级 1→2 的需求）
	for (int32 CurrentIndex = 1; CurrentIndex < LevelUpInformation.Num(); CurrentIndex++)
	{
		// 累加当前等级的独立需求值
		TotalRequiredXP += LevelUpInformation[CurrentIndex].LevelUpRequirement;

		// 检查总 XP 是否足够升到下一级
		if (XP >= TotalRequiredXP)
		{
			Level++;
		}
		else
		{
			break; // 经验不足，终止升级
		}
	}

	return Level;
}
