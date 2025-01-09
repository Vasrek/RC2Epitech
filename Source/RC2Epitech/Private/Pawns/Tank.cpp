#include "Pawns/Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 600;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MovementAction)
		{
			EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ATank::Move);
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ThisClass::Fire);
		}
	}
	
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankController = Cast<APlayerController>(GetController());
	if (TankController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(TankController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerContext, 0);
		}
	}
}

void ATank::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

		if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			FHitResult HitResult;
			PlayerController->GetHitResultUnderCursor(
				ECC_Visibility,
				false,
				HitResult
			);

			RotateTurret(HitResult.ImpactPoint);
		}
	
}

void ATank::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		FVector DeltaLocation = FVector::ZeroVector;
		DeltaLocation.X = MovementVector.Y * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
		AddActorLocalOffset(DeltaLocation, true);

		FRotator DeltaRotation = FRotator::ZeroRotator;
		DeltaRotation.Yaw = MovementVector.X * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
		AddActorLocalRotation(DeltaRotation, true);
	}
}

void ATank::Look(const FInputActionValue& Value)
{
	
}


