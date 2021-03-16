#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "WarHammerAnimNotifyState.generated.h"

UCLASS()
class SANDBOX3_API UWarHammerAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UWarHammerAnimNotifyState();

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
