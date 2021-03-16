#include "WarHammer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Sandbox3/Actors/Weapons/WeaponBase.h"
#include "Sandbox3/Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/Linker.h"
#include "../ImpactEffects/ImpactEffects.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AWarHammer::AWarHammer()
{
	HammerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hammer"));
	HammerMesh->SetCastShadow(false);
	
	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	CollisionCapsule->SetupAttachment(HammerMesh);
	CollisionCapsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionCapsule->SetGenerateOverlapEvents(true);
	CollisionCapsule->bReturnMaterialOnMove = true;

	SetRootComponent(HammerMesh);
}

void AWarHammer::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AWarHammer::SpawnImpact(const FHitResult& HitResult)
{
	FRotator TempRotator;

	FTransform Location = CollisionCapsule->GetComponentTransform();

	AImpactEffects* TempImpact = GetWorld()->SpawnActorDeferred<AImpactEffects>(ImpactEffect, Location);

	if (TempImpact != nullptr)
	{
		TempImpact->HitResult = HitResult;
		TempImpact->HitResult.bBlockingHit = HitResult.bBlockingHit;

		FTransform HitTransform(TempRotator, HitResult.ImpactPoint);

		UGameplayStatics::FinishSpawningActor(TempImpact, HitTransform);
	}
}
