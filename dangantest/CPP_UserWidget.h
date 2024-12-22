// CPP_UserWidget.h
#pragma once

#include "CoreMinimal.h"
#include "NavigationSystemTypes.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include"GameFramework/PlayerController.h"
#include "CPP_UserWidget.generated.h"

/**
 * 自定义用户界面控件类
 */
UCLASS()
class DANGANRONPA_API UCPP_UserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* Gamestart;

	UPROPERTY(meta = (BindWidget))
	class UButton* load;

	UPROPERTY(meta = (BindWidget))
	class UButton* option;

	UPROPERTY(meta = (BindWidget))
	class UButton* quit;

	UFUNCTION()
	void OnButtonClicked();

	// 显示不同界面的函数
	void ShowLoadUI();
	void ShowOptionUI()
	{	APlayerController* PlayerController=GetWorld()->GetFirstPlayerController();
		if(PlayerController)
		{
			UUserWidget*Mywidget=CreateWidget<UUserWidget>(PlayerController,UCPP_UserWidget::StaticClass());
			
		}
		
	}
	void ShowQuitUI();
	void SwitchLevel()
	{
		// 通过关卡名来切换关卡
		UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("LV_School")));
	}
};
