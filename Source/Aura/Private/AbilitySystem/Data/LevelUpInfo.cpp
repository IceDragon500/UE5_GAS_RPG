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
		 *他这里的设计是这样的
		 *我们用了一个变量在存储我们的经验值，这个经验是是我们的总共的经验值
		 *他不会因为升级归0
		 *所以 在经验表格中，LevelUpRequirement就表示了：我们拥有XXX经验时，是XXX等级
		 *例如
		 *进入游戏为1级
		 *升级至2级需要300
		 *升级至3级需要700
		 *升级至4级需要1100
		 *升级至5级需要1500
		 *当我们在1级击杀了一个怪物获得1000经验时，我们的计算如下：
		 *我们使用1000经验进行对比，发现到大于3级的700，小于4级的1100
		 *所以当前我们就是3级1000经验，还差100经验值到4级
		 *当我们又击杀了一个怪物获得300经验时，我们当前总共有1000+300=1300经验值
		 *我们再次按照上面的思路进行比较，1300大于4级的1100，小于5级的1500
		 *所以我们当前是4级1300经验值
		 *所以 在经验表格中，LevelUpRequirement是递增的，不应该一样
		 *
		 *而我们通常的思路是
		 *1级升级至2级 需要300
		 *2级升级至3级 需要400
		 *3级升级至4级 需要400（按照这个思路 这里是可以一样的）
		 *4级升级至5级 需要400
		 *当我们在1级击杀了一个怪物获得1000经验时，我们的计算如下：
		 *升级至2级需要300经验，从1000扣除300剩余700
		 *升级至3级需要400经验，从700扣除400剩余300
		 *升级至4级需要400经验，我们当前只有300经验
		 *所以最后的结果是：我们当前是3级300经验值，还差100经验升4级
		 *
		 *
		 *但是他现在这里还是有个问题是，如果我连续升级，只会给我一次
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
