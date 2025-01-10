#include "Components/HealthComponent.h"

#include "GameModes/TankGameMode.h"
#include "Kismet/GameplayStatics.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	TankGameMode = Cast<ATankGameMode>(UGameplayStatics::GetGameMode(this));
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;

	CurrentHealth -= Damage;
	if (CurrentHealth <= 0.f)
	{
		CurrentHealth = 0;
		TankGameMode->ActorDied(DamagedActor);
	}
}



