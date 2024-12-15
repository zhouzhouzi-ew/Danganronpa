// Fill out your copyright notice in the Description page of Project Settings.


#include "DialoguePlayerController.h"
#include"HUD/RestartWidget.h"


void ADialoguePlayerController::ShowRestartWidget()
{
	if (RestartWidgetClass != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Daaa"));
		SetPause(true);
		SetInputMode(FInputModeUIOnly());

		bShowMouseCursor = true;
		RestartWidget = CreateWidget<URestartWidget>(this, RestartWidgetClass);
		RestartWidget->AddToViewport();

	}
	
}
void ADialoguePlayerController::HideRestartWidget()
{
	RestartWidget->RemoveFromParent();
	RestartWidget->Destruct();
	SetPause(false);
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}
