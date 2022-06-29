
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C01_Property.generated.h"
//	GENERATED_BODY() �� ���� 

UCLASS()
class CPP_BASIC_API AC01_Property : public AActor
{
	GENERATED_BODY()	//����ȭ�� �ʿ��� �ڵ��


private:
	UPROPERTY(EditAnywhere)			//�������� ���µ� �������ķε� �ٲ� ���� ���� ��
	int32 A = 10;
	UPROPERTY(EditAnywhere)			//�������� ���µ� �������ķε� �ٲ� ���� ���� ��
	int32 F = 50;
	UPROPERTY(EditInstanceOnly)		//�������Ŀ� ���� ����
	int32 B;
	UPROPERTY(EditDefaultsOnly)		//�����Ǳ� ���� ����Ʈ, �������� ����
									//�ش� Ŭ���� �������� ����
	int32 C;
	UPROPERTY(VisibleAnywhere, Category = "Property")
	int D = 30;

		

protected:
	//ReadOnly: Get�� ����			EditInstanceOnly: ���� ���� ��������, ī�װ���
	//UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Property")
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Property")
		int Variable = 60;
	
public:	
	AC01_Property();
	void print();

protected:
	virtual void BeginPlay() override;

public:	

};
