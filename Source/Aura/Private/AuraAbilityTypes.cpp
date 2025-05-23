#include "AuraAbilityTypes.h"

bool FAuraGameplayEffectContext::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	uint32 RepBits = 0;

	//IsSaving() : 如果此存档用于保存数据，则返回 true，也可以是保存前的准备存档。
	if (Ar.IsSaving())
	{
		//bReplicateInstigator : 如果 Instigator 可以复制，则为 True。此 bool 本身不可复制
		//Instigator : 即拥有能力系统组件的角色
		if (bReplicateInstigator && Instigator.IsValid()) RepBits |= 1 << 0;

		//bReplicateEffectCauser : 如果 Instigator 可以复制，则为 True。此 bool 本身不可复制
		//EffectCauser : 实际造成伤害的物理行为者，可以是武器或弹丸
		if (bReplicateEffectCauser && EffectCauser.IsValid()) RepBits |= 1 << 1;

		//AbilityCDO : 产生这种效果的能力 CDO 背景（复制）
		if (AbilityCDO.IsValid()) RepBits |= 1 << 2;

		//bReplicateSourceObject : 如果 SourceObject 可以复制，则为 True。此 bool 本身不会复制
		//SourceObject : 该特效的创建对象，可以是演员或静态对象。可用于将效果绑定到游戏对象上
		if (bReplicateSourceObject && SourceObject.IsValid()) RepBits |= 1 << 3;

		if (Actors.Num() > 0) RepBits |= 1 << 4;
		if (HitResult.IsValid()) RepBits |= 1 << 5;
		if (bHasWorldOrigin) RepBits |= 1 << 6;
		if (bIsBlockedHit) RepBits |= 1 << 7;
		if (bIsCriticalHit) RepBits |= 1 << 8;
		if (bIsSuccessfulDebuff) RepBits |= 1 << 9;
		if (DebuffDamage > 0.f) RepBits |= 1 << 10;
		if (DebuffDuration > 0.f) RepBits |= 1 << 11;
		if (DebuffFrequency > 0.f) RepBits |= 1 << 12;
		if (DamageType.IsValid()) RepBits |= 1 << 13;
		if (!DeathImpulse.IsZero()) RepBits |= 1 << 14;
	}

	Ar.SerializeBits(&RepBits, 15);

	if (RepBits & (1 << 0)) Ar << Instigator;
	if (RepBits & (1 << 1)) Ar << EffectCauser;
	if (RepBits & (1 << 2)) Ar << AbilityCDO;
	if (RepBits & (1 << 3)) Ar << SourceObject;
	if (RepBits & (1 << 4)) SafeNetSerializeTArray_Default<31>(Ar, Actors);
	if (RepBits & (1 << 5))
	{
		if (Ar.IsLoading())
		{
			if (!HitResult.IsValid())
			{
				HitResult = TSharedPtr<FHitResult>(new FHitResult());
			}
			HitResult->NetSerialize(Ar, Map, bOutSuccess);
		}
	}
	if (RepBits & (1 << 6))
	{
		Ar << WorldOrigin;
		bHasWorldOrigin = true;
	}
	else
	{
		bHasWorldOrigin = false;
	}
	if (RepBits & (1 << 7)) Ar << bIsBlockedHit;
	if (RepBits & (1 << 8)) Ar << bIsCriticalHit;
	if (RepBits & (1 << 9)) Ar << bIsSuccessfulDebuff;
	if (RepBits & (1 << 10)) Ar << DebuffDamage;
	if (RepBits & (1 << 11)) Ar << DebuffDuration;
	if (RepBits & (1 << 12)) Ar << DebuffFrequency;
	if (RepBits & (1 << 13))
	{
		if (Ar.IsLoading())
		{
			if (!DamageType.IsValid())
			{
				DamageType = TSharedPtr<FGameplayTag>(new FGameplayTag());
			}
			DamageType->NetSerialize(Ar, Map, bOutSuccess);
		}
	}
	if (RepBits & (1 << 14))
	{
		DeathImpulse.NetSerialize(Ar, Map, bOutSuccess);
	}

	if (Ar.IsLoading())
	{
		AddInstigator(Instigator.Get(), EffectCauser.Get());
	}
	bOutSuccess = true;

	return true;
}
