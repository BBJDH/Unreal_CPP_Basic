
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_DrawDebug.generated.h"

UCLASS()
class CPP_BASIC_API AC02_DrawDebug : public AActor
{
	GENERATED_BODY()
	
	
private:
	UPROPERTY(EditAnywhere, Category = "Draw")
	FVector InitLocation[5];

	UPROPERTY(EditAnywhere, Category = "Draw")
	FBox Box;
	//BOX ����ü

	//UPROPERTY(EditAnywhere, Category = "Draw")
	//FTransform Transform;
	//Ʈ������ BP�� ����

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UPointLightComponent * PointLight;
	
public:	
	AC02_DrawDebug();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


private:
	FVector Location[5];
	//���������� ����� Location

};
