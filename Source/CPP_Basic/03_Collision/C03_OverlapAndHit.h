
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C03_OverlapAndHit.generated.h"

UCLASS()
class CPP_BASIC_API AC03_OverlapAndHit : public AActor
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
	AC03_OverlapAndHit();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, FHitResult const & Hit);

};
/*************************************
Hit 이벤트를 위한 사전 설정
해당 콜리전 컴포넌트를 쿼리엔 피직스로
쿼리온리라면 오버랩, 피직스 온리라면 hit만 된다

블록이 필요하다면 콜리전 프리셋에 해당 프리셋에 대하여 블록 체크
**************************************/