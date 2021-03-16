#include "ProjectileBase_RocketLauncher.h"
#include "../ImpactEffects/ImpactEffects.h"
#include "../Impulses/ExplosionImpulse.h"
#include "Kismet/GameplayStatics.h"
#include "Sandbox3/SandboxGameInstance.h"
#include "Sandbox3/Character/PlayerCharacter.h"

AProjectileBase_RocketLauncher::AProjectileBase_RocketLauncher() { bIsCausingRadiusDamage = true; }

void AProjectileBase_RocketLauncher::BeginPlay()
{
	Super::BeginPlay();

	AActor::SetLifeSpan(1.F);
}

void AProjectileBase_RocketLauncher::ProjectileStop(const FHitResult& HitResult)
{
	Super::ProjectileStop(HitResult);

	if (bIsCausingRadiusDamage == true)
	{
		ExplodeOnImpact(HitResult);

		ProjectileMesh->SetHiddenInGame(true);

		SpawnImpact(HitResult);
	}
}

void AProjectileBase_RocketLauncher::ExplodeOnImpact(const FHitResult& HitResult)
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
		OutActors[i] = Cast<AActor>(HitResult.Actor);

		//Damage->OnTakeDamage(OutActors[i], AmmoData, CriticalHitModifier, HitResult);
	}

	SpawnImpulse(HitResult);
}	

void AProjectileBase_RocketLauncher::SpawnImpact(const FHitResult& HitResult)
{
	FRotator TempRotator;

	FTransform Location = ProjectileMesh->GetComponentTransform();

	AImpactEffects* TempImpact = GetWorld()->SpawnActorDeferred<AImpactEffects>(ImpactEffect, Location);

	if (TempImpact != nullptr)
	{
		TempImpact->HitResult = HitResult;
		TempImpact->HitResult.bBlockingHit = HitResult.bBlockingHit;

		FTransform HitTransform(TempRotator, HitResult.ImpactPoint);

		UGameplayStatics::FinishSpawningActor(TempImpact, HitTransform);
	}
}

void AProjectileBase_RocketLauncher::SpawnImpulse(const FHitResult& HitResult)
{
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector Location = HitResult.ImpactPoint;
	FRotator Rotation = FRotator(0.F);

	GetWorld()->SpawnActor<AExplosionImpulse>(Impulse, Location, Rotation, Params);
}
