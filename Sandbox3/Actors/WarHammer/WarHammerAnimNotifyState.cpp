#include "WarHammerAnimNotifyState.h"
#include "Sandbox3/Character/PlayerCharacter.h"

UWarHammerAnimNotifyState::UWarHammerAnimNotifyState() {}

void UWarHammerAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(MeshComp->GetOwner());

		if (Player != NULL)
		{
			Player->SetShouldBeShown(false);
			Player->SetIsMelee(false);
		}
	}
}
