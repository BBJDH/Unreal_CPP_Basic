#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C07_Override.generated.h"

UCLASS()
class CPP_BASIC_API AC07_Override : public AActor
{
	GENERATED_BODY()

	private:
	UPROPERTY(VisibleDefaultsOnly)
	class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
	class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
	class UTextRenderComponent* Text;

public:
	AC07_Override();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UFUNCTION(BlueprintNativeEvent)
	void ChangeColorWhite(); //����� ���Ǹ��� ���� �ִ�
	void ChangeColorWhite_Implementation();  //���� ���Ǵ� �̷��� �ٿ��� �� ������ �����
	//������ ����� ���ڸ����� ������ �ȵ�
	//BlueprintNativeEvent �ʿ信 ���� ������



	//�ڽĵ鿡�� ������ �Լ� ����
	//ImplementableEvent
	UFUNCTION(BlueprintImplementableEvent)
	void ChangeColorRed();
	//�ڽĿ��� ������ ������ �ڿ�_Implementation �ٿ��� ����
	//��ü�� ���� �Լ� �������̵��� �����ϰ� ��
	//�������� �̺�Ʈ�� ��Ÿ��


};
