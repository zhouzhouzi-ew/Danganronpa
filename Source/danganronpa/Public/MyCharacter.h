#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include <GameFramework/SpringArmComponent.h>
#include "Engine/DataTable.h"
#include "MyCharacter.generated.h"


class UUserWidget;
class AdanganronpaProjectile;
class UCameraComponent;


UCLASS()
class DANGANRONPA_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintCallable, Category = "Death")
	void Death();

	UPROPERTY(EditAnywhere, Category = "Projectile")
	USceneComponent* SpawnProjectileScene;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	bool bCurrentProjectileIsRight = true;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AdanganronpaProjectile> DanGanProjectile;


	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void FireProjectile();

	FRotator CalculateSpawnRotation();

	// ������������תѭ��
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void StartCameraRotationCycle();

	// ������ֹͣ��תѭ��
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void StopCameraRotationCycle();

	// ����������Ŀ����ת�Ƕ�
	UFUNCTION(BlueprintCallable)
	void ChangeCameraRotation();

	// ������ƽ����ת�����
	UFUNCTION(BlueprintCallable)
	void SmoothCameraRotation(float DeltaTime);

	// ��ʱ�����
	UPROPERTY(EditAnywhere, Category = "Rotation")
	FTimerHandle RotationTimerHandle;

	// ��ǰ��ת�Ƕȵ�����
	UPROPERTY(EditAnywhere, Category = "Rotation")
	int32 CurrentRotationIndex;

	// ��ת�Ƕ�����
	UPROPERTY(EditAnywhere, Category = "Rotation")
	TArray<float> RotationAngles;

	// �ۼ�ʱ��
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Rotation")
	float RotationTimeElapsed;

	// �����תʱ��
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float MaxRotationTime;

	// tick�������ü��
	UPROPERTY(EditAnywhere, Category = "Death")
	int32 ifDeath=0;

	// ����Ƿ�ﵽ�����תʱ��
	UFUNCTION(BlueprintCallable)
	void CheckDeathCondition();

	// �������SpringArm��������ã�������ͼ�ṩ
	UPROPERTY(EditAnywhere,  Category = "Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere,  Category = "Camera")
	USpringArmComponent* SpringArmComponent;

	/*UFUNCTION(BlueprintCallable, Category = "TalkingSystem")
	void OnInitLoadingWidget();

	UPROPERTY(EditAnywhere, Category = "TalkingSystem")
	TSubclassOf<UUserWidget> TalkingWidgetClass;

	UPROPERTY(EditAnywhere, Category = "TalkingSystem")
	UDataTable* TalkingDataTable;

	UPROPERTY()
	TObjectPtr <UUserWidget> CreatedTalkingWidget;*/

};

