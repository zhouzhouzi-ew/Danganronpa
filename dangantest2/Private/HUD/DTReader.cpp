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
        MyDialogue->GetAllRows(ContextString, Dialogues); // Dialogues已获取DataTable所有行信息
        DialogueData = Dialogues;

        FDialogData* _data = MyDialogue->FindRow<FDialogData>(_rowname, ContextString, false); // false代表不报错

        if (!_data)
        {
            throw std::runtime_error("Failed to find the specified row in the DataTable.");
        }

        // 如果需要处理 Dialogues 的内容，可以继续添加逻辑
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

