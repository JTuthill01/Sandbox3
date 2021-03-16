#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarHammer.generated.h"

UCLASS()
class SANDBOX3_API AWarHammer : public AActor
{
	GENERATED_BODY()
	
public:	

	AWarHammer();

	FORCEINLINE FName GetHammerSocketName() const { return SocketName; }

	UFUNCTION(BlueprintCallable)
	void SetDamageToDeal(int DamageDelt) { DamageToDeal = DamageDelt; }

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SpawnImpact(const FHitResult& HitResult);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	USkeletalMeshComponent* HammerMesh;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UCapsuleComponent* CollisionCapsule;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class APlayerCharacter* Player;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class AImpactEffects* Impact;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AImpactEffects> ImpactEffect;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class AWeaponBase* Damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName SocketName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int DamageToDeal;
};
