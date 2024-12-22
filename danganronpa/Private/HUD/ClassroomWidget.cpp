// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ClassroomWidget.h"
#include"Components/Button.h"
#include"Components/TextBlock.h"
#include"Components/Image.h"
#include<Player/NaegiController.h>
#include "HUD/DTReader.h"
#include "Animation/WidgetAnimation.h"
#include"HUD/KototamaWidget.h"
#include "Kismet/GameplayStatics.h"

void UDialogueWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	InitializePortraits();
	FName _rowname = FName(TEXT("1"));
	FString ContextString = TEXT("TEST");
	
	
	if (MyDialogue)
	{
		MyDialogue->GetAllRows(ContextString, Dialogues);//Dialogues�ѻ�ȡDataTable��������Ϣ
		FDialogData* _data = MyDialogue->FindRow< FDialogData>(_rowname, ContextString, false);//false��������
		// �����ı�������
		DialogueText->SetText(FText::FromString(Dialogues[TextIndex]->DialogueText));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No connected DT"));
	}
}

void UDialogueWidget::OnBubbleClicked()
{
	if (bIsAnimating) {
		// ������ڲ��Ŷ�����ֱ�ӷ��أ������ظ�����
		UE_LOG(LogTemp, Warning, TEXT("Animation is in progress. Ignoring further clicks."));
		return;
	}

	if (TextIndex < Dialogues.Num()) {
		if (Dialogues[TextIndex]->out) {
			UE_LOG(LogTemp, Warning, TEXT("Sensed Out"));
			SetPortraitHidden();
			SetTextAndBubbleHidden();

			if (InMainDialogue) {
				if (TextIndex == 2) {
					InvestigatePhase = true;
				}
				if (TextIndex == Dialogues.Num() - 1 && InvestigatePhase && PaperRead && CameraRead) {
					PlayAnimate();
					InvestigatePhase = false;
				}
				else if (TextIndex == 3) {
					bIsAnimating = true; // ��Ƕ������ڲ���

					// �������ض���
					PlayAnimation(BroadcastFade);
					SetTextAndBubbleHidden();

					// �ӳ��л��� MyDialogue �ĵ����仰
					GetWorld()->GetTimerManager().SetTimer(
						TimerHandle1,
						[this]() {
							// ��ʾ�����仰
							TextIndex = 4;
							DialogueText->SetText(FText::FromString(Dialogues[TextIndex]->DialogueText));

							// ������ʾ��������ʾ�Ի���
							SetTextAndBubbleVisible();
							SetPortraitVisible();
							// ����������ɣ����ñ��
							bIsAnimating = false;
						},
						2.0f, // �ӳ� 1 ��
						false
					);
				}
				else if (TextIndex == 4) {
					// �Ի��������л����µĹؿ�
					UE_LOG(LogTemp, Warning, TEXT("Dialogue Finished. Loading Map_Playground..."));
					UGameplayStatics::OpenLevel(this, FName("Map_Playground"));
				}
			}
		}
		// �����������
		else if (Dialogues[TextIndex + 1]->intro) {
			SetPortraitHidden();
			TextIndex++;
			SetPortraitVisible();
			DialogueText->SetText(FText::FromString(Dialogues[TextIndex]->DialogueText));
		}
		// ������ʾ��һ��
		else {
			DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
		}
	}
	else if (InvestigatePhase) {
		// ...
	}
	else {
		
	}
}




void UDialogueWidget::OnCameraClicked()
{
	TextIndex = -1;
	CameraRead = true;
	if (InvestigatePhase) {
		FString ContextString = TEXT("TEST");
		Dialogues.Empty();
		CameraDialogue->GetAllRows(ContextString, Dialogues);
		SetTextAndBubbleVisible();
		DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
	}
	
}

void UDialogueWidget::OnPaperClicked()
{
	TextIndex = -1; // ���öԻ�����
	PaperRead = true; // ��� Paper �Ի��Ѷ�

	if (InvestigatePhase) {
		FString ContextString = TEXT("TEST");
		Dialogues.Empty();
		PaperDialogue->GetAllRows(ContextString, Dialogues);

		// ��ʾ Paper �Ի��ĵ�һ�仰
		SetTextAndBubbleVisible();
		DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));

		// ���Ŷ����߼��� OnBubbleClicked ��������
	}
}




void UDialogueWidget::PlayAnimate()
{
	if (PaperRead && CameraRead) {
		TextMoveOn(0.0f); // �ӳٴ��������߼�
	}
}



void UDialogueWidget::SetTextAndBubbleHidden()
{
	TextBubble->SetVisibility(ESlateVisibility::Hidden);//��ť���ɼ��Ҳ��ɽ���
	DialogueText->SetVisibility(ESlateVisibility::Hidden);
}

void UDialogueWidget::SetTextAndBubbleVisible()
{
	TextBubble->SetVisibility(ESlateVisibility::Visible);
	DialogueText->SetVisibility(ESlateVisibility::Visible);
}

void UDialogueWidget::InitializePortraits()
{
	if (TextBubble != nullptr)
	{
		TextBubble->OnClicked.AddDynamic(this, &UDialogueWidget::OnBubbleClicked);
	}
	Broadcast->SetRenderOpacity(0.0f);
	Naegi_normal->SetVisibility(ESlateVisibility::Hidden);
	Naegi_talking->SetVisibility(ESlateVisibility::Hidden);
	Naegi_confused->SetVisibility(ESlateVisibility::Hidden);
	Camera->SetRenderOpacity(0.0f);
	Camera->OnClicked.AddDynamic(this, &UDialogueWidget::OnCameraClicked);
	Paper->SetRenderOpacity(0.0f);
	Paper->OnClicked.AddDynamic(this, &UDialogueWidget::OnPaperClicked);
}

void UDialogueWidget::TextMoveOn(float delay)
{
	// ȷ�� TextIndex ��λ�����Ϊ 3 �ĶԻ�
	int32 TargetIndex = 3;

	// ��� Dialogues �Ƿ���Ч����������Ϊ 3 �� 4 ������
	if (MyDialogue) {
		FString ContextString = TEXT("TEST");
		Dialogues.Empty();
		MyDialogue->GetAllRows(ContextString, Dialogues);

		if (Dialogues.IsValidIndex(TargetIndex) && Dialogues.IsValidIndex(TargetIndex + 1)) {
			// ��ʾ�� 3 �жԻ�
			TextIndex = TargetIndex;
			DialogueText->SetText(FText::FromString(Dialogues[TextIndex]->DialogueText));

			// ���ų��ֶ�������ʾ�Ի���
			PlayAnimation(BroadcastAppear);
			SetTextAndBubbleVisible();
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("Target Index 3 or 4 is out of range in Dialogues!"));
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("MyDialogue is NULL! Cannot load dialogues."));
	}
}



void UDialogueWidget::SetPortraitVisible()
{
	UE_LOG(LogTemp, Warning, TEXT("SettingPortraitVisible"));
	CurrentPortrait = Cast<UImage>(GetWidgetFromName(FName(Dialogues[TextIndex]->CharacterName)));
	//��ȡ��ǰ��˵����������
	if (CurrentPortrait)
	    CurrentPortrait->SetVisibility(ESlateVisibility::Visible);
}

void UDialogueWidget::SetPortraitHidden()
{
	CurrentPortrait = Cast<UImage>(GetWidgetFromName(FName(Dialogues[TextIndex]->CharacterName)));
	//��ȡ��ǰ��˵����������
	if(CurrentPortrait)
		CurrentPortrait->SetVisibility(ESlateVisibility::Hidden);
}



