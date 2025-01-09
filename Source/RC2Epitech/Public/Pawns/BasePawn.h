#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "BasePawn.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class USoundBase;
class AProjectile;

UCLASS()
class RC2EPITECH_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	void RotateTurret(FVector LookAtTarget);

	UPROPERTY(EditAnywhere, Category = "Canon properties")
	float InterpSpeed = 5.f;

	void Fire();

private:
	UPROPERTY(VisibleAnywhere, BlueprintreadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere, BlueprintreadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintreadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintreadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Combat Properties")
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat Properties")
	FVector ProjectileScale = FVector(2.0f, 2.0f, 2.0f);

	UPROPERTY(EditAnywhere, Category = "Combat Properties")
	USoundCue* FireSFX;

};
