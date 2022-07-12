// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C05_Box.generated.h"

UCLASS()
class CPP_BASIC_API AC05_Box : public AActor
{
	GENERATED_BODY()

	private:
	UPROPERTY(VisibleDefaultsOnly)
	class USceneComponent * Root;

	UPROPERTY(VisibleDefaultsOnly)
	class UStaticMeshComponent* Meshes[3];

	UPROPERTY(VisibleDefaultsOnly)
	class UTextRenderComponent* Text;
	
public:	
	AC05_Box();

private:
	UFUNCTION()
	void OnPhysic(int32 InIdex, FLinearColor InColor);

protected:
	virtual void BeginPlay() override;

private:
	class UMaterialInstanceDynamic* Materials[3];
	FVector WorldLocation[3];

};
