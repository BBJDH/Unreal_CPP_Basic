
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "C01_SphereTrace.generated.h"

UCLASS()
class CPP_BASIC_API AC01_SphereTrace : public AActor
{
	GENERATED_BODY()

	private:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EDrawDebugTrace::Type> DebugType;

	//이넘 클래스가 아닌 이넘은 타입이 될수 없다
	//때문에 언리얼에서 TEnumAsByte로 타입화를 제공, 타입화

	UPROPERTY(EditAnywhere)
	float DrawDuration = 5;
	//그릴 시간, 초

	UPROPERTY(EditAnywhere)
	float MaxMass = 200;

	UPROPERTY(EditAnywhere)
	float ImpulseAmount = 100000;
	//Impulse : 힘을 받는정도(충격량) force : 때리는 힘(직접 준 일)
	//포스 : 받고 있는 힘, 임펄스 : 변돌될 힘

private:
	UPROPERTY(VisibleDefaultsOnly)
	class UParticleSystemComponent* Particle;
	
public:	
	AC01_SphereTrace();

protected:
	virtual void BeginPlay() override;


public:
	UFUNCTION()
	void OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
/*************************************
enum class 문법 

UENUM(BlueprintType)
BlueprintType 붙이면 블프에서 타입으로 다룰 수 있다, 
Uint8 명시로 1바이트 사이즈 명시도 전반적으로사용

하지만 다른 사용 방식은 사이즈 지정을 해주는 템플릿을 통해 직렬화 해야한다 
그것이 TEnumAsByte,


**참고 클래스 전방선언은 포인터만 가능하다
**************************************/