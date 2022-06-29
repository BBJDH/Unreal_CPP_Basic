#pragma once

#include "CoreMinimal.h"
//언리얼에 필요한 기본적인 요소들 헤더

// 내 프로젝트의 모듈이름이 무엇인지 궁금하다면
//.uproject 파일의
/*

	"Modules": [
		{
			"Name": "CPP_Basic",
			"Type": "Runtime",
			"LoadingPhase": "Default",
			"AdditionalDependencies": [
				"Engine"
			]
*///를 확인

//이 클래스가 어느 모듈에 포함되어 있는지 : CPP_BASIC_API
class CPP_BASIC_API CHelpers
{

public:
	//
	template<typename T>
	static void CreateComponent(AActor* InActor, T** OutComponent,
		FName InName, USceneComponent* InParent = nullptr, FName InSocketName = NAME_None)
	{//어느 Actor에 소속될지/어디에서 생성될지(InActor), 할당받을 컴포넌트 포인터, 생성이름, 달라붙을 부모(유무 포함)		
		//Scene 컴포넌트 부터 트랜스폼이 생긴다 여기서부터 부모자식 행렬관계(좌표)가 형성되므로 최상위인 USceneComponent를 사용

		*OutComponent = InActor->CreateDefaultSubobject<T>(InName);

			if (!!InParent)		//nullptr 체크
			{
				//부모 SceneComponent가 존재한다면
				(*OutComponent)->SetupAttachment(InParent, InSocketName);
				//붙인다 행렬곱 실시

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
		Cast<Typename>(); 해당 타입으로 캐스팅
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