// 我自己用来学习的试作品 -- 来自icedragon500


#include "Character/AuraEnemy.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AAuraEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	GetMesh()->MarkRenderStateDirty();
	GetWeaponMesh()->SetRenderCustomDepth(true);
	GetWeaponMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	GetWeaponMesh()->MarkRenderStateDirty();
}

void AAuraEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	GetWeaponMesh()->SetRenderCustomDepth(false);
	GetMesh()->MarkRenderStateDirty();
	GetWeaponMesh()->MarkRenderStateDirty();
}
