#include "SandboxGameInstance.h"

USandboxGameInstance::USandboxGameInstance() = default;

FAmmoData USandboxGameInstance::GrenadeLauncherAmmoData()
{
	GrenadeLauncherData.CritcalHit = 0.F;
	GrenadeLauncherData.Damage = 100.F;
	GrenadeLauncherData.DamageRadius = 300.F;

	return GrenadeLauncherData;
}

FAmmoData USandboxGameInstance::PistolAmmoData()
{
	PistolData.CritcalHit = 0.F;
	PistolData.Damage = 10.F;
	PistolData.DamageRadius = 0.F;

	return PistolData;
}

FAmmoData USandboxGameInstance::ShotgunAmmoData()
{
	ShotgunData.CritcalHit = 0.F;
	ShotgunData.Damage = 25.F;
	ShotgunData.DamageRadius = 0.F;

	return ShotgunData;
}

FAmmoData USandboxGameInstance::RifleAmmoData()
{
	RifleData.CritcalHit = 0.F;
	RifleData.Damage = 15.F;
	RifleData.DamageRadius = 0.F;

	return RifleData;
}

FAmmoData USandboxGameInstance::RocketLauncherAmmoData()
{
	RocketLauncherData.CritcalHit = 0.F;
	RocketLauncherData.Damage = 200.F;
	RocketLauncherData.DamageRadius = 400.F;

	return RocketLauncherData;
}

FAmmoData USandboxGameInstance::SniperRifleAmmoData()
{
	SniperRifleData.CritcalHit = 0.F;
	SniperRifleData.Damage = 50.F;
	SniperRifleData.DamageRadius = 0.F;

	return SniperRifleData;
}

FAmmoData USandboxGameInstance::WarHammerAmmoData()
{
	WarHammerData.CritcalHit = 0.F;
	WarHammerData.Damage = 60.F;
	WarHammerData.DamageRadius = 0.F;

	return WarHammerData;
}
