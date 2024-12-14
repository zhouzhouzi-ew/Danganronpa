// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NaegiController.generated.h"
class UDialogueWidget;
class UKototamaWidget;
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
	TSubclassOf<UKototamaWidget>KototamaWidgetClass;

	void CreateDialogueWidget();

	UPROPERTY()
	TObjectPtr< UDialogueWidget>DialogueWidget;
	/*FSlateBrush DefaultBrush;
	DefaultBrush.SetResourceObject(LoadObject<UTexture2D>(nullptr, TEXT("Content/resources/images/DanganCursor_Idle")));

	FSlateBrush HoverBrush;
	HoverBrush.SetResourceObject(LoadObject<UTexture2D>(nullptr, TEXT("Content/resources/images/DanganCursor_Focus")));*/
};
