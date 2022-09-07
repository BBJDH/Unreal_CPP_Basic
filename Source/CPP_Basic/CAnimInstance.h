
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "05_IK/CFeetComponent.h"
#include "CAnimInstance.generated.h"

/**
 #include "05_IK/CFeetComponent.h"
 �����Ͱ� �ƴ϶�� ��� ������ ������

 */
UCLASS()
class CPP_BASIC_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	bool bfeet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	FFeetData FeetData;



//public:
//	void BlueprintBeginPlay_Implementation();
//���� ���̶� ���õ�
public:
	void NativeBeginPlay()override;
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;
	//�𸮾� ������ �����Լ��� �������̵� ��ð� �ǹ������̴�
private:
	class ACharacter* OwnerCharacter;
	
};
