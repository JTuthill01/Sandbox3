#include "ProjectileBasePistol.h"
#include "../ImpactEffects/ImpactEffects.h"
#include "Kismet/GameplayStatics.h"

AProjectileBasePistol::AProjectileBasePistol() = default;

void AProjectileBasePistol::BeginPlay()
{
	Super::BeginPlay();

	AActor::SetLifeSpan(0.2F);
}

void AProjectileBasePistol::ProjectileStop(const FHitResult& HitResult)
{
	Super::ProjectileStop(HitResult);

	SpawnImpact(HitResult);

	GEngine->AddOnScreenDebugMessage(-1, 5.F, FColor::Red, __FUNCTION__);
}

void AProjectileBasePistol::SpawnImpact(const FHitResult& HitResult)
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
