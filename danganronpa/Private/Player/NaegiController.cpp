// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NaegiController.h"
#include <HUD/ClassroomWidget.h>
#include <HUD/PlaygroundWidget.h>
#include <HUD/InventoryWidget.h>
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
void ANaegiController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Begin Play"));
	CreateDialogueWidget();
}

void ANaegiController::CreateDialogueWidget()
{
    
    // ��������ģʽ
    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;

    // ��ȡ��ǰ�ؿ���
    FName CurrentLevel = *UGameplayStatics::GetCurrentLevelName(this);

    // ���ݹؿ���������Ӧ�� Widget
    if (CurrentLevel == FName("Map_Classroom"))
    {
        DialogueWidget = CreateWidget<UDialogueWidget>(this, DialogueWidgetClass);
        if (DialogueWidget)
        {
            DialogueWidget->AddToViewport();
            UE_LOG(LogTemp, Log, TEXT("DialogueWidget Added to Viewport"));
        }
    }
    else if (CurrentLevel == FName("Map_Playground"))
    {
        PlaygroundWidget = CreateWidget<UPlaygroundWidget>(this, PlaygroundWidgetClass);
        if (PlaygroundWidget)
        {
            PlaygroundWidget->AddToViewport();
            UE_LOG(LogTemp, Log, TEXT("PlaygroundWidget Added to Viewport"));
        }
    }
    else if (CurrentLevel == FName("TestLevel"))
    {
        InventoryWidget = CreateWidget<UInventoryWidget>(this, InventoryWidgetClass);
        if (InventoryWidget)
        {
            InventoryWidget->AddToViewport();
            UE_LOG(LogTemp, Log, TEXT("InventoryWidget Added to Viewport"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No matching level found for Widgets."));
    }
}



