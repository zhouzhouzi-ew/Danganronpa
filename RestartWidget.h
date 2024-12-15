// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RestartWidget.generated.h"


class UButton;
/**
 * 
 */
UCLASS(Blueprintable)
class DANGANRONPA_API URestartWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(meta = (BindWidget), Blueprintable)
	TObjectPtr<UButton> RestartButton;

	UPROPERTY(meta = (BindWidget),Blueprintable)
	TObjectPtr<UButton> ExitButton;

	virtual void NativeOnInitialized() override;
protected:
	UFUNCTION()
	void OnRestartClicked();
	UFUNCTION()
	void OnExitClicked();
};
