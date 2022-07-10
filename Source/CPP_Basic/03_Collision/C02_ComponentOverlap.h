
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

/*************************************
Source - Runtime - Engine - Classes - Components
PrimitiveComponent - 해당 기능의 부모 액터로 이동
OverlappedComponent 검색을 통해
FComponentBeginOverlapSignature 를 찾고 다시 검색을 통해
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_SixParams
( FComponentBeginOverlapSignature, UPrimitiveComponent, OnComponentBeginOverlap, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult &, SweepResult);
를 확인
마찬가지로 뒤의 네번째 인자부터 일반적으로 사용
**************************************/

};
