
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
Actor����
OnActorBeginOverlap�� ���ǵǾ� �ִ�

DECLARE_�������̼����� (F�������̼�_�ڷ��� ����)
F�������̼�_�ڷ��� On�������̼Ǻ���;
�� Actor �ȿ� ��� ������ ������ �ִ�

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams( FActorBeginOverlapSignature, AActor, OnActorBeginOverlap, AActor*, OverlappedActor, AActor*, OtherActor );
SPARSE�� ������� �ʴ� �ٸ� ����  OverlappedActor, AActor*, OtherActor �Ķ���� ��ø� �ʿ��ϴ�
**************************************/