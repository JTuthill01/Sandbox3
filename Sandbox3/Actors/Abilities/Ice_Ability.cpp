#include "Ice_Ability.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sandbox3/Character/PlayerCharacter.h"

AIce_Ability::AIce_Ability()
{

}

void AIce_Ability::BeginPlay()
{
	Super::BeginPlay();
}

void AIce_Ability::AbilityHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::AbilityHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	FRotator TempRot;
	FVector TempScale = FVector(1.F);

	AActor* TempActor = Cast<AActor>(PlayerRef);

	if (OtherActor != this && OtherActor != TempActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.F, FColor::Red, TEXT("HIT"));
	}

	
}
