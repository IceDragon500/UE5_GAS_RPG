// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

/**
 * 继承自GameplayAbility的Aura子类
 * 在这里实现了读取技能描述的功能
 */
UCLASS()
class AURA_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="属性设置|Input")
	FGameplayTag StartupInputTag;

	//获取当前技能描述
	virtual FString GetDescription(int32 Level);

	//获取下一级的技能描述
	virtual FString GetNextLevelDescription(int32 Level);

	//当技能被锁定时的描述
	static FString GetLockedDescription(int32 Level);

protected:
	
	float GetManaCost(int32 InLevel = 1) const;
	
	float GetCooldown(int32 InLevel = 1) const;

private:
	
};


/* 99课
*Things Not to Use:
不能使用的东西：

Replication Policy
复制策略

Useless. Don't use it. Refer to Epic's Ability System Questions for an explanation from Epic.
无用。不要使用。请参阅 “Epic的能力系统问题”，查看史诗的解释。

Gameplay Abilities are replicated from Server to owning Client already.
游戏能力已从服务器复制到拥有该能力的客户端。

Note: Gameplay Abilities don't run on Simulated Proxies (use GEs and GCs)
注意：游戏能力不会在模拟代理（使用 GE 和 GC）上运行。

Server Respects Remote Ability Cancellation
服务器尊重远程能力取消

Means when the local Client's ability ends, the server's will end
意味着当本地客户端的能力结束时，服务器的能力也将结束

Not typically a good idea; it's the Server's version that matters
这通常不是一个好主意；重要的是服务器的版本

Replicate Input Directly
直接复制输入

Always replicates input press/release events to the Server.
总是将输入按下/释放事件复制到服务器。

Epic discourages it
Epic不鼓励这样做
 */

/* 100课
* Input
输入
Binding Input to the Ability System Component
将输入绑定到能力系统组件
This was an option before Enhanced Input
这是在 “增强输入 ”之前的一个选项。
Inputs were bound directly to Abilities
输入直接绑定到能力
Enum with Ability Input constants
能力输入常量枚举
 Rigid刚性

Enhanced Input
增强输入
Input Actions are bound to inputs via the Input Mapping Context.
输入操作通过 “输入映射上下文 ”与输入绑定。
We can decide how to activate abilities in response to inputs.
我们可以决定如何根据输入激活能力。
 Lyra provides one example
 Lyra 提供了一个示例
 We'll use a similar approach (though less complicated)
 我们将使用类似的方法（尽管没那么复杂）
Data Driven
数据驱动
 Change Input-to-Ability mappings at runtime
 在运行时更改输入到能力的映射
 */
