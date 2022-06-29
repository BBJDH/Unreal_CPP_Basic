#pragma once

#include "CoreMinimal.h"
//�𸮾� �ʿ��� �⺻���� ��ҵ� ���

// �� ������Ʈ�� ����̸��� �������� �ñ��ϴٸ�
//.uproject ������
/*

	"Modules": [
		{
			"Name": "CPP_Basic",
			"Type": "Runtime",
			"LoadingPhase": "Default",
			"AdditionalDependencies": [
				"Engine"
			]
*///�� Ȯ��

//�� Ŭ������ ��� ��⿡ ���ԵǾ� �ִ��� : CPP_BASIC_API
class CPP_BASIC_API CHelpers
{

public:
	//
	template<typename T>
	static void CreateComponent(AActor* InActor, T** OutComponent,
		FName InName, USceneComponent* InParent = nullptr, FName InSocketName = NAME_None)
	{//��� Actor�� �Ҽӵ���/��𿡼� ��������(InActor), �Ҵ���� ������Ʈ ������, �����̸�, �޶���� �θ�(���� ����)		
		//Scene ������Ʈ ���� Ʈ�������� ����� ���⼭���� �θ��ڽ� ��İ���(��ǥ)�� �����ǹǷ� �ֻ����� USceneComponent�� ���

		*OutComponent = InActor->CreateDefaultSubobject<T>(InName);

			if (!!InParent)		//nullptr üũ
			{
				//�θ� SceneComponent�� �����Ѵٸ�
				(*OutComponent)->SetupAttachment(InParent, InSocketName);
				//���δ� ��İ� �ǽ�

				return;
			}
		InActor->SetRootComponent(*OutComponent);
		//InActor->RootComponent(*OutComponent); //Protected

	}
	template<typename T>
	static void GetAsset(T** OutObject, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);
		*OutObject = asset.Object;
	}

	template<typename T>
	static void GetAssetDynamic(T** OutObject, FString InPath)
	{
		/*************************************
		Cast<Typename>(); �ش� Ÿ������ ĳ����
		**************************************/
		*OutObject = Cast<T>
			(
				StaticLoadObject
				(
					T::StaticClass(),
					nullptr,
					*InPath
				)
			);
	}
};