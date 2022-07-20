#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C03_MultiLineTrace.generated.h"

UCLASS()
class CPP_BASIC_API AC03_MultiLineTrace : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;


public:
	AC03_MultiLineTrace();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	float TotalTime = 0;
};
