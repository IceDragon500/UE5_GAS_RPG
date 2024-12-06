// 我自己用来学习的试作品

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

UCLASS(Abstract) //Abstract表示这一个抽象类，不能直接实例化
class AURA_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:

	AAuraCharacterBase();

protected:

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category= "角色|Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

public:
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return Weapon; }


};
