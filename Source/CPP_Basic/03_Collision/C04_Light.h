
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C04_Light.generated.h"

UCLASS()
class CPP_BASIC_API AC04_Light : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
	class USceneComponent * Root;

	UPROPERTY(VisibleDefaultsOnly)
	class UPointLightComponent* PointLight;

	UPROPERTY(VisibleDefaultsOnly)
	class UPointLightComponent* PointLight2;

	UPROPERTY(VisibleDefaultsOnly)
	class UTextRenderComponent* Text;
	
public:	
	AC04_Light();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnLight();
	UFUNCTION()
		void OffLight();

	UFUNCTION()
	FString OnRandomColor(FLinearColor InColor);
};
//공개 안하면 터진다