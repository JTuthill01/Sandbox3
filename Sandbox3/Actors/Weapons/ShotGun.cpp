#include "ShotGun.h"
#include "Kismet/GameplayStatics.h"
#include "Sandbox3/SandboxGameInstance.h"
#include "../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Math/Quat.h"

void AShotGun::WeaponFire(EFireType FireType)
{
	FTransform TempTransform;

	FQuat TempQuat;

	Super::WeaponFire(FireType);

	WeaponMesh->PlayAnimation(WeaponAnim, false);

	TempTransform = WeaponMesh->GetSocketTransform("AmmoEject");

	TempTransform.GetRotation() = TempQuat;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), AmmoEject, TempTransform.GetTranslation(), TempQuat.Rotator());
}

void AShotGun::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	ammoData = Instance->ShotgunAmmoData();
}

void AShotGun::SetReloadTime() { reloadTime = maxMagAmmo * 0.5F; }
