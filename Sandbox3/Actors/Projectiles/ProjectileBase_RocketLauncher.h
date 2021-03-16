#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectileBase_RocketLauncher.generated.h"

UCLASS()
class SANDBOX3_API AProjectileBase_RocketLauncher : public AProjectileBase
{
	GENERATED_BODY()

public:
	AProjectileBase_RocketLauncher();
	
protected:
	virtual void BeginPlay() override;
	virtual void ProjectileStop(const FHitResult& HitResult) override;
	virtual void ExplodeOnImpact(const FHitResult& HitResult) override;

private:

	void SpawnImpact(const FHitResult& HitResult);
	void SpawnImpulse(const FHitResult& HitResult);

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FAmmoData RocketLauncherAmmoData;
};
