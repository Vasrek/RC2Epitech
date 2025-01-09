#pragma once

#include "CoreMinimal.h"
#include "Pawns/BasePawn.h"
#include "InputActionValue.h"
#include "Tank.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class RC2EPITECH_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* PlayerContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MovementAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* CameraAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* FireAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float Speed = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float TurnRate = 45.f;

	APlayerController* TankController;
	
};
