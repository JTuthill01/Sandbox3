#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Rifle.generated.h"

UCLASS()
class SANDBOX3_API ARifle : public AWeaponBase
{
	GENERATED_BODY()

public:
	ARifle();

protected:
	virtual void WeaponFire(EFireType FireType) override;
	virtual void StopFire() override;
	virtual void SetWeaponEnum() override;
	virtual void BeginPlay() override;

	UFUNCTION()
	void RifleFire();

	UFUNCTION()
	void StopReload();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRifleFiring;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle RifleFireHandleTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle ReloadTimer;
};
