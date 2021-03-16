#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectileBase_GrenadeLauncher.generated.h"

UCLASS()
class SANDBOX3_API AProjectileBase_GrenadeLauncher : public AProjectileBase
{
	GENERATED_BODY()

public:
	AProjectileBase_GrenadeLauncher();

protected:
	
	virtual void BeginPlay() override;
	virtual void ProjectileStop(const FHitResult& HitResult) override;
	virtual void ExplodeOnImpact(const FHitResult& HitResult) override;

private:

	void SpawnImpact(const FHitResult& HitResult);
	void SpawnImpulse(const FHitResult& HitResult);
	
};
