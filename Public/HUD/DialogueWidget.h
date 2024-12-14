// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include"DTReader.h"
#include "TimerManager.h"
#include "DialogueWidget.generated.h"
class UButton; 
class UTextBlock;
class UWidgetAnimation;
class UImage;
/**
 * 
 */
UCLASS()
class DANGANTEST2_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton>TextBubble;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>GoldenKatana;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>Drawer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>ScratchOnFloor;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>BathRoomDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient,meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation>BedroomAfterFade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation>BathroomFade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation>Flash;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> MyDialogue;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> KatanaDialogue;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> DrawerDialogue;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> ScratchDialogue;

	// 绑定的TextBlock
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DialogueText;

	int32 TextIndex;
	int32 InvesIndex=-1;
	TArray<FDialogData*>Dialogues;
	TArray<FDialogData*>Dialogues_Inves;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Monokuma_BigLaugh;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Kirigiri_Firm;
protected:
	UFUNCTION()
	void OnBubbleClicked();

	UFUNCTION()
	void OnDoorClicked();

	UFUNCTION()
	void OnKatanaClicked();

	UFUNCTION()
	void OnScratchClicked();

	UFUNCTION()
	void OnDrawerClicked();
private:
	bool LookForMaizono;
	bool InBedroom;
	bool InBathroom;
	bool InMainDialogue=true;
	bool InvestigatePhase = false;
	void SetTextAndBubbleHidden();

	void SetTextAndBubbleVisible();
	//获取定时器管理器
	FTimerHandle TimerHandle1;
	FTimerHandle TimerHandle2;
	void InitializePortraits();
	//让文本框重新出现且内容往前，delay为出现的延迟时间
	void TextMoveOn(float delay = 4.0f);

	TObjectPtr<UImage> CurrentPortrait;

	void SetPortraitVisible();
	void SetPortraitHidden();

	TObjectPtr<UDataTable> CurrentDialogue;
};
