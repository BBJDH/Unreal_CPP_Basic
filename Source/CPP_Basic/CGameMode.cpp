// Copyright Epic Games, Inc. All Rights Reserved.


#include "CGameMode.h"
#include "Global.h"

ACGameMode::ACGameMode()
{

	//Blueprint'/Game/BP_CPlayer.BP_CPlayer'
	//��� ����Ʈ Ŭ���� Ÿ��
	//TSubclassof<APawn> DefaultPawnClass;
	//�������Ʈ Ŭ���� Ÿ���� �������� �о�� ���� �ݵ�� �ĺ��� �ڿ� _C�� �پ�� Ŭ������ �ν��Ѵ�
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'");
}