// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/DialogueWidget.h"
#include"Components/Button.h"
#include"Components/TextBlock.h"
#include"Components/Image.h"
#include<Player/NaegiController.h>
#include "HUD/DTReader.h"
#include "Animation/WidgetAnimation.h"


void UDialogueWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	InitializePortraits();
	FName _rowname = FName(TEXT("1"));
	FString ContextString = TEXT("TEST");
	TextIndex = 0; InBedroom = true; InBathroom = false;
	LookForMaizono = false;
	BathRoomDoor->SetRenderOpacity(0.0f);
	if (BathRoomDoor != nullptr)
	{
		BathRoomDoor->OnClicked.AddDynamic(this, &UDialogueWidget::OnDoorClicked);
	}
	//MyDialogue = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("C:/Unreal Projects/dangantest2/Content/resources/datatable/DT_Dialogue.uasset")));
	//静态读取datatable
	
	if (MyDialogue)
	{
		MyDialogue->GetAllRows(ContextString, Dialogues);//Dialogues已获取DataTable所有行信息
		FDialogData* _data = MyDialogue->FindRow< FDialogData>(_rowname, ContextString, false);//false代表不报错
		// 更新文本框内容
		DialogueText->SetText(FText::FromString(Dialogues[TextIndex]->DialogueText));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No connected DT"));
	}
}

void UDialogueWidget::OnBubbleClicked()
{
	if (  TextIndex < Dialogues.Num()-1) {
		if (Dialogues[TextIndex]->out) {//这样设置，TextIndex会停在out为true的地方
			UE_LOG(LogTemp, Warning, TEXT("Sensed Out"));
			SetPortraitHidden();
			//执行隐藏/销毁函数
			SetTextAndBubbleHidden();
			if (InMainDialogue) {
				if (TextIndex == 2) {
					PlayAnimation(BedroomAfterFade); InBedroom = false; InBathroom = true;
					TextMoveOn(4.0f);
					PlayAnimation(Flash, -4.0f);
				}
				if (TextIndex == 5) {
					PlayAnimation(BathroomFade); InBedroom = true; InBathroom = false;
					InvestigatePhase = true;
				}
			}
		}
		else if(Dialogues[TextIndex+1]->intro){//有新立绘要显示
			SetPortraitHidden();//隐藏先前立绘
			TextIndex++;
			//UE_LOG(LogTemp, Warning, TEXT("CharacterName: %s"), *Dialogues[TextIndex]->CharacterName);
			SetPortraitVisible();
			DialogueText->SetText(FText::FromString(Dialogues[TextIndex]->DialogueText));
		}
		else {
			DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
		}
		
	}
	else if (InvestigatePhase) {

	}
	else{
		//对话推完了，进入下一关卡
	}
	
	ANaegiController* NaegiController=Cast<ANaegiController>(GetOwningPlayer());
	if (NaegiController != nullptr)
	{
		
	}
}

void UDialogueWidget::OnDoorClicked()
{
	if (InBedroom) {
		UE_LOG(LogTemp, Warning, TEXT("DoorClicked"));
		if (TextBubble->GetVisibility() == ESlateVisibility::Hidden && TextIndex == 1) {//该找舞园了
			LookForMaizono = true;
		}
		else {
			LookForMaizono = false;
		}
		if (LookForMaizono) {
			DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
			SetTextAndBubbleVisible();
		}
		else {
			return;
		}
	}
}

void UDialogueWidget::OnKatanaClicked()
{
	TextIndex = -1;
	if (InvestigatePhase) {
		FString ContextString = TEXT("TEST");
		Dialogues.Empty();
		KatanaDialogue->GetAllRows(ContextString, Dialogues);
		SetTextAndBubbleVisible();
		DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
		if (TextIndex == Dialogues.Num() - 1) {
			TextIndex = -1;//重置Index
		}
	}
}

void UDialogueWidget::OnScratchClicked()
{

}

void UDialogueWidget::OnDrawerClicked()
{

}

void UDialogueWidget::SetTextAndBubbleHidden()
{
	TextBubble->SetVisibility(ESlateVisibility::Hidden);//按钮不可见且不可交互
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
	Monokuma_BigLaugh->SetVisibility(ESlateVisibility::Hidden);
	Kirigiri_Firm->SetVisibility(ESlateVisibility::Hidden);
	GoldenKatana->SetRenderOpacity(0.0f);
	GoldenKatana->OnClicked.AddDynamic(this, &UDialogueWidget::OnKatanaClicked);
	Drawer->SetRenderOpacity(0.0f);
	Drawer->OnClicked.AddDynamic(this, &UDialogueWidget::OnDrawerClicked);
	ScratchOnFloor->SetRenderOpacity(0.0f);
	ScratchOnFloor->OnClicked.AddDynamic(this, &UDialogueWidget::OnScratchClicked);
}

void UDialogueWidget::TextMoveOn(float delay)
{
	if (Dialogues[TextIndex+1]->intro) {
		++TextIndex;
		UE_LOG(LogTemp, Warning, TEXT("CharacterName: %s"), *Dialogues[TextIndex]->CharacterName);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle1, this, &UDialogueWidget::SetPortraitVisible, delay, false);
		DialogueText->SetText(FText::FromString(Dialogues[TextIndex]->DialogueText));
	}
	else {
		DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle2, this, &UDialogueWidget::SetTextAndBubbleVisible, delay, false);
}

void UDialogueWidget::SetPortraitVisible()
{
	UE_LOG(LogTemp, Warning, TEXT("SettingPortraitVisible"));
	CurrentPortrait = Cast<UImage>(GetWidgetFromName(FName(Dialogues[TextIndex]->CharacterName)));
	//获取当前在说话的立绘名
	if (CurrentPortrait)
	    CurrentPortrait->SetVisibility(ESlateVisibility::Visible);
}

void UDialogueWidget::SetPortraitHidden()
{
	CurrentPortrait = Cast<UImage>(GetWidgetFromName(FName(Dialogues[TextIndex]->CharacterName)));
	//获取当前在说话的立绘名
	if(CurrentPortrait)
		CurrentPortrait->SetVisibility(ESlateVisibility::Hidden);
}


