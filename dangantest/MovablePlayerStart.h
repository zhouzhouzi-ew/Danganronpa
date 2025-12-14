#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "Components/CapsuleComponent.h"
#include "MovablePlayerStart.generated.h"

UCLASS()
class TEST2_API AMovablePlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
	AMovablePlayerStart();

protected:
	virtual void BeginPlay() override;
};
