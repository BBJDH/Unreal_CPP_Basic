// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"



void UCAnimInstance::NativeBeginPlay() 
{
	//__super, 부모객체의 함수 콜
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());

	CLog::Print("Begin Play");

}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//CLog::Print("Update",1);
	//ABP를 열기만 해도 Update가 출력된다
	//프리뷰 액터에서 콜, 할당된 애니메이션에서 콜

	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();

}