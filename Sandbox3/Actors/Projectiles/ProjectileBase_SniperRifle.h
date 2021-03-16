#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectileBase_SniperRifle.generated.h"

UCLASS()
class SANDBOX3_API AProjectileBase_SniperRifle : public AProjectileBase
{
	GENERATED_BODY()
	
protected:

	virtual void ProjectileStop(const FHitResult& HitResult) override;

private:

	void SpawnImpact();

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FAmmoData SniperRifleAmmoData;
};
