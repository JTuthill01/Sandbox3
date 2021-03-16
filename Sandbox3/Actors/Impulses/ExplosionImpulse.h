#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosionImpulse.generated.h"

UCLASS()
class SANDBOX3_API AExplosionImpulse : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosionImpulse();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class URadialForceComponent* RadialForce;
};
