// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/DataTable.h" // ���� DataTable ֧��
#include "UObject/NoExportTypes.h"
#include "DialogueManager.generated.h"

// ����Ի�����нṹ
USTRUCT(BlueprintType)
struct FDialogueRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FString CharacterName; // ��ɫ����

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FString DialogueText; // �Ի�����

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    UTexture2D* CharacterImage; // ��ɫ����
};



UCLASS()
class DANGANRONPA_API ADialogueManager : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADialogueManager();

    // ��ǰ�Ի���
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    UDataTable* DialogueTable;

    // ��ǰ�Ի�����
    UPROPERTY(BlueprintReadWrite, Category = "Dialogue")
    int32 CurrentIndex = 0;

    // ��ȡ��ǰ�Ի�
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    bool GetNextDialogue(FString& OutCharacterName, FString& OutDialogueText, UTexture2D*& OutCharacterImage);

   


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
