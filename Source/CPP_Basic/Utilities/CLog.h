// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


	/*************************************
	__FILE__ : ��ũ��, ���ϸ�
	__FUNCTION__ : ���� �Ҽӵ� �Լ�,
	__LINE__ : ���� �ִ� ����

	**************************************/
#define LogLine() {CLog::Log(__FILE__, __FUNCTION__, __LINE__);}

class CPP_BASIC_API CLog
{
public:
	static void Log(int32 InValue);
	static void Log(float InValue);
	static void Log(FString const & InValue);
	static void Log(FVector const & InValue);
	static void Log(FRotator const & InValue);
	static void Log(UObject const * InValue);
	static void Log(FString const & InValue, FString const & InFuncName, int32 InLineNumber);
};
