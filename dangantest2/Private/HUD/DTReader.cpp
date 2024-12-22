// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/DTReader.h"

// Sets default values
ADTReader::ADTReader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADTReader::BeginPlay()
{
	Super::BeginPlay();
	
	FName _rowname = FName(TEXT("1"));
	FString ContextString = TEXT("TEST");
	
    try
    {
        if (!MyDialogue)
        {
            throw std::runtime_error("MyDialogue is null.");
        }

        TArray<FDialogData*> Dialogues;
        MyDialogue->GetAllRows(ContextString, Dialogues); // Dialogues�ѻ�ȡDataTable��������Ϣ
        DialogueData = Dialogues;

        FDialogData* _data = MyDialogue->FindRow<FDialogData>(_rowname, ContextString, false); // false��������

        if (!_data)
        {
            throw std::runtime_error("Failed to find the specified row in the DataTable.");
        }

        // �����Ҫ���� Dialogues �����ݣ����Լ�������߼�
    }
    catch (const std::exception& e)
    {
        UE_LOG(LogTemp, Error, TEXT("Exception occurred: %s"), *FString(e.what()));
    }

}

// Called every frame
void ADTReader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

