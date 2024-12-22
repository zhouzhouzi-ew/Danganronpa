// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NaegiController.h"
#include <HUD/BedroomAfterWidget.h>
#include <HUD/KototamaWidget.h>
#include "TimerManager.h"
#include <HUD/DTReader.h>
#include "Kismet/GameplayStatics.h"
#include <HUD/DialogueWidget.h>
#include <HUD/PlaygroundWidget.h>
#include <HUD/InventoryWidget.h>
void ANaegiController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Begin Play"));
	KototamaWidget = CreateWidget<UKototamaWidget>(this, KototamaWidgetClass);
	CreateDialogueWidget();
}

void ANaegiController::CreateDialogueWidget()
{
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
	else if(CurrentLevel == FName("Map_BedroomAfter1")){
		if (BedroomAfterWidgetClass != nullptr)
		{
			//SetPause(true);
			SetInputMode(FInputModeUIOnly());//��֧��UI����

			bShowMouseCursor = true;
			BedroomAfterWidget = CreateWidget<UBedroomAfterWidget>(this, BedroomAfterWidgetClass);

			if (BedroomAfterWidget) {
				BedroomAfterWidget->AddToViewport();
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Subclass Fail"));
			}


		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Class"));
	}
}


void ANaegiController::GetKototama(FKototama* Kototama)
{
	KototamaWidget->SetName(Kototama->Name);
	KototamaWidget->SetDescription(Kototama->Description);
	KototamaWidget->SetImage((Kototama->Image));
	KototamaWidget->AddToViewport();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle1, FTimerDelegate::CreateLambda([this]()
		{
			if (KototamaWidget)
			{
				KototamaWidget->RemoveFromParent();
			}
		}), 3.0f, false);

}
/*UTexture2D* NewTexture, const FText& NewName, const FText& NewDescription*/