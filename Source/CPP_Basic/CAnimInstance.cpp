// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"



void UCAnimInstance::NativeBeginPlay() 
{
	//__super, �θ�ü�� �Լ� ��
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());

	CLog::Print("Begin Play");

}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//CLog::Print("Update",1);
	//ABP�� ���⸸ �ص� Update�� ��µȴ�
	//������ ���Ϳ��� ��, �Ҵ�� �ִϸ��̼ǿ��� ��

	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();

}