// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BedroomAfterWidget.h"
#include"Components/Button.h"
#include"Components/TextBlock.h"
#include"Components/Image.h"
#include<Player/NaegiController.h>
#include "HUD/DTReader.h"
#include "Animation/WidgetAnimation.h"
#include"HUD/KototamaWidget.h"
#include "Kismet/GameplayStatics.h"
void UBedroomAfterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Dialogues.Empty();
	InitializePortraits();
	FName _rowname = FName(TEXT("1"));
	FString ContextString = TEXT("TEST");
	KototamaNames = KototamaTable->GetRowNames();
	TextIndex = 0; InBedroom = true; InBathroom = false;
	LookForMaizono = false;
	BathRoomDoor->SetRenderOpacity(0.0f);
	if (BathRoomDoor != nullptr)
	{
		BathRoomDoor->OnClicked.AddDynamic(this, &UBedroomAfterWidget::OnDoorClicked);
	}
	//MyDialogue = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("C:/Unreal Projects/dangantest2/Content/resources/datatable/DT_Dialogue.uasset")));
	//��̬��ȡdatatable

	if (MyDialogue)
	{
		MyDialogue->GetAllRows(ContextString, Dialogues);//Dialogues�ѻ�ȡDataTable��������Ϣ
		if (Dialogues.IsValidIndex(0)) {
			FDialogData* _data = MyDialogue->FindRow< FDialogData>(_rowname, ContextString, false);//false��������
			// �����ı�������
			DialogueText->SetText(FText::FromString(Dialogues[TextIndex]->DialogueText));
		}

	}
	if (MyObject)
	{
		MyObject->GetAllRows(ContextString, Objects);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No connected DT"));
	}
}

