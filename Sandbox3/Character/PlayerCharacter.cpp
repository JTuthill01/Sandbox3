#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Sandbox3/Actors/WarHammer/WarHammerAnimNotifyState.h"
#include "Sandbox3/Actors/WarHammer/WarHammer.h"
#include "Sandbox3/Actors/WeaponPickups/WeaponPickupBase.h"
#include "../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraSystem.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(GetRootComponent());

	Sleeve = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Sleeve"));
	Sleeve->SetupAttachment(Camera);
	Sleeve->SetCastShadow(false);

	Gloves = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gloves"));
	Gloves->SetupAttachment(Camera);
	Gloves->SetMasterPoseComponent(Sleeve);
	Gloves->SetCastShadow(false);

	Ability = CreateDefaultSubobject<UNiagaraSystem>(TEXT("Ability"));

	bCanFire = true;
	bCanSwitchWeapon = true;
	bCanReload = true;

	ReloadTime = 1.5F;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

void APlayerCharacter::DoOnce(AWeaponBase* Weapon)
{
	if (bDo)
	{
		ShowWeapon(Weapon);

		return;
	}

	else
		return;
}

void APlayerCharacter::ResetDoOnce()
{
	bDo = true;

	return;
}

void APlayerCharacter::EquipWeapon(AWeaponBase* Weapon)
{
	if (bIsChangingWeapon == false)
	{
		bIsChangingWeapon = true;

		if (bIsReloading)
		{
			bCanFire = false;

			bIsReloading = false;
		}
	}

	CurrentWeapon = Weapon;

	HasWeaponEnum = EHasWeapon::HasWeapon;

	ShowWeapon(Weapon);
}

void APlayerCharacter::ShowWeapon(AWeaponBase* Weapon)
{
	if (IsValid(Weapon))
	{
		if (Weapon != WeaponSlot_01)
		{
			WeaponSlot_01->SetActorHiddenInGame(true);

			if (Weapon == WeaponSlot_02)
			{
				WeaponSlot_02->SetActorHiddenInGame(false);
			}
		}

		else if (Weapon == WeaponSlot_01)
		{
			WeaponSlot_01->SetActorHiddenInGame(false);
		}
	}
}

bool APlayerCharacter::SpawnWeapon(TSubclassOf<AWeaponBase > WeaponToSpawn, bool& bIsSuccessful)
{
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector Location = GetMesh()->GetComponentLocation();

	FRotator Rotation = GetMesh()->GetComponentRotation();

	switch (EWeaponSlotEnum)
	{
	case EWeaponSlot::First_Slot:

		if (!bIsFirstSlotFull)
		{
			WeaponSlot_01 = GetWorld()->SpawnActor<AWeaponBase>(WeaponToSpawn, Location, Rotation, Params);

			if (IsValid(WeaponSlot_01))
			{
				WeaponSlot_01->AttachToComponent(Gloves, FAttachmentTransformRules::SnapToTargetIncludingScale,
					WeaponSlot_01->GetSocketName());

				bIsFirstSlotFull = true;

				CurrentWeapon = WeaponSlot_01;

				HasWeaponEnum = EHasWeapon::HasWeapon;

				ShowWeapon(CurrentWeapon);

				bIsSuccessful = true;

				bIsFirstSlotActive = false;

				bIsSecondSlotActive = false;
			}
		}

		else if (!bIsSecondSlotFull)
		{
			EWeaponSlotEnum = EWeaponSlot::Second_Slot;

			SpawnWeapon(WeaponToSpawn, bIsSuccessful);
		}

		else
		{
			bIsSuccessful = false;
		}
		
		break;

	case EWeaponSlot::Second_Slot:

		if (!bIsSecondSlotFull)
		{
			WeaponSlot_02 = GetWorld()->SpawnActor<AWeaponBase>(WeaponToSpawn, Location, Rotation, Params);

			if (IsValid(WeaponSlot_02))
			{
				WeaponSlot_02->AttachToComponent(Gloves, FAttachmentTransformRules::SnapToTargetIncludingScale,
					WeaponSlot_02->GetSocketName());

				bIsSecondSlotFull = true;

				CurrentWeapon = WeaponSlot_02;

				HasWeaponEnum = EHasWeapon::HasWeapon;

				ShowWeapon(CurrentWeapon);

				bIsSuccessful = true;

				bIsSecondSlotActive = true;

				bIsFirstSlotActive = false;
			}
		}

		else if (!bIsFirstSlotFull)
		{
			EWeaponSlotEnum = EWeaponSlot::First_Slot;

			SpawnWeapon(WeaponToSpawn, bIsSuccessful);
		}

		else
		{
			bIsSuccessful = false;
		}

		break;

	case EWeaponSlot::Third_Slot:
		break;

	default:
		break;
	}

	return bIsSuccessful;
}

