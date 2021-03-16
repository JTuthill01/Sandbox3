#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Sandbox3/Actors/Weapons/WeaponBase.h"
#include "INT_Damage.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UINT_Damage : public UInterface
{
	GENERATED_BODY()
};

class SANDBOX3_API IINT_Damage
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnDamage(AActor* Actor, int DamageToDeal, float CritcalDamageModifier, FHitResult& HitResult);

	UFUNCTION(BlueprintImplementableEvent)
	void OnTakeDamage(AActor* Actor, FAmmoData Data, float CritcalDamageModifier, FHitResult& HitResult);
};
