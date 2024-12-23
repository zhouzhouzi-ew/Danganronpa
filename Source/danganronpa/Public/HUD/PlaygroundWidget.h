#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD/DTReader.h"
#include "PlaygroundWidget.generated.h"
class UButton;
class UTextBlock;
class UWidgetAnimation;
class UImage;
/**
 *
 */
UCLASS()
class DANGANRONPA_API UPlaygroundWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    /** ��ʼ����������д�麯���� */
    virtual void NativeOnInitialized() override;

protected:
    UPROPERTY(EditAnywhere)
    TObjectPtr<UDataTable> MyDialogue;

    int32 TextIndex;
    int32 InvesIndex = -1;

    TArray<FDialogData*>Dialogues;

    /** �ı���ť */
    UPROPERTY(meta = (BindWidget))
    class UButton* TextBubble;

    /** �Ի��ı� */
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* DialogueText;

    /** ���������� */
    UPROPERTY(meta = (BindWidget))
    class UCanvasPanel* PortraitsPlacement;

    /** ���������ͼ��ؼ� */
    UPROPERTY(meta = (BindWidget))
    class UImage* Naegi_normal;

    UPROPERTY(meta = (BindWidget))
    class UImage* Asahina_normal;

    UPROPERTY(meta = (BindWidget))
    class UImage* Mondo_Angry;

    UPROPERTY(meta = (BindWidget))
    class UImage* Sayaka_normal;

    UPROPERTY(meta = (BindWidget))
    class UImage* Yamada_normal;

    UPROPERTY(meta = (BindWidget))
    class UImage* Hagakure_normal;

    UPROPERTY(meta = (BindWidget))
    class UImage* Monokuma_normal;

    UPROPERTY(meta = (BindWidget))
    class UImage* Monokuma_laugh;

    UPROPERTY(meta = (BindWidget))
    class UImage* Monokuma_thread;

    UPROPERTY(meta = (BindWidget))
    class UImage* Kirigiri_normal;

    UPROPERTY(meta = (BindWidget))
    class UImage* Leon_normal;

    /** �����������ʾ������ */
    void SetTextAndBubbleHidden();
    void SetTextAndBubbleVisible();
    void SetPortraitVisible();
    void SetPortraitHidden();
    void InitializePortraits();
    UFUNCTION()
    void OnBubbleClicked();
    TObjectPtr<UDataTable> CurrentDialogue;
    TObjectPtr<UImage> CurrentPortrait;

    bool EndMap = false;
    TArray<FName>_rowNames;
};

