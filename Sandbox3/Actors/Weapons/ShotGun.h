#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "ShotGun.generated.h"

UCLASS()
class SANDBOX3_API AShotGun : public AWeaponBase
{
	GENERATED_BODY()
	
protected:
	virtual void WeaponFire(EFireType FireType) override;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetReloadTime();
};
