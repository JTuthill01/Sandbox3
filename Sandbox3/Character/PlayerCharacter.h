#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Sandbox3/Actors/Weapons/WeaponBase.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteract);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAimEnter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAimExit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStopFire);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFireWeapon, EWeaponType, Weapon);

UENUM(BlueprintType)
enum class EHasWeapon : uint8 { NoWeapon, HasWeapon };

UENUM(BlueprintType)
enum class EWeaponSlot : uint8 { First_Slot, Second_Slot, Third_Slot };

UENUM(BlueprintType)
enum class EWEaponReloadType : uint8 { Pistol_Reload, Rifle_Reload };

UCLASS()
class SANDBOX3_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	void SetShouldBeShown(bool ShouldBeShown);

	UPROPERTY(BlueprintAssignable)
	FInteract OnInteract;

	UPROPERTY(BlueprintAssignable)
	FStopFire OnStopFire;

	UPROPERTY(BlueprintAssignable)
	FFireWeapon OnFireWeapon;

	UPROPERTY(BlueprintAssignable)
	FAimEnter OnAimEnter;

	UPROPERTY(BlueprintAssignable)
	FAimExit OnAimExit;

	UFUNCTION(BlueprintCallable)
	void FOnAimEnter();

	UFUNCTION(BlueprintCallable)
	void FOnAimExit();

	UFUNCTION(BlueprintCallable)
	void Reload();

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	void StopReload();

	UFUNCTION(BlueprintCallable)
	bool SpawnWeapon(TSubclassOf<AWeaponBase> WeaponToSpawn, bool& bIsSuccessful);

	UFUNCTION(BlueprintCallable)
	bool SpawnHammer(TSubclassOf<AWarHammer> HammerToSpawn, bool& bIsSuccessful);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AWeaponBase* CurrentWeapon;

	FORCEINLINE UCameraComponent* GetCamera() { return Camera;}
	FORCEINLINE void SetIsMelee(bool IsMelee) { bIsMelee = IsMelee; }
	FORCEINLINE FName GetSocketName() { return AbilitySocket; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bDo;

	void DoOnce(AWeaponBase* Weapon);
	void ResetDoOnce();

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(AWeaponBase* Weapon);

	UFUNCTION(BlueprintCallable)
	void ShowWeapon(AWeaponBase* Weapon);

	UFUNCTION(BlueprintCallable)
	void SetFOV(float FOV);

	UFUNCTION(BlueprintCallable)
	void StopFire();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void ADS_FOV();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lux")
	float MaxSprintSpeed = 900.F;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* Sleeve;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* Gloves;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimMontage* Melee;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lux")
	float BaseTurnRate = 45.F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lux")
	float BaseLookRate = 45.F;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseLookUpRate = 45.F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool bIsMelee;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsFirstSlotFull;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsSecondSlotFull;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsThirdSlotFull;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bCanFire;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bCanReload;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bCanSwitchWeapon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsReloading;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsChangingWeapon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsAiming;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsNearWall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsUsingAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsFirstSlotActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSecondSlotActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsThirdSlotActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasHammerSpawned;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName AbilitySocket;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EHasWeapon HasWeaponEnum;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EWeaponSlot EWeaponSlotEnum;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EWeaponType Type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AWeaponBase* WeaponSlot_01;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AWeaponBase* WeaponSlot_02;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class AWarHammer* HammerSpawn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float defaultFOV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle ReloadTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem* Ability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimSequence* AbilityAnim;

private:

	void MoveForward(float Value);
	void MoveRight(float Value);
	void MoveUp(float Value);
	void Turn(float Value);
	void TurnRate(float Value);
	void LookUp(float Value);
	void LookUpRate(float Value);

	void StartJump();
	void StopJump();
	void StartSprint();
	void StopSprint();
	void StartMeleeAttack();
	void HideHammer();
	void FirePressed();
	void FireReleased();
	void Interact();
	void Equip();
	void PlayAbility();

	void SetCurrentWeapon(AWeaponBase* WeaponToSet);

	float DefaultWalkSpeed;
	float AnimTime;
	float ReloadTime;

	bool bShouldBeShown;
};
