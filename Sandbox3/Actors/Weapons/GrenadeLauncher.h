#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "GrenadeLauncher.generated.h"

UCLASS()
class SANDBOX3_API AGrenadeLauncher : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AGrenadeLauncher();

protected:
	virtual void BeginPlay() override;
	virtual void WeaponFire(EFireType FireType) override;
};
