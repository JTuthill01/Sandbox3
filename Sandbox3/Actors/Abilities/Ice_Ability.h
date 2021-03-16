#pragma once

#include "CoreMinimal.h"
#include "AbilitiesBase.h"
#include "Ice_Ability.generated.h"

UCLASS()
class SANDBOX3_API AIce_Ability : public AAbilitiesBase
{
	GENERATED_BODY()
	
public:
	AIce_Ability();

protected:
	virtual void BeginPlay() override;
	virtual void AbilityHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
};
