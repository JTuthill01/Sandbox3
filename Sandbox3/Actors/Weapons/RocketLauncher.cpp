#include "RocketLauncher.h"
#include "Sandbox3/SandboxGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ARocketLauncher::WeaponFire(EFireType FireType)
{
	Super::WeaponFire(FireType);

	WeaponMesh->PlayAnimation(WeaponAnim, false);
}

void ARocketLauncher::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	ammoData = Instance->RocketLauncherAmmoData();
}
