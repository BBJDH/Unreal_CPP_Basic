
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C05_MultiTrigger.generated.h"


DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiLightOverlap, int32, FLinearColor);

UCLASS()
class CPP_BASIC_API AC05_MultiTrigger : public AActor
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
	AC05_MultiTrigger();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


public:
	FMultiLightOverlap OnMultiLightOverlap;
	//멀티 델리게이트는 Add한 순서대로 콜된다
};
