#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameMode.generated.h"

class ATank;
class ATankPlayerController;

/**
 * 
 */
UCLASS()
class RC2EPITECH_API ATankGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

private:
	ATank* Tank;
	ATankPlayerController* TankPlayerController;
	
	
};
