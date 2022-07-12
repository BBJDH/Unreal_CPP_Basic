
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C04_Trigger.generated.h"

DECLARE_DELEGATE(FBoxLightOverlap) // void ____(void)
DECLARE_DELEGATE_RetVal_OneParam(FString, FBoxLightColorOverlap, FLinearColor);
//���Ϲ���� �ְ� �Ķ���� �ϳ�, (������ Ÿ��, �������̼� �̸�(����� ����), �Ķ���� Ÿ��)

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
	//��������Ʈ�� ����� ������ ���������� �ܺο��� ���ε��ϱ� ���� �ۺ�
	FBoxLightOverlap OnFBoxLightBeginOverlap;
	FBoxLightOverlap OnFBoxLightEndOverlap;

	FBoxLightColorOverlap OnBoxLightColorOverlap;
};
