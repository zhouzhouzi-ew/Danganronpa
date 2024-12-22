#include "MyCharacter.h"
#include "../danganronpaProjectile.h"
#include "Blueprint/UserWidget.h"

#include "DialoguePlayerController.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>



// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnProjectileScene = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnProjectileScene"));
	SpawnProjectileScene->SetupAttachment(RootComponent);

	// ��ʼ��
	CurrentRotationIndex = 0;
	RotationAngles = { 120.f, 300.f, 250.f, 0.f, 60.f };  // ��ת�Ƕ�˳��
	RotationTimeElapsed = 0.f;
	MaxRotationTime = 60.f;  // ���������תʱ��Ϊ 300 ��


	

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Death();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		// ����Ϊ��Ϸģʽ����
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		// ȷ�����������
		PlayerController->bShowMouseCursor = false;
	}

	

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotationTimeElapsed += DeltaTime;
	
	// ���������ƽ����ת
	SmoothCameraRotation(DeltaTime);

	// �����������
	CheckDeathCondition();
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::StartCameraRotationCycle);


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

void AMyCharacter::FireProjectile()
{
	UE_LOG(LogTemp, Warning, TEXT("FireProjectile"));

	// ��ȡ��ҿ�����
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	FVector SpawnLocation = FVector::ZeroVector;  // ��ʼ�� SpawnLocation

	if (PlayerController)
	{
		// ��Ļ���� (0, 0) Ϊ���½�
		FVector2D ScreenPosition(0.f, 0.f); // ��Ļ���½ǵ�����

		// ����Ļ����ת��Ϊ��������
		FVector WorldLocation, WorldDirection;
		UGameplayStatics::DeprojectScreenToWorld(PlayerController, ScreenPosition, WorldLocation, WorldDirection);

		// ʹ��ת���������������Ϊ���λ��
		SpawnLocation = WorldLocation;
	}

	FRotator SpawnRotation = CalculateSpawnRotation();

	// ���� Spawn Parameters
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;  // ���������ߣ�ͨ��Ϊ��ǰ Actor
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AActor* SpawnedProjectile = GetWorld()->SpawnActor<AdanganronpaProjectile>
		(DanGanProjectile, SpawnLocation, SpawnRotation, SpawnParams);

}

FRotator AMyCharacter::CalculateSpawnRotation()
{
	FVector StartLocation = SpawnProjectileScene->GetComponentLocation();

	FVector Endlocation = { 0,0,0 };
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		float MouseX, MouseY;
		PlayerController->GetMousePosition(MouseX, MouseY);

		// ����Ļ����ת��Ϊ��������
		FVector MouseWorldLocation;
		FVector MouseWorldDirection;

		UGameplayStatics::DeprojectScreenToWorld(PlayerController, FVector2D(MouseX, MouseY),
			MouseWorldLocation, MouseWorldDirection);

		FVector LineTraceEnd = MouseWorldLocation + (MouseWorldDirection * 80000.0f);

		FHitResult HItResult;

		TArray<AActor*> ActorsToIgnore;

		bool bHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), StartLocation, LineTraceEnd,
			ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HItResult, true,
			FLinearColor::Red, FLinearColor::Green, 5);

		if (bHit)
		{
			Endlocation = HItResult.ImpactPoint;
		}
		else
		{
			Endlocation = HItResult.TraceEnd;
		}
		// ��ӡ FVector ��ֵ��ToString() �᷵�� "X=0.000000 Y=0.000000 Z=0.000000"
		UE_LOG(LogTemp, Warning, TEXT("EndLocation: %s"), *Endlocation.ToString());
	}

	FVector StartLoc = SpawnProjectileScene->GetComponentLocation();

	FRotator ReturnValue = UKismetMathLibrary::FindLookAtRotation(StartLoc, Endlocation);
	// ��ӡ FVector ��ֵ


	return ReturnValue;

}


void AMyCharacter::StartCameraRotationCycle()
{
	// ����ÿ3���л���ת�ǶȵĶ�ʱ��
	GetWorld()->GetTimerManager().SetTimer(RotationTimerHandle, this, &AMyCharacter::ChangeCameraRotation, 2.0f, true);
}

void AMyCharacter::StopCameraRotationCycle()
{
	// ֹͣ��תѭ��
	GetWorld()->GetTimerManager().ClearTimer(RotationTimerHandle);
}

void AMyCharacter::ChangeCameraRotation()
{
	// ��ȡ��һ��Ŀ����ת�Ƕ�
	if (RotationAngles.Num() > 0)
	{
		// ѭ��������ת�Ƕ�
		CurrentRotationIndex = (CurrentRotationIndex + 1) % RotationAngles.Num();
		float TargetYaw = RotationAngles[CurrentRotationIndex];

		// ��ȡ��ǰ���������ת
		if (CameraComponent)
		{
			FRotator CurrentRotation = CameraComponent->GetComponentRotation();

			// ����һ��Ŀ����ת��ֻ�ı�Yaw�Ƕ�
			FRotator TargetRotation = CurrentRotation;
			TargetRotation.Yaw = TargetYaw;

			

			// ʹ�� SetControlRotation �����¿���������ת
			Controller->SetControlRotation(TargetRotation);
		}
	}
}


void AMyCharacter::SmoothCameraRotation(float DeltaTime)
{
	// ÿ֡ƽ��������ת������������SpringArm���ڣ�
	if (CameraComponent && SpringArmComponent)
	{
		FRotator CurrentRotation = CameraComponent->GetComponentRotation();
		FRotator TargetRotation = CameraComponent->GetComponentRotation();

		// ʹ�� FInterpTo ��ƽ��������ת
		FRotator SmoothedRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 5.0f);
		CameraComponent->SetWorldRotation(SmoothedRotation);
	}
}

void AMyCharacter::CheckDeathCondition()
{
	if (!ifDeath)
	{
		// �ۼ���תʱ��
		RotationTimeElapsed += GetWorld()->GetDeltaSeconds();

		// ����ۼ�ʱ�䳬��300�룬������������
		if (RotationTimeElapsed >= MaxRotationTime)
		{
			Death();  // �������� Death() ������ Character ��
			ifDeath++;
		}
	}
	
	
}

