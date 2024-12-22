#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Engine/TriggerBox.h"
#include "MyTriggerBox.generated.h"




UCLASS()
class DANGANRONPA_API AMyTriggerBox : public ATriggerBox
{

    GENERATED_BODY()

public:
    // ���캯��
    AMyTriggerBox();

protected:
    // ������
    UPROPERTY(VisibleAnywhere, Category = "Trigger")
    UBoxComponent* TriggerBox;

    // �ص��¼�����
    UFUNCTION(BlueprintCallable)
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

public:
    // ������ʱִ�е��¼�
    UFUNCTION(BlueprintCallable)
    void OnTriggerHit();

    UFUNCTION(BlueprintCallable)
    void TriggerDeath();

    UFUNCTION(BlueprintCallable)
    void OpenNextLevel();
};

