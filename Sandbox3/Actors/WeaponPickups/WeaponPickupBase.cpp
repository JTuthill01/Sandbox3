#include "WeaponPickupBase.h"
#include "Sandbox3/Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Sandbox3/Actors/WarHammer/WarHammer.h"

// Sets default values
AWeaponPickupBase::AWeaponPickupBase()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));

	SetRootComponent(WeaponMesh);

	Sphere->SetupAttachment(WeaponMesh);
	Sphere->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AWeaponPickupBase::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}
