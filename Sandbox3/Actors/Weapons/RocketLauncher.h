#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "RocketLauncher.generated.h"

UCLASS()
class SANDBOX3_API ARocketLauncher : public AWeaponBase
{
	GENERATED_BODY()
	
protected:
	virtual void WeaponFire(EFireType FireType) override;
	virtual void BeginPlay() override;
};
