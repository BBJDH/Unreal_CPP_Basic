
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C04_Trigger.generated.h"

DECLARE_DELEGATE(FBoxLightOverlap) // void ____(void)
DECLARE_DELEGATE_RetVal_OneParam(FString, FBoxLightColorOverlap, FLinearColor);
//리턴밸류가 있고 파라미터 하나, (리턴할 타입, 델리게이션 이름(사용자 정의), 파라미터 타입)

UCLASS()
class CPP_BASIC_API AC04_Trigger : public AActor
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
	AC04_Trigger();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	//델리게이트로 선언된 변수는 변수이지만 외부에서 바인딩하기 쉽게 퍼블릭
	FBoxLightOverlap OnFBoxLightBeginOverlap;
	FBoxLightOverlap OnFBoxLightEndOverlap;

	FBoxLightColorOverlap OnBoxLightColorOverlap;
};
