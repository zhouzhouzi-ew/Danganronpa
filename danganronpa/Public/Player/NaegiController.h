// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NaegiController.generated.h"
class UDialogueWidget;
class UPlaygroundWidget;
class UInventoryWidget;
/**
 * 
 */
UCLASS()
class DANGANTEST2_API ANaegiController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDialogueWidget>DialogueWidgetClass;

	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPlaygroundWidget>PlaygroundWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryWidget>InventoryWidgetClass;

	void CreateDialogueWidget();

	UPROPERTY()
	TObjectPtr< UDialogueWidget>DialogueWidget;
	
	UPROPERTY()
	TObjectPtr<UPlaygroundWidget>PlaygroundWidget;

	UPROPERTY()
	TObjectPtr<UInventoryWidget>InventoryWidget;
	
private:
	FTimerHandle TimerHandle1;
};
