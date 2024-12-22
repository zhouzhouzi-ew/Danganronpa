// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NaegiController.generated.h"
class UBedroomAfterWidget;
class UKototamaWidget;
struct FKototama;
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

	

	UPROPERTY()
	TObjectPtr<UKototamaWidget>KototamaWidget;

	UPROPERTY()
	TObjectPtr< UDialogueWidget>DialogueWidget;

	UPROPERTY()
	TObjectPtr<UPlaygroundWidget>PlaygroundWidget;

	UPROPERTY()
	TObjectPtr<UInventoryWidget>InventoryWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBedroomAfterWidget>BedroomAfterWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UKototamaWidget>KototamaWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDialogueWidget>DialogueWidgetClass;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPlaygroundWidget>PlaygroundWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryWidget>InventoryWidgetClass;

	void CreateDialogueWidget();

	UPROPERTY()
	TObjectPtr< UBedroomAfterWidget>BedroomAfterWidget;
	
	void GetKototama(FKototama* Kototama);
	/*FSlateBrush DefaultBrush;
	DefaultBrush.SetResourceObject(LoadObject<UTexture2D>(nullptr, TEXT("Content/resources/images/DanganCursor_Idle")));

	FSlateBrush HoverBrush;
	HoverBrush.SetResourceObject(LoadObject<UTexture2D>(nullptr, TEXT("Content/resources/images/DanganCursor_Focus")));*/
private:
	FTimerHandle TimerHandle1;
};
