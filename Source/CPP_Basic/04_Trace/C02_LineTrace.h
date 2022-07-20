#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_LineTrace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLineTraceResult, class AActor*, InActor, FLinearColor, InColor);
//class AActor* 전방선언도 같이 사용, 자료형과 파라미터 이름까지 일치시키기위해 명시함을 기억하자
UCLASS()
class CPP_BASIC_API AC02_LineTrace : public AActor
{
	GENERATED_BODY()

	private:
	UPROPERTY(EditAnywhere)
	FVector LaunchAmount = FVector(0, 0, 200);
	//플레이어 띄울 힘

private:
	UPROPERTY(VisibleDefaultsOnly)
	class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
	class UTextRenderComponent* Text;

public:
	AC02_LineTrace();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


private:
	UFUNCTION()
	void StartLaunch(AActor* InActor, FLinearColor InColor);
//class AActor* 전방선언도 같이 사용, 자료형과 파라미터 이름까지 일치시키기위해 명시함을 기억하자
public:
	UPROPERTY(BlueprintAssignable)	//다이나믹 델리게이션만 가능, 블프와 통신이 가능하도록 만듬
	FLineTraceResult OnLineTraceResult;
	//맨 위에서 정의한 델리게이션, BlueprintAssignable : 블루프린트 이벤트로 간주

private:
	TArray<class AC02_Cylinder *> Cylinders;

};
