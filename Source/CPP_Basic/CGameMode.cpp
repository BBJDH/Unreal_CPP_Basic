// Copyright Epic Games, Inc. All Rights Reserved.


#include "CGameMode.h"
#include "Global.h"

ACGameMode::ACGameMode()
{

	//Blueprint'/Game/BP_CPlayer.BP_CPlayer'
	//블루 프린트 클래스 타입
	//TSubclassof<APawn> DefaultPawnClass;
	//블루프린트 클래스 타입을 에셋으로 읽어올 때는 반드시 식별자 뒤에 _C가 붙어야 클래스로 인식한다
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'");
}