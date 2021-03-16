#include "Rifle.h"
#include "Sandbox3/Character/PlayerCharacter.h"
#include "Components/SceneComponent.h"
#include "Sandbox3/SandboxGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Math/Quat.h"

ARifle::ARifle() = default;

void ARifle::WeaponFire(EFireType FireType)
{
	bIsRifleFiring = true;

	RifleFire();

	GetWorld()->GetTimerManager().SetTimer(RifleFireHandleTimer, this, &ARifle::RifleFire, automaticFireRate, true);
}

void ARifle::StopFire()
{
	Super::StopFire();

	bIsRifleFiring = false;

	GetWorldTimerManager().ClearTimer(RifleFireHandleTimer);
}

void ARifle::SetWeaponEnum()
{
	Super::SetWeaponEnum();

	WeaponType = EWeaponType::Rifle;
}

void ARifle::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	ammoData = Instance->RifleAmmoData();

}

void ARifle::RifleFire()
{
	if (IsValid(PlayerRef))
	{
		if (bIsRifleFiring == true)
		{
			Super::WeaponFire(fireType);

			WeaponMesh->PlayAnimation(WeaponAnim, false);

			PlayerRef->OnFireWeapon.Broadcast(EWeaponType::Rifle);

			FTransform TempTransform;

			FQuat TempQuat;

			TempTransform = WeaponMesh->USceneComponent::GetSocketTransform("AmmoEject");

			TempTransform.GetRotation() = TempQuat;

			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), AmmoEject, TempTransform.GetTranslation(), TempQuat.Rotator());
		}

		if (currentAmmo <= 0)
		{
			currentAmmo = 0;

			StopFire();

			PlayerRef->Reload();

			GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ARifle::StopReload, 1.5F, false);
		}
	}
}

void ARifle::StopReload() 
{ 
	PlayerRef->StopReload(); 

	GetWorldTimerManager().ClearTimer(ReloadTimer);
}

