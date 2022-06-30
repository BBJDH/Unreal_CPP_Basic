// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/CLog.h"


DEFINE_LOG_CATEGORY_STATIC(GameProject, Display, All)

void CLog::Log(int32 InValue)
{
	//GLog->Log("Gameproject",ELogVerbosity::Display, FString::FromInt(InValue));
	UE_LOG(GameProject,Display,TEXT("%d"),InValue)
	//ī�װ��� ���� ���� "LogTemp"
#pragma region ELogVerbosity
					/*************************************
	ELogVerbosity

	Fatal
	���� �α״� �׻� �ܼ� �� �α� ���Ͽ� ��µǸ� �αװ� ��Ȱ��ȭ�� ��쿡�� �۵��� �ߴܵȴ�.

	Error
	���� �α״� �ܼ� �� �α� ���Ͽ� ��µǸ�, �� �α״� �⺻������ ���������� ǥ�õȴ�.

	Warning
	���� �α״� �ܼ� �� �α� ���Ͽ� ��µǸ�, �� �α״� �⺻������ ��������� ǥ�õȴ�.

	Display
	���� �α״� �ֹܼ� �α� ���Ͽ� ��µȴ�.

	Log
	���� �α״� �α� ���Ͽ��� ��µ�����, ���� ���� �ֿܼ����� ��µ��� ������, �������� ��� �α� ���� ���ؼ��� ��� ��µȴ�.

	Verbose
	������ �α״� �α� ���Ͽ��� ��µ�����, ���� ���� �ֿܼ��� ��µ��� �ʴ´�. �Ϲ������� �ڼ��� �α� �� ����뿡 ���ȴ�.

	VeryVerbose
	������ �α״� �α� ���Ͽ��� ��µ�����, ���� ���� �ֿܼ��� ��µ��� �ʴ´�. �� ������ �α״� �Ϲ������� �뷮�� �α׸� ����ϴ� ���� �α뿡 ���ȴ�

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
	//C:\\Test\\test.cpp ���� �޺κ� test.cpp�� ����������

	int32 index = 0, length = 0;
	InFileName.FindLastChar(TEXT('\\'), index);
	//�ڿ������� ���� ���ڸ� ã�´�

	length = InFileName.Len() - 1;
	//���� ���ϰ���� ���ڿ� ������ ����(�ι��ڱ��� ����ϱ� ������ �θ�ŭ ��)

	FString filename = InFileName.Right(length - index);
	//�� �ڿ������� index ��ŭ ����

	FString str;
	str.Append(filename);
	str.Append(", ");
	str.Append(InFuncName);
	str.Append(", ");
	str.Append(FString::FromInt(InLineNumber));


	GLog->Log("GameProject", ELogVerbosity::Display, *str);

}