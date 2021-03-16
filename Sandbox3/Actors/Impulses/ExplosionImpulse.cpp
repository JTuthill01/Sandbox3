#include "ExplosionImpulse.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AExplosionImpulse::AExplosionImpulse()
{
	RadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("Radial Force"));
}

// Called when the game starts or when spawned
void AExplosionImpulse::BeginPlay()
{
	Super::BeginPlay();

	RadialForce->FireImpulse();
}


