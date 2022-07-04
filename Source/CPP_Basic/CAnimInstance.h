// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CPP_BASIC_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Animation")

	float Speed;

public:
	virtual void NativeBeginPlay()override;
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;
	//�𸮾� ������ �����Լ��� �������̵� ��ð� �ǹ������̴�
private:
	class ACharacter* OwnerCharacter;
	
};
