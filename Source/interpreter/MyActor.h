// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class INTERPRETER_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	UFUNCTION(BlueprintCallable,Category = "ok")
	void Called(FString input,FString& Output);


	UFUNCTION(BlueprintCallable, Category = "ok")
	void Check(FString input, FString& Output);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int calculate(std::string s);
	bool isValidNumber(std::string str);
};
