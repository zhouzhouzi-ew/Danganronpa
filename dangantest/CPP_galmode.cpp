#include "CPP_galmode.h"
#include "Blueprint/UserWidget.h"

void ACPP_galmode::BeginPlay()
{
	Super::BeginPlay();

	// 检查是否已设置用户界面类
	if (UserWidgetClass)
	{
		// 创建用户界面实例
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), UserWidgetClass);
		if (CurrentWidget)
		{
			// 显示用户界面
			CurrentWidget->AddToViewport();
		}
	}

	// 显示鼠标光标
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->SetInputMode(FInputModeUIOnly());
	}
}
