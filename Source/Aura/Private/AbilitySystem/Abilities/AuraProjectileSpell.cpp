// 我自己用来学习的试作品 -- 来自icedragon500


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "Interaction/CombatInterface.h"


void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo,
                                           const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	

	
	
}

void UAuraProjectileSpell::SpawnProjectile()
{
	
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();

	if(!bIsServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());

	if(CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		//todo 设置旋转


		//SpawnActorDeferred
		//生成给定的类并返回类 T 指针，强制设置世界变换（注意这也允许缩放）。
		//不会运行蓝图的构造脚本，以便调用者有机会事先设置参数。
		//调用者有责任通过调用 UGameplayStatics::FinishSpawningActor 手动调用建造脚本（请参阅 AActor::OnConstruction）。
		
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn //定义了用于处理以下情况的可用策略：当角色生成时，它穿透了阻挡碰撞。
			);

		//todo  这将视为投射物提供一个用于造成伤害的游戏效果规格

		Projectile->FinishSpawning(SpawnTransform);
	}
}
