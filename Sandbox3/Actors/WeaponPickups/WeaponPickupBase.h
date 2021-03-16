#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponPickupBase.generated.h"

class AWeaponBase;

UCLASS()
class SANDBOX3_API AWeaponPickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponPickupBase();

	FORCEINLINE UStaticMeshComponent* GetMesh() { return WeaponMesh; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USphereComponent* Sphere;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class APlayerCharacter* PlayerRef;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName WeaponName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AWeaponBase> Weapon;
};
