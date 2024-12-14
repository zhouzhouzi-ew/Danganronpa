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
	// 对话内容
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog")
	FString DialogueText;

	// 可选：对话角色（如果有）
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
	// 对话内容
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog")
	FString Name;

	// 可选：对话角色（如果有）
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog")
	FString Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog")
	TObjectPtr<UImage>Image;

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
	UDataTable* MyDialogue;//*******重要：用于在BP内添加一个DataTable

	
	TArray<FDialogData*>DialogueData;
};