void UBedroomAfterWidget::OnBubbleClicked()
{
	if (EndMap) {
		TextIndex = 0;
		//GetWorld()->GetTimerManager().ClearAllTimers(this);
		TextBubble->SetVisibility(ESlateVisibility::Hidden);
		DialogueText->SetVisibility(ESlateVisibility::Hidden);
		ANaegiController* PlayerController = Cast<ANaegiController>(UGameplayStatics::GetPlayerController(this, 0));
		if (PlayerController)
		{
			PlayerController->SetInputMode(FInputModeGameOnly());
			PlayerController->bShowMouseCursor = false;
			//EnableInput(PlayerController);
		}
		UGameplayStatics::OpenLevel(this, FName("FirstPersonMap"));//�˴��л��ؿ�
	}
	else if (TextIndex < Dialogues.Num()) {
		if (Dialogues[TextIndex]->out) {//�������ã�TextIndex��ͣ��outΪtrue�ĵط�
			UE_LOG(LogTemp, Warning, TEXT("Sensed Out"));
			SetPortraitHidden();
			//ִ������/���ٺ���
			SetTextAndBubbleHidden();
			if (GetNum == 5) {//���ռ��귿����ȫ���Ե�
				EndDialogue->GetAllRows("TEST", Dialogues);
				DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
				SetTextAndBubbleVisible(); SetPortraitVisible();
				EndMap = true;
			}
			if (InMainDialogue) {
				if (TextIndex == 2) {
					PlayAnimation(BedroomAfterFade); InBedroom = false; InBathroom = true;
					TextMoveOn(4.0f);
					PlayAnimation(Flash, -4.0f);
				}
				if (TextIndex == 5) {
					PlayAnimation(BathroomFade); InBedroom = true; InBathroom = false;
					InvestigatePhase = true;
					InMainDialogue = false;
				}
			}
			else if (InvestigatePhase) {
				if (EnterBathroomAgain) {//����׶ν���ԡ��
					PlayAnimation(BedroomAfterFade); InBedroom = false; InBathroom = true;
					TextMoveOn(4.0f);
					EnterBathroomAgain = false;
				}
			}
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

void UBedroomAfterWidget::OnDoorClicked()
{
	if (InBedroom && !InvestigatePhase) {
		UE_LOG(LogTemp, Warning, TEXT("DoorClicked"));
		if (TextBubble->GetVisibility() == ESlateVisibility::Hidden && TextIndex == 1) {//������԰��
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
	else if (InvestigatePhase && TextBubble->GetVisibility() == ESlateVisibility::Hidden) {
		InvesBathroom->GetAllRows("TEST", Dialogues);
		SetTextAndBubbleVisible();
		DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
		EnterBathroomAgain = true;

	}
}

void UBedroomAfterWidget::OnKatanaClicked()
{
	// = -1;
	if (InvestigatePhase && InBedroom && TextBubble->GetVisibility() == ESlateVisibility::Hidden) {
		FString ContextString = TEXT("TEST");
		//Dialogues.Empty();
		KatanaDialogue->GetAllRows(ContextString, Dialogues);
		SetTextAndBubbleVisible();
		DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
		if (Dialogues[TextIndex]->intro)
			SetPortraitVisible();
		ANaegiController* NaegiController = Cast<ANaegiController>(GetOwningPlayer());
		if (KototamaTable) {
			FKototama* Kototama = KototamaTable->FindRow<FKototama>(FName("Katana"), ContextString, false);
			FObjects* Object = MyObject->FindRow<FObjects>(FName("Katana"), ContextString, false);
			if (Kototama->Get == false) {
				NaegiController->GetKototama(Kototama);
				Kototama->Get = true;
				Object->bIsAcquired = true;
				GetNum++;
			}
		}

	}
}

void UBedroomAfterWidget::OnScratchClicked()
{
	if (InvestigatePhase && InBedroom && TextBubble->GetVisibility() == ESlateVisibility::Hidden) {
		FString ContextString = TEXT("TEST");
		//Dialogues.Empty();
		ScratchDialogue->GetAllRows(ContextString, Dialogues);
		SetTextAndBubbleVisible();
		DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
		ANaegiController* NaegiController = Cast<ANaegiController>(GetOwningPlayer());
		if (KototamaTable) {
			FKototama* Kototama = KototamaTable->FindRow<FKototama>(FName("Scratch"), ContextString, false);
			FObjects* Object = MyObject->FindRow<FObjects>(FName("Scratch"), ContextString, false);
			if (Kototama->Get == false) {
				NaegiController->GetKototama(Kototama);
				Kototama->Get = true;
				Object->bIsAcquired = true;
				GetNum++;
			}
		}
	}
}

void UBedroomAfterWidget::OnDrawerClicked()
{
	if (InvestigatePhase && InBedroom && TextBubble->GetVisibility() == ESlateVisibility::Hidden) {
		FString ContextString = TEXT("TEST");
		//Dialogues.Empty();
		DrawerDialogue->GetAllRows(ContextString, Dialogues);
		SetTextAndBubbleVisible();
		DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
		ANaegiController* NaegiController = Cast<ANaegiController>(GetOwningPlayer());
		if (KototamaTable) {
			FKototama* Kototama = KototamaTable->FindRow<FKototama>(FName("DrawerContent"), ContextString, false);
			FObjects* Object = MyObject->FindRow<FObjects>(FName("DrawerConter"), ContextString, false);
			if (Kototama->Get == false) {
				NaegiController->GetKototama(Kototama);
				Kototama->Get = true;
				Object->bIsAcquired = true;
				GetNum++;
			}
		}
	}
}

void UBedroomAfterWidget::OnMaizonoHandClicked()
{
	if (InvestigatePhase && InBathroom && TextBubble->GetVisibility() == ESlateVisibility::Hidden) {
		FString ContextString = TEXT("TEST");
		//Dialogues.Empty();
		MaizonoHandDialogue->GetAllRows(ContextString, Dialogues);
		SetTextAndBubbleVisible();
		DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
		if (Dialogues[TextIndex]->intro)
			SetPortraitVisible();
		ANaegiController* NaegiController = Cast<ANaegiController>(GetOwningPlayer());
		if (KototamaTable) {
			FKototama* Kototama = KototamaTable->FindRow<FKototama>(FName("MaizonoHand"), ContextString, false);
			FObjects* Object = MyObject->FindRow<FObjects>(FName("MaizonoHand"), ContextString, false);
			if (Kototama != nullptr) {
				if (Kototama->Get == false) {
					NaegiController->GetKototama(Kototama);
					Kototama->Get = true;
					Object->bIsAcquired = true;
					GetNum++;
				}
			}
		}
	}
}

void UBedroomAfterWidget::On11037Clicked()
{
	if (InvestigatePhase && InBathroom && TextBubble->GetVisibility() == ESlateVisibility::Hidden) {
		FString ContextString = TEXT("TEST");
		//Dialogues.Empty();
		_11037Dialogue->GetAllRows(ContextString, Dialogues);
		SetTextAndBubbleVisible();
		DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
		ANaegiController* NaegiController = Cast<ANaegiController>(GetOwningPlayer());
		if (KototamaTable) {
			FKototama* Kototama = KototamaTable->FindRow<FKototama>(FName("11037"), ContextString, false);
			FObjects* Object = MyObject->FindRow<FObjects>(FName("Number"), ContextString, false);
			if (Kototama != nullptr) {
				if (Kototama->Get == false) {
					NaegiController->GetKototama(Kototama);
					Kototama->Get = true;
					Object->bIsAcquired = true;
					GetNum++;
				}
			}
		}
	}
}

void UBedroomAfterWidget::SetTextAndBubbleHidden()
{
	TextBubble->SetVisibility(ESlateVisibility::Hidden);//��ť���ɼ��Ҳ��ɽ���
	DialogueText->SetVisibility(ESlateVisibility::Hidden);
}

void UBedroomAfterWidget::SetTextAndBubbleVisible()
{
	TextBubble->SetVisibility(ESlateVisibility::Visible);
	DialogueText->SetVisibility(ESlateVisibility::Visible);
}
//��ʼ������Ͱ�ť
void UBedroomAfterWidget::InitializePortraits()
{
	if (TextBubble != nullptr)
	{
		TextBubble->OnClicked.AddDynamic(this, &UBedroomAfterWidget::OnBubbleClicked);
	}
	Monokuma_BigLaugh->SetVisibility(ESlateVisibility::Hidden);
	Kirigiri_Firm->SetVisibility(ESlateVisibility::Hidden);
	Kirigiri_ThinkTalk->SetVisibility(ESlateVisibility::Hidden);
	Kirigiri_Think->SetVisibility(ESlateVisibility::Hidden);
	Kirigiri_Idle->SetVisibility(ESlateVisibility::Hidden);
	GoldenKatana->SetRenderOpacity(0.0f);
	GoldenKatana->OnClicked.AddDynamic(this, &UBedroomAfterWidget::OnKatanaClicked);
	Drawer->SetRenderOpacity(0.0f);
	Drawer->OnClicked.AddDynamic(this, &UBedroomAfterWidget::OnDrawerClicked);
	MaizonoHand->SetRenderOpacity(0.0f);
	MaizonoHand->OnClicked.AddDynamic(this, &UBedroomAfterWidget::OnMaizonoHandClicked);
	B11037->SetRenderOpacity(0.0f);
	B11037->OnClicked.AddDynamic(this, &UBedroomAfterWidget::On11037Clicked);
	ScratchOnFloor->SetRenderOpacity(0.0f);
	ScratchOnFloor->OnClicked.AddDynamic(this, &UBedroomAfterWidget::OnScratchClicked);
	ANaegiController* NaegiController = Cast<ANaegiController>(GetOwningPlayer());
	if (KototamaTable) {
		TArray<FName>_rowNames = KototamaTable->GetRowNames();
		for (auto _data : _rowNames) {
			FKototama* _kototama = KototamaTable->FindRow<FKototama>(_data, "TEST", false);
			_kototama->Get = false;
		}
		TArray<FName>_rowNames2 = MyObject->GetRowNames();
		for (auto _data : _rowNames2) {
			FObjects* _object = MyObject->FindRow<FObjects>(_data, "TEST", false);
			_object->bIsAcquired= false;
		}
	}
}

void UBedroomAfterWidget::TextMoveOn(float delay)
{
	if (Dialogues[TextIndex + 1]->intro) {
		++TextIndex;
		UE_LOG(LogTemp, Warning, TEXT("CharacterName: %s"), *Dialogues[TextIndex]->CharacterName);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle1, this, &UBedroomAfterWidget::SetPortraitVisible, delay, false);
		DialogueText->SetText(FText::FromString(Dialogues[TextIndex]->DialogueText));
	}
	else {
		DialogueText->SetText(FText::FromString(Dialogues[++TextIndex]->DialogueText));
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle2, this, &UBedroomAfterWidget::SetTextAndBubbleVisible, delay, false);
}

void UBedroomAfterWidget::SetPortraitVisible()
{
	UE_LOG(LogTemp, Warning, TEXT("SettingPortraitVisible"));
	CurrentPortrait = Cast<UImage>(GetWidgetFromName(FName(Dialogues[TextIndex]->CharacterName)));
	//��ȡ��ǰ��˵����������
	if (CurrentPortrait)
		CurrentPortrait->SetVisibility(ESlateVisibility::Visible);
}

void UBedroomAfterWidget::SetPortraitHidden()
{
	CurrentPortrait = Cast<UImage>(GetWidgetFromName(FName(Dialogues[TextIndex]->CharacterName)));
	//��ȡ��ǰ��˵����������
	if (CurrentPortrait)
		CurrentPortrait->SetVisibility(ESlateVisibility::Hidden);
}




