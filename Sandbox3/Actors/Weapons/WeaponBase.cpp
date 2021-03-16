#include "WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sandbox3/Character/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Sandbox3/Actors/Projectiles/ProjectileBase.h"
#include "Animation/AnimationAsset.h"
#include "Sandbox3/Actors/ImpactEffects/ImpactEffects.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetCastShadow(false);
	SetRootComponent(WeaponMesh);

	recoilIntensitity = 30.F;
	aimFOV = 70.F;
	bulletSpread = 500.F;

	PlayerRef = nullptr;
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayerRef->ADS_FOV();
}

void AWeaponBase::WeaponReload()
{
	int temp = UKismetMathLibrary::Min(maxMagAmmo, currentTotalAmmo);

	currentAmmo = temp;

	currentTotalAmmo -= temp;

	WeaponMesh->PlayAnimation(ReloadAnim, false);
}

void AWeaponBase::WeaponFire(EFireType FireType)
{
	fireType = FireType;

	currentAmmo--;

	FHitResult Hit;

	FRotator Rotation;
	FRotator TempRotator;

	FTransform Transform;

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	switch (FireType)
	{
	case EFireType::Hitscan:

		if (PlayerRef)
		{
			if (bHasMultipleBullets == true)
			{
				for (int i = 0; i < bulletCount - 1; i++)
				{
					CalculateShot(PlayerRef->GetCamera(), WeaponMesh, SocketName, Hit, Transform);

					GetWorld()->SpawnActor<AImpactEffects>(ImpactEffects, Transform, SpawnInfo);

					AddDamage(Hit);
				}

				if (bIsAutomatic == true)
				{
					AutomaticRecoil();
				}
			}

			else
			{
				CalculateShot(PlayerRef->GetCamera(), WeaponMesh, SocketName, Hit, Transform);

				GetWorld()->SpawnActor<AImpactEffects>(ImpactEffects, Transform, SpawnInfo);

				AddDamage(Hit);

				if (bIsAutomatic == true)
				{
					AutomaticRecoil();
				}
			}

		}

		break;

	case EFireType::Projectile:
		
		CalculateShot(PlayerRef->GetCamera(), WeaponMesh, "MuzzleFlash", Hit, Transform);

		GetWorld()->SpawnActor<AProjectileBase>(Projectile, Transform, SpawnInfo);

		if (bIsAutomatic == true)
		{
			AutomaticRecoil();
		}

		break;

	default:
		break;
	}
}

void AWeaponBase::StopFire()
{
	//TODO Stuff
}

void AWeaponBase::HasAmmoInMag(bool& bHasAmmo, bool& bIsMagFull)
{
	bAmmo = bHasAmmo;
	bMagFull = bIsMagFull;

	if (currentAmmo > 0)
	{
		bHasAmmo = true;
	}

	else
	{
		bHasAmmo = false;
	}

	if (currentAmmo == maxMagAmmo)
	{
		bIsMagFull = true;
	}

	else
	{
		bIsMagFull = false;
	}
}

void AWeaponBase::HasFullMag(bool& bIsMagFull)
{
	bMagFull = bIsMagFull;

	if (currentAmmo == maxMagAmmo)
	{
		bIsMagFull = true;
	}

	else
	{
		bIsMagFull = false;
	}
}

void AWeaponBase::HasExtraAmmo(bool& bHasExtraAmmo)
{
	if (currentTotalAmmo > 0)
	{
		bHasExtraAmmo = true;
	}
}

