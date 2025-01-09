#include "Pawns/BasePawn.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectiles/Projectile.h"
#include "Sound/SoundCue.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// Construct box component
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base mesh"));
	BaseMesh->SetupAttachment(BoxComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet SpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			InterpSpeed));
}

void ABasePawn::Fire()
{
	FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator ProjectileSpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
	FVector Scale = ProjectileScale;
	FTransform SpawnProjectileTransform(ProjectileSpawnRotation, ProjectileSpawnPointLocation, Scale);

	if (ProjectileClass != nullptr)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnProjectileTransform);
		Projectile->SetOwner(this);

		if (FireSFX)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				FireSFX,
				GetActorLocation());
		}
	}
}

