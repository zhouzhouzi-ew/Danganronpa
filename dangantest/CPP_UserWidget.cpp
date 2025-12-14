// CPP_UserWidget.cpp
#include "CPP_UserWidget.h"
#include "Components/Button.h"

void UCPP_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 检查按钮是否有效并绑定点击事件
	if (Gamestart)
	{
		Gamestart->OnClicked.AddDynamic(this, &UCPP_UserWidget::OnButtonClicked);
	}
	if (load)
	{
		load->OnClicked.AddDynamic(this, &UCPP_UserWidget::OnButtonClicked);
	}
	if (option)
	{
		option->OnClicked.AddDynamic(this, &UCPP_UserWidget::OnButtonClicked);
	}
	if (quit)
	{
		quit->OnClicked.AddDynamic(this, &UCPP_UserWidget::OnButtonClicked);
	}
}

void UCPP_UserWidget::OnButtonClicked()
{
	// 根据不同的按钮进行相应的操作
	if (Gamestart)
	{
		SwitchLevel();
	}
	else if (load)
	{
		ShowLoadUI();
	}
	else if (option)
	{
		ShowOptionUI();
	}
	else if (quit)
	{
		ShowQuitUI();
	}
}

// 逻辑实现函数：分别显示不同的界面
void UCPP_UserWidget::ShowGameStartUI()
{
	// 例如，加载开始游戏的界面
	UE_LOG(LogTemp, Warning, TEXT("Game Start UI"));
	// 你可以在这里使用 CreateWidget 创建并显示新界面
}

void UCPP_UserWidget::ShowLoadUI()
{
	// 例如，加载加载游戏的界面
	UE_LOG(LogTemp, Warning, TEXT("Load Game UI"));
	// 可以通过 CreateWidget 加载并显示另一个 UI 界面
}

void UCPP_UserWidget::ShowOptionUI()
{
	// 例如，显示设置界面
	UE_LOG(LogTemp, Warning, TEXT("Option UI"));
	// 同样可以通过 CreateWidget 显示不同的 UI
}

void UCPP_UserWidget::ShowQuitUI()
{
	// 退出游戏界面逻辑
	UE_LOG(LogTemp, Warning, TEXT("Quit UI"));
	// 在这里你可以调用退出游戏的代码
}
