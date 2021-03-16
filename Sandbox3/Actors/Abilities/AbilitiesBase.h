#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystem.h"
#include "AbilitiesBase.generated.h"

UCLASS()
class SANDBOX3_API AAbilitiesBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbilitiesBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void AbilityToSpawn();

	UFUNCTION(BlueprintCallable)
	virtual void AbilityHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraComponent* NAbility;

	class APlayerCharacter* PlayerRef;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* VFX_Ability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* AbilityCollision;*/

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProjectileMovementComponent* MovementComponent;*/
};
