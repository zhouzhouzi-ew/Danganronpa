// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include"HUD/DTReader.h"
#include "DialogueWidgetBase.generated.h"
class UButton;
class UTextBlock;
class UWidgetAnimation;
class UImage;
/**
 * 
 */
UCLASS()
class DANGANTEST2_API UDialogueWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>TextBubble;

	// �󶨵�TextBlock
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DialogueText;

	int32 TextIndex;

	TArray<FDialogData*>Dialogues;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> MainDialogue;//                            DataTables

	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> KototamaTable;

	virtual void InitializePortraits();

	TArray<FName>_rowNames;

	UFUNCTION()
	virtual void OnBubbleClicked();


	
	//���ı������³�����������ǰ��delayΪ���ֵ��ӳ�ʱ��
	void TextMoveOn(float delay = 4.0f);

	TObjectPtr<UImage> CurrentPortrait;

	void SetPortraitVisible();
	void SetPortraitHidden();

	//��ȡ��ʱ��������
	FTimerHandle TimerHandle1;
	FTimerHandle TimerHandle2;

	void SetTextAndBubbleHidden();

	void SetTextAndBubbleVisible();

	bool EndMap = false;
};
