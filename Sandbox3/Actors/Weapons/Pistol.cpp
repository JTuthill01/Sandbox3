#include "Pistol.h"
#include "Components/SceneComponent.h"
#include "Sandbox3/SandboxGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Math/Quat.h"

void APistol::WeaponFire(EFireType FireType)
{
	FTransform TempTransform;
	FQuat TempQuat;

	Super::WeaponFire(FireType);

	WeaponMesh->PlayAnimation(WeaponAnim, false);

	TempTransform = WeaponMesh->USceneComponent::GetSocketTransform("AmmoEject");

	TempTransform.GetRotation() = TempQuat;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), AmmoEject, TempTransform.GetTranslation(), TempQuat.Rotator());
}

void APistol::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	ammoData = Instance->PistolAmmoData();
}
