#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "SniperRifle.generated.h"

UCLASS()
class SANDBOX3_API ASniperRifle : public AWeaponBase
{
	GENERATED_BODY()
	
protected:
	virtual void WeaponFire(EFireType FireType) override;
	virtual void BeginPlay() override;
};
