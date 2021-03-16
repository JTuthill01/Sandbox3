#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Sandbox3/Actors/Weapons/WeaponBase.h"
#include "SandboxGameInstance.generated.h"

UCLASS()
class SANDBOX3_API USandboxGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	USandboxGameInstance();

	UFUNCTION()
	FAmmoData GrenadeLauncherAmmoData();

	UFUNCTION()
	FAmmoData PistolAmmoData();

	UFUNCTION()
	FAmmoData ShotgunAmmoData();

	UFUNCTION()
	FAmmoData RifleAmmoData();

	UFUNCTION()
	FAmmoData RocketLauncherAmmoData();

	UFUNCTION()
	FAmmoData SniperRifleAmmoData();

	UFUNCTION()
	FAmmoData WarHammerAmmoData();

	FAmmoData PistolData;
	FAmmoData ShotgunData;
	FAmmoData RifleData;
	FAmmoData GrenadeLauncherData;
	FAmmoData RocketLauncherData;
	FAmmoData SniperRifleData;
	FAmmoData WarHammerData;
};
