#include "WarHammerPickup.h"
#include "Kismet/GameplayStatics.h"
#include "Sandbox3/Character/PlayerCharacter.h"
#include "Sandbox3/Actors/WarHammer/WarHammer.h"
#include "Components/SphereComponent.h"

// Sets default values
AWarHammerPickup::AWarHammerPickup()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	HammerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));

	SetRootComponent(HammerMesh);

	Sphere->SetupAttachment(HammerMesh);
	Sphere->SetGenerateOverlapEvents(true);
}

void AWarHammerPickup::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

