// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/CanteenWidget.h"
#include<GeneralController.h>
#include"HUD/DTReader.h"
#include "Kismet/GameplayStatics.h"
void UCanteenWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	_rowNames = MainDialogue->GetRowNames();
}

void UCanteenWidget::InitializePortraits()
{
	Super::InitializePortraits();
	Kirigiri_ThinkTalk->SetVisibility(ESlateVisibility::Hidden);
	Asahina_HeadLow->SetVisibility(ESlateVisibility::Hidden);
	Asahina_IdleFrown->SetVisibility(ESlateVisibility::Hidden);
	Asahina_Worry->SetVisibility(ESlateVisibility::Hidden);
	Ishimaru_Think->SetVisibility(ESlateVisibility::Hidden);
	Monokuma_BigLaugh->SetVisibility(ESlateVisibility::Hidden);
}

void UCanteenWidget::OnBubbleClicked()
{
	Super::OnBubbleClicked();
	if (EndMap) {
		TextIndex = -1;
		UGameplayStatics::OpenLevel(this, FName("Map_Classroom"));//�˴��л��ؿ�
	}
	else if (TextIndex < _rowNames.Num()) {//ȷ����Խ��
		if (_rowNames[TextIndex] == FName(TEXT("GetKnife"))) {
			UE_LOG(LogTemp, Warning, TEXT("KnifeGet"));
			if (KototamaTable) {
				AGeneralController* PlayerController = Cast<AGeneralController>(GetOwningPlayer());
				FKototama* Kototama = KototamaTable->FindRow<FKototama>(FName("Knife"), "TEST", false);
				FObjects* Object = MyObject->FindRow<FObjects>(FName("Knife"), "TEST", false);
				if (Kototama != nullptr) {
					if (Kototama->Get == false) {
						PlayerController->GetKototama(Kototama);
						Kototama->Get = true;
						Object->bIsAcquired = true;
					}
				}
				else
					UE_LOG(LogTemp, Warning, TEXT("KototamaNotFound"));
			}

		}
		if (_rowNames[TextIndex] == FName(TEXT("EndOfDialogue"))) {
			EndMap = true;
		}
	}
}
