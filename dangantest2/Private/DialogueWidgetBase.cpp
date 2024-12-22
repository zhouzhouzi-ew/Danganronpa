// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidgetBase.h"
#include"Components/Button.h"
#include"Components/TextBlock.h"
#include"Components/Image.h"
#include<GeneralController.h>
#include "HUD/DTReader.h"
#include "Animation/WidgetAnimation.h"
#include"HUD/KototamaWidget.h"
#include<GeneralController.h>
#include "Kismet/GameplayStatics.h"
void UDialogueWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Dialogues.Empty();
	InitializePortraits();
	TextIndex = 0;
	
	if (MainDialogue)
	{
		MainDialogue->GetAllRows("TEST", Dialogues);//Dialogues�ѻ�ȡDataTable��������Ϣ
		UE_LOG(LogTemp, Warning, TEXT("Dialogues array size: %d"), Dialogues.Num());
		if (Dialogues.IsValidIndex(0)) {
			UE_LOG(LogTemp, Warning, TEXT("happened"));
			FDialogData* _data = MainDialogue->FindRow< FDialogData>("1", "TEST", false);//false��������
			// �����ı�������
			DialogueText->SetText(FText::FromString(Dialogues[TextIndex]->DialogueText));
		}

	}
	else
		UE_LOG(LogTemp, Warning, TEXT("What's happened"));
}

void UDialogueWidgetBase::OnBubbleClicked()
{
	if (EndMap) {
		//�˴��л��ؿ�
	}
	if (TextIndex < Dialogues.Num()) {
		if (Dialogues[TextIndex]->out) {//�������ã�TextIndex��ͣ��outΪtrue�ĵط�
			UE_LOG(LogTemp, Warning, TEXT("Sensed Out"));
			SetPortraitHidden();
			//ִ������/���ٺ���
			SetTextAndBubbleHidden();
			
		}
		else if (Dialogues[TextIndex + 1]->intro) {//��������Ҫ��ʾ
			SetPortraitHidden();//������ǰ����
			TextIndex++;
			//UE_LOG(LogTemp, Warning, TEXT("CharacterName: %s"), *Dialogues[TextIndex]->CharacterName);
			SetPortraitVisible();
			DialogueText->SetText(FText::FromString(Dialogues[TextIndex]->DialogueText));
		}
		else {
			DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
		}

	}
}

void UDialogueWidgetBase::SetTextAndBubbleHidden()
{
	TextBubble->SetVisibility(ESlateVisibility::Hidden);//��ť���ɼ��Ҳ��ɽ���
	DialogueText->SetVisibility(ESlateVisibility::Hidden);
}

void UDialogueWidgetBase::SetTextAndBubbleVisible()
{
	TextBubble->SetVisibility(ESlateVisibility::Visible);
	DialogueText->SetVisibility(ESlateVisibility::Visible);
}

void UDialogueWidgetBase::InitializePortraits()
{
	if (TextBubble != nullptr)
	{
		TextBubble->OnClicked.AddDynamic(this, &UDialogueWidgetBase::OnBubbleClicked);
	}
}

void UDialogueWidgetBase::TextMoveOn(float delay)
{
	if (Dialogues[TextIndex + 1]->intro) {
		++TextIndex;
		UE_LOG(LogTemp, Warning, TEXT("CharacterName: %s"), *Dialogues[TextIndex]->CharacterName);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle1, this, &UDialogueWidgetBase::SetPortraitVisible, delay, false);
		DialogueText->SetText(FText::FromString(Dialogues[TextIndex]->DialogueText));
	}
	else {
		DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle2, this, &UDialogueWidgetBase::SetTextAndBubbleVisible, delay, false);
}

void UDialogueWidgetBase::SetPortraitVisible()
{
	UE_LOG(LogTemp, Warning, TEXT("SettingPortraitVisible!"));
	CurrentPortrait = Cast<UImage>(GetWidgetFromName(FName(Dialogues[TextIndex]->CharacterName)));
	//��ȡ��ǰ��˵����������
	if (CurrentPortrait)
		CurrentPortrait->SetVisibility(ESlateVisibility::Visible);
}

void UDialogueWidgetBase::SetPortraitHidden()
{
	CurrentPortrait = Cast<UImage>(GetWidgetFromName(FName(Dialogues[TextIndex]->CharacterName)));
	//��ȡ��ǰ��˵����������
	if (CurrentPortrait)
		CurrentPortrait->SetVisibility(ESlateVisibility::Hidden);
}
