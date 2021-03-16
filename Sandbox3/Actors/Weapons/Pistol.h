#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Pistol.generated.h"

UCLASS()
class SANDBOX3_API APistol : public AWeaponBase
{
	GENERATED_BODY()
	
protected:
	virtual void WeaponFire(EFireType FireType) override;
	virtual void BeginPlay() override;
};
