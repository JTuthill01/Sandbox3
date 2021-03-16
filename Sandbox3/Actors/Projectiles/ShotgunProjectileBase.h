#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ShotgunProjectileBase.generated.h"

UCLASS()
class SANDBOX3_API AShotgunProjectileBase : public AProjectileBase
{
	GENERATED_BODY()

protected:
	
	virtual void BeginPlay() override;
	virtual void ProjectileStop(const FHitResult& HitResult) override;

private:

	void SpawnImpact(const FHitResult& HitResult);
};
