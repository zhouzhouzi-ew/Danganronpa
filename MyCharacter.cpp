#include "MyCharacter.h"
#include "DialoguePlayerController.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	Death();

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCharacter::Death()
{
	UE_LOG(LogTemp, Warning, TEXT("Death"));
	ADialoguePlayerController* PlayerController = Cast<ADialoguePlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		
		PlayerController->ShowRestartWidget();
	}
}
