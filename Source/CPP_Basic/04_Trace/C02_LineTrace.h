#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_LineTrace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLineTraceResult, class AActor*, InActor, FLinearColor, InColor);

UCLASS()
class CPP_BASIC_API AC02_LineTrace : public AActor
{
	GENERATED_BODY()

	private:
	UPROPERTY(EditAnywhere)
	FVector LaunchAmount = FVector(0, 0, 200);
	//�÷��̾� ��� ��

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
	void StartLaunch(class AActor* InActor, FLinearColor InColor);

public:
	UPROPERTY(BlueprintAssignable)
	FLineTraceResult OnLineTraceResult;
	//�� ������ ������ �������̼�, BlueprintAssignable : �������Ʈ �̺�Ʈ�� ����

private:
	TArray<class AC02_Cylinder *> Cylinders;
};
