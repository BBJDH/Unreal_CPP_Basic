// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/CLog.h"


DEFINE_LOG_CATEGORY_STATIC(GameProject, Display, All)

void CLog::Log(int32 InValue)
{
	//GLog->Log("Gameproject",ELogVerbosity::Display, FString::FromInt(InValue));
	UE_LOG(GameProject,Display,TEXT("%d"),InValue)
	//카테고리를 지정 가능 "LogTemp"
#pragma region ELogVerbosity
					/*************************************
	ELogVerbosity

	Fatal
	수준 로그는 항상 콘솔 및 로그 파일에 출력되며 로그가 비활성화된 경우에도 작동이 중단된다.

	Error
	수준 로그는 콘솔 및 로그 파일에 출력되며, 이 로그는 기본적으로 빨간색으로 표시된다.

	Warning
	수준 로그는 콘솔 및 로그 파일에 출력되며, 이 로그는 기본적으로 노란색으로 표시된다.

	Display
	수준 로그는 콘솔및 로그 파일에 출력된다.

	Log
	수준 로그는 로그 파일에는 출력되지만, 게임 내의 콘솔에서는 출력되지 않지만, 에디터의 출력 로그 탭을 통해서는 계속 출력된다.

	Verbose
	수준의 로그는 로그 파일에는 출력되지만, 게임 내의 콘솔에는 출력되지 않는다. 일반적으로 자세한 로깅 및 디버깅에 사용된다.

	VeryVerbose
	수준의 로그는 로그 파일에는 출력되지만, 게임 내의 콘솔에는 출력되지 않는다. 이 수준의 로그는 일반적으로 대량의 로그를 출력하는 상세한 로깅에 사용된다

	**************************************/
#pragma endregion

}
void CLog::Log(float InValue)
{
	//GLog->Log("Gameproject", ELogVerbosity::Display, FString::SanitizeFloat(InValue));
	UE_LOG(GameProject, Display, TEXT("%f"), InValue);
}
void CLog::Log(FString const & InValue)
{
	GLog->Log("GameProject", ELogVerbosity::Display, *InValue);
	//UE_LOG(GameProject, Display, TEXT("%s"), *InValue);

}
void CLog::Log(FVector const & InValue)
{
	GLog->Log("GameProject", ELogVerbosity::Display, *InValue.ToString());
	//UE_LOG(GameProject, Display, TEXT("%s"), InValue);

}
void CLog::Log(FRotator const & InValue)
{
	GLog->Log("GameProject", ELogVerbosity::Display, *InValue.ToString());

}
void CLog::Log(UObject const * InValue)
{
	FString str{};
	if (!!InValue)
		str.Append(InValue->GetName());

	str.Append(InValue ? " : Not Null" : " : Null");

	GLog->Log("GameProject", ELogVerbosity::Display, *str);

}
void CLog::Log(FString const & InFileName, FString const & InFuncName, int32 InLineNumber)
{
	//C:\\Test\\test.cpp 에서 뒷부분 test.cpp만 가져오려면

	int32 index = 0, length = 0;
	InFileName.FindLastChar(TEXT('\\'), index);
	//뒤에서부터 지정 문자를 찾는다

	length = InFileName.Len() - 1;
	//들어온 파일경로의 문자열 갯수를 저장(널문자까지 기록하기 때문에 널만큼 뺌)

	FString filename = InFileName.Right(length - index);
	//맨 뒤에서부터 index 만큼 추출

	FString str;
	str.Append(filename);
	str.Append(", ");
	str.Append(InFuncName);
	str.Append(", ");
	str.Append(FString::FromInt(InLineNumber));


	GLog->Log("GameProject", ELogVerbosity::Display, *str);

}