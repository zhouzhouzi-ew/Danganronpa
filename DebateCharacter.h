#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DebateCharacter.generated.h"


UCLASS()
class DANGANRONPA_API ADebateCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // ���캯��
    ADebateCharacter();

protected:
    // ��Ϸ��ʼʱ���������ʱ����
    virtual void BeginPlay() override;

public:
    // ÿ֡����ʱ����
    virtual void Tick(float DeltaTime) override;
};