bool APlayerCharacter::SpawnHammer(TSubclassOf<AWarHammer> HammerToSpawn, bool& bIsSuccessful)
{
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector Location = GetMesh()->GetComponentLocation();

	FRotator Rotation = GetMesh()->GetComponentRotation();

	HammerSpawn = GetWorld()->SpawnActor<AWarHammer>(HammerToSpawn, Location, Rotation, Params);

	if (IsValid(HammerSpawn))
	{
		HammerSpawn->AttachToComponent(Gloves, FAttachmentTransformRules::SnapToTargetIncludingScale,
			HammerSpawn->GetHammerSocketName());

		HammerSpawn->SetActorHiddenInGame(true);

		bIsSuccessful = true;
	}

	else
	{
		bIsSuccessful = false;
	}

	return bIsSuccessful;
}

void APlayerCharacter::SetFOV(float FOV)
{
}

void APlayerCharacter::StopFire()
{
	CurrentWeapon->StopFire();

	OnStopFire.Broadcast();
}

void APlayerCharacter::Fire()
{
	if (bCanFire == true)
	{
		if (CurrentWeapon->bHasAmmoInMag() == true)
		{
			CurrentWeapon->WeaponFire(CurrentWeapon->fireType);

			OnFireWeapon.Broadcast(CurrentWeapon->WeaponType);
		}

		else if (CurrentWeapon->bHasAmmoInMag() == false)
		{
			if (CurrentWeapon->bExtraAmmo() == true)
			{
				bCanReload = true;

				Reload();
			}
		}

		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("No Ammo!!!!!!"));
		}
	}
}

void APlayerCharacter::Reload()
{
	if (bCanReload == true)
	{
		if (bIsReloading == false || bIsChangingWeapon == false)
		{
			if (CurrentWeapon->bHasFullMag() == false)
			{
				bIsReloading = true;

				bCanFire = false;

				CurrentWeapon->WeaponReload();

				GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &APlayerCharacter::StopReload, ReloadTime, false);
			}
		}
	}
}

void APlayerCharacter::StopReload()
{
	bIsReloading = false;

	bCanFire = true;

	GetWorld()->GetTimerManager().ClearTimer(ReloadTimer);
}

void APlayerCharacter::ADS_FOV()
{
	if (CurrentWeapon->GetIsAiming())
	{
		float temp = FMath::FInterpTo(Camera->FieldOfView, CurrentWeapon->GetAimFOV(),
			GetWorld()->DeltaTimeSeconds, 10.F);

		Camera->SetFieldOfView(temp);
	}

	else
	{
		float temp = FMath::FInterpTo(Camera->FieldOfView, defaultFOV,
			GetWorld()->DeltaTimeSeconds, 10.F);

		Camera->SetFieldOfView(temp);
	}
}

//// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(HammerSpawn))
	{
		HideHammer();
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("MoveUp"), this, &APlayerCharacter::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("TurnRate"), this, &APlayerCharacter::TurnRate);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &APlayerCharacter::LookUpRate);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &APlayerCharacter::StopJump);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &APlayerCharacter::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &APlayerCharacter::StopSprint);
	PlayerInputComponent->BindAction(TEXT("Melee"), IE_Pressed, this, &APlayerCharacter::StartMeleeAttack);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerCharacter::FirePressed);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &APlayerCharacter::FireReleased);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &APlayerCharacter::Interact);
	PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &APlayerCharacter::Reload);
	PlayerInputComponent->BindAction(TEXT("Equip"), IE_Pressed, this, &APlayerCharacter::Equip);
	PlayerInputComponent->BindAction(TEXT("Ability"), IE_Pressed, this, &APlayerCharacter::PlayAbility);
}

void APlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.F)
	{
		AddMovementInput(GetActorForwardVector() * Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.F)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void APlayerCharacter::MoveUp(float Value)
{
	if (Value != 0.F)
	{
		AddMovementInput(GetActorUpVector(), Value);
	}
}

void APlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::TurnRate(float Value)
{
	AddControllerPitchInput(Value);
}

void APlayerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value * BaseLookRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::Interact(){ OnInteract.Broadcast(); }

void APlayerCharacter::Equip() 
{
	if (CurrentWeapon != WeaponSlot_01 && bIsFirstSlotFull == true)
	{
		WeaponSlot_02->SetActorHiddenInGame(true);

		WeaponSlot_01->SetActorHiddenInGame(false);

		CurrentWeapon = WeaponSlot_01;
	}

	else if (CurrentWeapon != WeaponSlot_02 && bIsSecondSlotFull == true)
	{
		WeaponSlot_01->SetActorHiddenInGame(true);

		WeaponSlot_02->SetActorHiddenInGame(false);

		CurrentWeapon = WeaponSlot_02;
	}
}

void APlayerCharacter::PlayAbility()
{
	FVector TempLocation = GetActorLocation();
	FRotator TempRotator = UKismetMathLibrary::MakeRotFromX(GetActorForwardVector());

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Ability, TempLocation, TempRotator);
}

void APlayerCharacter::StartMeleeAttack() 
{
	bShouldBeShown = true;

	FHitResult HitResult;

	if (IsValid(HammerSpawn) && bShouldBeShown == true)
	{
		HammerSpawn->SetActorHiddenInGame(false);

		bIsMelee = true;
	}

	else
	{
		return;
	}
}

void APlayerCharacter::HideHammer()
{
	if (bIsMelee == false && IsValid(HammerSpawn))
	{
		if (bShouldBeShown == false)
		{
			HammerSpawn->SetActorHiddenInGame(true);
		}
	}
}

void APlayerCharacter::FirePressed()
{
	switch (HasWeaponEnum)
	{
	case EHasWeapon::NoWeapon:

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("No Weapon!!!!!!"));

		break;

	case EHasWeapon::HasWeapon:

		Fire();

		break;

	default:
		break;
	}
}

void APlayerCharacter::FireReleased()
{
	switch (HasWeaponEnum)
	{
	case EHasWeapon::NoWeapon:

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("No Weapon!!!!!!"));

		break;

	case EHasWeapon::HasWeapon:

		StopFire();

		break;

	default:
		break;
	}
}

void APlayerCharacter::SetCurrentWeapon(AWeaponBase* WeaponToSet) { CurrentWeapon = WeaponToSet; }

void APlayerCharacter::FOnAimEnter() { OnAimEnter.Broadcast(); }

void APlayerCharacter::FOnAimExit() { OnAimExit.Broadcast(); }

void APlayerCharacter::StartJump() { Jump(); }

void APlayerCharacter::StopJump() { StopJumping(); }

void APlayerCharacter::StartSprint() { GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed; }

void APlayerCharacter::StopSprint() { GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed; }

void APlayerCharacter::SetShouldBeShown(bool ShouldBeShown) { bShouldBeShown = ShouldBeShown; }

