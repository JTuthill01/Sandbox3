#include "ProjectileBase.h"
#include "Sandbox3/Actors/ImpactEffects/ImpactEffects.h"
#include "Sandbox3/Character/PlayerCharacter.h"
#include "Sandbox3/Actors/Impulses/ExplosionImpulse.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	TrailFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailFX"));

	ProjectileMesh->SetupAttachment(Sphere);

	SetRootComponent(Sphere);

	EmptyRotation = FRotator(0.F);

	ProjectileMovement->bSweepCollision = true;

	Sphere->bReturnMaterialOnMove = true;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	HitLocation = ProjectileMesh->GetComponentTransform();
	
	PlayerRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	ProjectileMovement->OnProjectileStop.AddDynamic(this, &AProjectileBase::ProjectileStop);

	SetLifeSpan(1.F);
}

void AProjectileBase::ProjectileStop(const FHitResult& HitResult)
{
	if (bIsCausingRadiusDamage == true)
	{
		ExplodeOnImpact(HitResult);

		ProjectileMesh->SetHiddenInGame(true);

		Spawn(HitResult);
	}

	else
	{
		//Damage->OnTakeDamage(HitResult.GetActor(), AmmoData, CriticalHitModifier, HitResult);

		GEngine->AddOnScreenDebugMessage(-1, 5.F, FColor::Red, __FUNCTION__);

		ProjectileMesh->SetHiddenInGame(true);

		Spawn(HitResult);
	}
}

void AProjectileBase::ExplodeOnImpact(const FHitResult& HitResult)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjects;
	TArray<AActor*> ActorsToIgnore;
	TArray<AActor*> OutActors;

	ActorsToIgnore.Add(PlayerRef->CurrentWeapon);

	TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
	TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), HitResult.ImpactPoint, AmmoData.DamageRadius, TraceObjects, NULL, ActorsToIgnore, OutActors);

	uint8 Len = OutActors.Num();

	for (uint8 i = 0; i < Len; ++i)
	{
		OutActors[i] = HitResult.Actor.Get();

		//Damage->OnTakeDamage(OutActors[i], AmmoData, CriticalHitModifier, HitResult);
	}

	SpawnImpulse(HitResult);
}

void AProjectileBase::Spawn(const FHitResult& HitResult){}

void AProjectileBase::SpawnImpulse(const FHitResult& HitResult)
{
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector Location = HitResult.ImpactPoint;
	FRotator Rotation = FRotator(0.F);

	GetWorld()->SpawnActor<AExplosionImpulse>(Impulse, Location, Rotation, Params);
}



