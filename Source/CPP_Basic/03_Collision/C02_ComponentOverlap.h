
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_ComponentOverlap.generated.h"

UCLASS()
class CPP_BASIC_API AC02_ComponentOverlap : public AActor
{
	GENERATED_BODY()

	private:
	UPROPERTY(VisibleDefaultsOnly)
	class USceneComponent * Root;

	UPROPERTY(VisibleDefaultsOnly)
	class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
	class UTextRenderComponent* Text;
	
public:	
	AC02_ComponentOverlap();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
