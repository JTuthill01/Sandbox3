#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarHammerPickup.generated.h"

class AWarHammer;

UCLASS()
class SANDBOX3_API AWarHammerPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWarHammerPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USphereComponent* Sphere;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UStaticMeshComponent* HammerMesh;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class APlayerCharacter* PlayerRef;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName WeaponName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AWarHammer> Hammer;
};
