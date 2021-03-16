#include "ImpactEffects.h"
#include "Kismet/KismetMathLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Chaos/ChaosEngineInterface.h"
#include "Sound/SoundBase.h"
#include "Materials/MaterialInterface.h"

// Sets default values
AImpactEffects::AImpactEffects(){}

// Called when the game starts or when spawned
void AImpactEffects::BeginPlay()
{
	Super::BeginPlay();

	SetDecalRotation(HitResult);

	SpawnFX(HitResult);

	SpawnSound(HitResult);

	SpawnDecal(HitResult);

	AActor::SetLifeSpan(0.3F);
}

void AImpactEffects::SetDecalRotation(FHitResult& Hit)
{
	FVector Normal;
	Normal = Hit.Normal;

	FRotator TempRotator;
	TempRotator = UKismetMathLibrary::MakeRotFromX(Normal);

	float TempFloat = UKismetMathLibrary::RandomFloatInRange(-180.F, 180.F);

	DecalRotation = UKismetMathLibrary::MakeRotator(TempFloat, TempRotator.Pitch, TempRotator.Yaw);
}

void AImpactEffects::SpawnFX(FHitResult& Hit)
{
	if (Hit.bBlockingHit == true && Hit.PhysMaterial != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, __FUNCTION__);

		FRotator Rotation;
		FVector Scale(1.F);

		switch (Hit.PhysMaterial->SurfaceType)
		{
		case SurfaceType1:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DefaultFX, Hit.Location, Rotation, Scale);

		break;

		case SurfaceType2:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, Hit.Location, Rotation, Scale);

		break;

		case SurfaceType3:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, Hit.Location, Rotation, Scale);

		break;

		case SurfaceType4:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, Hit.Location, Rotation, Scale);

			break;

		case SurfaceType5:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, Hit.Location, Rotation, Scale);

			break;

		case SurfaceType6:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, Hit.Location, Rotation, Scale);

			break;

		case SurfaceType7:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, Hit.Location, Rotation, Scale);

			break;

		case SurfaceType8:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, Hit.Location, Rotation, Scale);

			break;

		default:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DefaultFX, Hit.Location, Rotation, Scale);
			
			break;
		}
	}
}

void AImpactEffects::SpawnSound(FHitResult& Hit)
{
	if (Hit.bBlockingHit == true && Hit.PhysMaterial != nullptr)
	{
		switch (Hit.PhysMaterial->SurfaceType)
		{
		case SurfaceType1:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), DefaultSound, Hit.Location);

			break;

		case SurfaceType2:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ConcreteSound, Hit.Location);

			break;

		case SurfaceType3:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound, Hit.Location);

			break;

		case SurfaceType4:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound, Hit.Location);

			break;

		case SurfaceType5:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound, Hit.Location);

			break;

		case SurfaceType6:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound, Hit.Location);

			break;

		case SurfaceType7:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound, Hit.Location);

			break;

		case SurfaceType8:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound, Hit.Location);

			break;

		default:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), DefaultSound, Hit.Location);

			break;
		}
	}
}

void AImpactEffects::SpawnDecal(FHitResult& Hit)
{
	FVector DecalVector(DecalSize);

	USceneComponent* TempComponent = Cast<USceneComponent>(Hit.Component);
	
	if (Hit.bBlockingHit == true && Hit.PhysMaterial != nullptr)
	{
		switch (Hit.PhysMaterial->SurfaceType)
		{
		case SurfaceType1:
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, __FUNCTION__);

			UGameplayStatics::SpawnDecalAttached(DefaultDecalMaterial, DecalVector, TempComponent, HitName, Hit.ImpactPoint, DecalRotation);

			break;
		case SurfaceType2:

			UGameplayStatics::SpawnDecalAttached(ConcreteDecalMaterial, DecalVector, TempComponent, HitName, Hit.ImpactPoint, DecalRotation);

			break;
		case SurfaceType3:

			UGameplayStatics::SpawnDecalAttached(FleshDecalMaterial, DecalVector, TempComponent, HitName, Hit.ImpactPoint, DecalRotation);

			break;
		case SurfaceType4:

			UGameplayStatics::SpawnDecalAttached(FleshDecalMaterial, DecalVector, TempComponent, HitName, Hit.ImpactPoint, DecalRotation);

			break;
		case SurfaceType5:

			UGameplayStatics::SpawnDecalAttached(FleshDecalMaterial, DecalVector, TempComponent, HitName, Hit.ImpactPoint, DecalRotation);

			break;
		case SurfaceType6:

			UGameplayStatics::SpawnDecalAttached(FleshDecalMaterial, DecalVector, TempComponent, HitName, Hit.ImpactPoint, DecalRotation);

			break;
		case SurfaceType7:

			UGameplayStatics::SpawnDecalAttached(FleshDecalMaterial, DecalVector, TempComponent, HitName, Hit.ImpactPoint, DecalRotation);

			break;
		case SurfaceType8:

			UGameplayStatics::SpawnDecalAttached(FleshDecalMaterial, DecalVector, TempComponent, HitName, Hit.ImpactPoint, DecalRotation);

			break;
		
		default:

			UGameplayStatics::SpawnDecalAttached(DefaultDecalMaterial, DecalVector, TempComponent, HitName, Hit.ImpactPoint, DecalRotation);

			break;
		}
	}
}
