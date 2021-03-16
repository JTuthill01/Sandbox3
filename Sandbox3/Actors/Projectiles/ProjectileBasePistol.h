#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectileBasePistol.generated.h"

UCLASS()
class SANDBOX3_API AProjectileBasePistol : public AProjectileBase
{
	GENERATED_BODY()
	
public:
	AProjectileBasePistol();

protected:
	virtual void BeginPlay() override;
	virtual void ProjectileStop(const FHitResult& HitResult) override;

private:

	void SpawnImpact(const FHitResult& HitResult);
};
