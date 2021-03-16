#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class AProjectileBase;

UENUM(BlueprintType)
enum class EWeaponType : uint8 { Pistol, Rifle, Shotgun, GrenadeLauncher, RocketLauncher, SniperRifle, WarHammer };

UENUM(BlueprintType)
enum class EFireType : uint8 { Hitscan, Projectile };

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AWeaponBase> WeaponType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* IconImage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsEquipped;
};

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CritcalHit;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DamageRadius;
};

UCLASS()
class SANDBOX3_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBase();

	virtual void Tick(float DeltaTime) override;

	FORCEINLINE FName GetSocketName();

	UFUNCTION()
	virtual void SetWeaponEnum();

	UFUNCTION(BlueprintCallable)
	void WeaponReload();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AutomaticRecoil();

	UFUNCTION(BlueprintCallable)
	virtual void WeaponFire(EFireType FireType);

	UFUNCTION(BlueprintCallable)
	virtual void StopFire();

	UFUNCTION(BlueprintCallable)
	void OnAimEnter();

	UFUNCTION(BlueprintCallable)
	void OnAimExit();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void HasAmmoInMag(bool& bHasAmmo, bool& bIsMagFull);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void HasFullMag(bool& bIsMagFull);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void HasExtraAmmo(bool& bHasExtraAmmo);

	UFUNCTION(BlueprintCallable)
	void CalculateShot(class UCameraComponent* Camera, class USceneComponent* WMesh, FName WeaponFireSocketName, FHitResult& HitResult, FTransform& ProjectileTransform);

	UFUNCTION(BlueprintCallable)
	void AddDamage(FHitResult HitResult);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName SocketName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName MuzzleSocketName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class APlayerCharacter* PlayerRef;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimationAsset* WeaponAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimationAsset* ReloadAnim;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int currentAmmo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int maxMagAmmo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int currentTotalAmmo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int maxTotalAmmo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float reloadTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float critcalHitDamageModifier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float recoilIntensitity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float bulletSpread;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FAmmoData ammoData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UParticleSystem* TrailFX;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UParticleSystem* EmitterFX;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsAiming;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bHasMultipleBullets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsAutomatic;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float automaticFireRate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int bulletCount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EFireType fireType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem* AmmoEject;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AProjectileBase> Projectile;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	AProjectileBase* ProjectileToSpawn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AImpactEffects> ImpactEffects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float aimFOV;

	FTransform NewProjectileTransform;
	FTransform EmitterTransform;

	FORCEINLINE bool GetIsAiming() const;
	FORCEINLINE bool GetHasAmmo() const;
	FORCEINLINE bool GetIsMagfull() const;
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() { return WeaponMesh;}
	FORCEINLINE float GetAimFOV() const;

protected:
	virtual void BeginPlay() override;

	bool bAmmo;
	bool bMagFull;

	FTransform MuzzleLocation;

public:
	bool bHasAmmoInMag();
	bool bHasExtraAmmo();
	bool bHasFullMag();
	bool bExtraAmmo();
};
