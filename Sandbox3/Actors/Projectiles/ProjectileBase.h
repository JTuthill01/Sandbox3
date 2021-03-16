#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sandbox3/Actors/Weapons/WeaponBase.h"
#include "ProjectileBase.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProjectileStopDelegate, const FHitResult&, ImpactResult);

UCLASS()
class SANDBOX3_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UParticleSystemComponent* TrailFX;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class APlayerCharacter* PlayerRef;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AWeaponBase* Damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsCausingRadiusDamage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AImpactEffects> ImpactEffect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AExplosionImpulse> Impulse;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class AImpactEffects* Effect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CriticalHitModifier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FAmmoData AmmoData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTransform HitLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTransform EffectHitTransform;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator EmptyRotation;

protected:
	UFUNCTION(BlueprintCallable)
	virtual void ProjectileStop(const FHitResult& HitResult);

	UFUNCTION(BlueprintCallable)
	virtual void ExplodeOnImpact(const FHitResult& HitResult);

	UFUNCTION()
	virtual void SpawnImpulse(const FHitResult& HitResult);

	UFUNCTION()
	virtual void Spawn(const FHitResult& HitResult);

private:
	
};
