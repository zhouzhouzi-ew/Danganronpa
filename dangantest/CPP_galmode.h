#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CPP_galmode.generated.h"

UCLASS()
class DANGANRONPA_API ACPP_galmode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> UserWidgetClass; // 用于指定 Widget 类

	UPROPERTY()
	class UUserWidget* CurrentWidget; // 当前加载的 Widget
};
