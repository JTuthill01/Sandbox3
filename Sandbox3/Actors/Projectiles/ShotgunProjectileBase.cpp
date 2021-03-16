#include "ShotgunProjectileBase.h"
#include "../ImpactEffects/ImpactEffects.h"
#include "Kismet/GameplayStatics.h"

void AShotgunProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	AActor::SetLifeSpan(0.1F);
}

void AShotgunProjectileBase::ProjectileStop(const FHitResult& HitResult)
{
	Super::ProjectileStop(HitResult);

	SpawnImpact(HitResult);
}

void AShotgunProjectileBase::SpawnImpact(const FHitResult& HitResult)
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
