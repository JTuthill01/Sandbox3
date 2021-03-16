#pragma once

#include "CoreMinimal.h"
#include "ImpactEffects.h"
#include "GrenadeLauncherImpactEffects.generated.h"

UCLASS()
class SANDBOX3_API AGrenadeLauncherImpactEffects : public AImpactEffects
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
};
