
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C01_ActorOverlab.generated.h"

UCLASS()
class CPP_BASIC_API AC01_ActorOverlab : public AActor
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
	AC01_ActorOverlab();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);


};
/*************************************
Actor에는
OnActorBeginOverlap이 정의되어 있다

DECLARE_델리게이션종류 (F델리게이션_자료형 선언)
F델리게이션_자료형 On델리게이션변수;
즉 Actor 안에 멤버 변수로 가지고 있다

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams( FActorBeginOverlapSignature, AActor, OnActorBeginOverlap, AActor*, OverlappedActor, AActor*, OtherActor );
SPARSE를 사용하지 않는 다면 뒤의  OverlappedActor, AActor*, OtherActor 파라메터 명시만 필요하다
**************************************/