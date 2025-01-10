#include "GameModes/TankGameMode.h"
#include "Pawns/Tank.h"
#include "Pawns/Tower.h"
#include "Kismet/GameplayStatics.h"


void ATankGameMode::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATankGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->DisableInput(Tank->GetTankPlayerController());
		Tank->GetTankPlayerController()->bShowMouseCursor = false;
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->Destroy();
	}
}

