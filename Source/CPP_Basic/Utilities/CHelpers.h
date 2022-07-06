#pragma once

#include "CoreMinimal.h"

#define CheckTrue(p) {if(p==true) return;} // True�� �Լ� ����
#define CheckTrueResult(p,result) {if(p==true) return result;}// True�� �Լ� ����, ������

#define CheckFalse(p) {if(p==false) return;}// false�� �Լ� ����
#define CheckFalseResult(p,result) {if(p==false) return result;} // false�� �Լ� ����, ������
//True�� ���� ������ �ִٸ� �� ��ȯ

#define CheckNull(p) {if(p==nullptr) return;}	//nullptr�̶�� �ش� �Լ� ����
#define CheckNullResult(p,result) {if(p==nullptr) return result;}// nullptr�̶�� ���ڰ�p�� ����

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

	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);
		*OutClass = asset.Class;
	}
};