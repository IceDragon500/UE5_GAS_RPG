// 我自己用来学习的试作品 -- 来自icedragon500

#pragma once

#include "CoreMinimal.h"
#include "Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraAbilitySystemLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "角色控制|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "角色控制|WidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "角色控制|CharacterClassInfo")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category = "角色控制|CharacterClassInfo")
	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category = "角色控制|CharacterClassInfo")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "角色控制|GameplayEffects")
	static  bool IsBlockHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "角色控制|GameplayEffects")
	static  bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable, Category = "角色控制|GameplayEffects")
	static void SetIsBlockHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool IsInBlockHit);

	UFUNCTION(BlueprintCallable, Category = "角色控制|GameplayEffects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool IsInCriticalHit);
	
protected:
private:
};
