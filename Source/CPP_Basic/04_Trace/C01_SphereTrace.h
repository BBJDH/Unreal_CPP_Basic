
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

	//�̳� Ŭ������ �ƴ� �̳��� Ÿ���� �ɼ� ����
	//������ �𸮾󿡼� TEnumAsByte�� Ÿ��ȭ�� ����, Ÿ��ȭ

	UPROPERTY(EditAnywhere)
	float DrawDuration = 5;
	//�׸� �ð�, ��

	UPROPERTY(EditAnywhere)
	float MaxMass = 200;

	UPROPERTY(EditAnywhere)
	float ImpulseAmount = 100000;
	//Impulse : ���� �޴�����(��ݷ�) force : ������ ��(���� �� ��)
	//���� : �ް� �ִ� ��, ���޽� : ������ ��

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
enum class ���� 

UENUM(BlueprintType)
BlueprintType ���̸� �������� Ÿ������ �ٷ� �� �ִ�, 
Uint8 ��÷� 1����Ʈ ������ ��õ� ���������λ��

������ �ٸ� ��� ����� ������ ������ ���ִ� ���ø��� ���� ����ȭ �ؾ��Ѵ� 
�װ��� TEnumAsByte,


**���� Ŭ���� ���漱���� �����͸� �����ϴ�
**************************************/