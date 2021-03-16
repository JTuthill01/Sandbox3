#include "GrenadeLauncher.h"
#include "Sandbox3/SandboxGameInstance.h"
#include "Kismet/GameplayStatics.h"

AGrenadeLauncher::AGrenadeLauncher(){}

void AGrenadeLauncher::BeginPlay()
{
	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	ammoData = Instance->GrenadeLauncherAmmoData();

	Super::BeginPlay();
}

void AGrenadeLauncher::WeaponFire(EFireType FireType)
{
	WeaponMesh->PlayAnimation(WeaponAnim, false);

	Super::WeaponFire(FireType);
}
