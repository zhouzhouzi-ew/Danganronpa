// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NaegiController.h"
#include <HUD/DialogueWidget.h>

void ANaegiController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Begin Play"));
	
	CreateDialogueWidget();
}

void ANaegiController::CreateDialogueWidget()
{
	if (DialogueWidgetClass != nullptr)
	{
		//SetPause(true);
		SetInputMode(FInputModeUIOnly());//仅支持UI输入

		bShowMouseCursor = true;
		DialogueWidget = CreateWidget<UDialogueWidget>(this, DialogueWidgetClass);
		if (DialogueWidget) {
			DialogueWidget->AddToViewport();
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Subclass Fail"));
		}
		

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Class"));
	}
}