void AWeaponBase::CalculateShot(class UCameraComponent* Camera, class USceneComponent* WMesh, FName WeaponFireSocketName, FHitResult& HitResult, FTransform& ProjectileTransform)
{
	UCameraComponent* LocalCameraComponent = Camera;
	USceneComponent* LocalWeaponMesh = WMesh;
	FName LocalSocketName = WeaponFireSocketName;
	FHitResult Hit = HitResult;
	FTransform LocalTransform;

	FVector StartLocation;
	FRotator EndLocation;
	FVector TempVector;
	FVector TVector;

	float TempFloat;
	float FloatX;
	float FloatY;
	float FloatZ;
	float TFloat;
	float Spread;
	float Spread1;
	float Spread2;
	float Spread3;

	StartLocation = LocalCameraComponent->GetComponentLocation();
	EndLocation = LocalCameraComponent->GetComponentRotation();

	TempVector = UKismetMathLibrary::GetForwardVector(EndLocation) * 10000.0;
	TVector = TempVector + StartLocation;

	TempFloat = bulletSpread * -1.F;
	TFloat = UKismetMathLibrary::RandomFloatInRange(TempFloat, bulletSpread);

	Spread = bulletSpread * -1.F;
	Spread1 = UKismetMathLibrary::RandomFloatInRange(Spread, bulletSpread);

	Spread2 = bulletSpread * -1.F;
	Spread3 = UKismetMathLibrary::RandomFloatInRange(Spread2, bulletSpread);

	FloatX = TVector.X + TFloat;
	FloatY = TVector.Y + Spread1;
	FloatZ = TVector.Z + Spread3;

	FVector EndVector(FloatX, FloatY, FloatZ);
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjects;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(UGameplayStatics::GetPlayerController(PlayerRef, 0));
	TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));

	FVector SocketLocation = LocalWeaponMesh->GetSocketLocation(LocalSocketName);

	FVector Scale(1.F, 1.F, 1.F);

	if (UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), StartLocation, EndVector, TraceObjects, true, ActorsToIgnore, EDrawDebugTrace::None, Hit, true) == true)
	{
		FRotator TempRotator;
		TempRotator = UKismetMathLibrary::FindLookAtRotation(SocketLocation, Hit.ImpactPoint);

		LocalTransform = UKismetMathLibrary::MakeTransform(SocketLocation, TempRotator, Scale);
	}

	else
	{
		FRotator TempRotator;
		AActor* TempActor = LocalCameraComponent->GetOwner();
		APawn* TempPawn;

		TempPawn = Cast<APawn>(TempActor);

		TempRotator = TempPawn->GetControlRotation();

		LocalTransform = UKismetMathLibrary::MakeTransform(SocketLocation, TempRotator, Scale);
	}

	HitResult = Hit;

	ProjectileTransform = LocalTransform;
}

void AWeaponBase::AddDamage(FHitResult HitResult)
{
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	//PlayerRef->OnAimEnter.AddDynamic(this, &AWeaponBase::OnAimEnter);
	//PlayerRef->OnAimExit.AddDynamic(this, &AWeaponBase::OnAimExit);
}

bool AWeaponBase::bHasAmmoInMag()
{
	if (currentAmmo > 0)
	{
		return true;
	}

	return false;
}

bool AWeaponBase::bHasExtraAmmo()
{
	if (currentTotalAmmo > 0)
	{
		return true;
	}

	return false;
}

bool AWeaponBase::bExtraAmmo()
{
	if (currentTotalAmmo > 0)
	{
		return true;
	}

	return false;
}

bool AWeaponBase::bHasFullMag()
{
	if (currentAmmo == maxMagAmmo)
	{
		return true;
	}

	return false;
}

void AWeaponBase::AutomaticRecoil_Implementation() {}

void AWeaponBase::OnAimEnter() { bIsAiming = true; }

void AWeaponBase::OnAimExit() { bIsAiming = false; }

bool AWeaponBase::GetIsAiming() const { return bIsAiming; }

bool AWeaponBase::GetHasAmmo() const { return bAmmo; }

bool AWeaponBase::GetIsMagfull() const { return bMagFull; }

float AWeaponBase::GetAimFOV() const { return aimFOV; }

FName AWeaponBase::GetSocketName() { return SocketName; }

void AWeaponBase::SetWeaponEnum() {}

