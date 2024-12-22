// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"Engine/DataTable.h"
#include"Components/Image.h"
#include "DTReader.generated.h"
USTRUCT(BlueprintType)
struct FDialogData : public FTableRowBase
{
	GENERATED_BODY()
public:
	// �Ի�����
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog")
	FString DialogueText;

	// ��ѡ���Ի���ɫ������У�
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog")
	FString CharacterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog")
	bool intro;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog")
	bool out;
};
USTRUCT(BlueprintType)
struct FKototama : public FTableRowBase
{
	GENERATED_BODY()
public:
	// 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KototamaData")
	FText Name;

	// 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KototamaData")
	FText Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KototamaData")
	TObjectPtr<UTexture2D>Image;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KototamaData")
	bool Get;

};
USTRUCT(BlueprintType)
struct FObjects : public FTableRowBase
{
	GENERATED_BODY()
public:
	// ��Ʒ������
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Objects")
	FString ObjectName;

	// ��Ʒ����ϸ����
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Objects")
	FString ObjectDetail;

	// �Ƿ��ѻ�ȡ
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Objects")
	bool bIsAcquired;

	// ��Ʒ��ͼƬ���ã�ʹ������
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Objects")
	FSoftObjectPath ObjectImage;
};
UCLASS()
class DANGANTEST2_API ADTReader : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ADTReader();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* MyDialogue;//*******��Ҫ��������BP�����һ��DataTable

	
	TArray<FDialogData*>DialogueData;
};