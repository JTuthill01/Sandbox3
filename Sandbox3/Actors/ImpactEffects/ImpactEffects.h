#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ImpactEffects.generated.h"

UCLASS()
class SANDBOX3_API AImpactEffects : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AImpactEffects();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", Meta = (ExposeOnSpawn = true))
	bool bIsUsingHitResult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", Meta = (ExposeOnSpawn = true))
	FRotator DecalRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", Meta = (ExposeOnSpawn = true))
	FHitResult HitResult;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void SetDecalRotation(FHitResult& Hit);

	UFUNCTION()
	void SpawnFX(FHitResult& Hit);

	UFUNCTION()
	void SpawnSound(FHitResult& Hit);

	UFUNCTION()
	void SpawnDecal(FHitResult& Hit);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystem* DefaultFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystem* ConcreteFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystem* FleshFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* DefaultSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* FleshSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* ConcreteSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	class UMaterialInterface* DefaultDecalMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	class UMaterialInterface* FleshDecalMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	class UMaterialInterface* ConcreteDecalMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DecalSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DecalLifeSpan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName HitName;
};
