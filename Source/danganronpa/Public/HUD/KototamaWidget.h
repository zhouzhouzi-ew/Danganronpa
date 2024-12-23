#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KototamaWidget.generated.h"
class UButton;
class UTextBlock;
class UWidgetAnimation;
class UImage;
/**
 *
 */
UCLASS()
class DANGANRONPA_API UKototamaWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> KototamaName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> KototamaDescription;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> KototamaImage;

	// ����ͼ��ķ���
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetImage(UTexture2D* NewTexture);

	// �����ı��ķ���
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetName(const FText& NewText);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetDescription(const FText& NewText);
};
