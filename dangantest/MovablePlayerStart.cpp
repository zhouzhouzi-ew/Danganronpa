#include "MovablePlayerStart.h"
#include "Components/CapsuleComponent.h"

AMovablePlayerStart::AMovablePlayerStart()
{
	// 获取 PlayerStart 的默认碰撞胶囊（CapsuleComponent），并设置为可移动
	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->SetMobility(EComponentMobility::Movable);
	}
}

void AMovablePlayerStart::BeginPlay()
{
	Super::BeginPlay();

	// 可以在此处做更多的运行时设置
}
  