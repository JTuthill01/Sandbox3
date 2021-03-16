#include "AbilitiesBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sandbox3/Character/PlayerCharacter.h"

// Sets default values
AAbilitiesBase::AAbilitiesBase()
{
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetSimulatePhysics(true);
	CollisionSphere->SetNotifyRigidBodyCollision(true);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionSphere->SetupAttachment(NAbility);

	/*VFX_Ability = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("VFX Ability"));*/

	NAbility = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Ability"));

	/*MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));*/

	SetRootComponent(NAbility);
}

// Called when the game starts or when spawned
void AAbilitiesBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	CollisionSphere->OnComponentHit.AddDynamic(this, &AAbilitiesBase::AbilityHit);
	//CollisionSphere->OnComponentBeginOverlap
}

void AAbilitiesBase::AbilityToSpawn() {}

void AAbilitiesBase::AbilityHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {}
