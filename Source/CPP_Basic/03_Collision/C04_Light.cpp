

#include "03_Collision/C04_Light.h"
#include "Global.h"
#include "C04_Trigger.h"
#include "Components/PointLightComponent.h"
#include "Components/TextRenderComponent.h"
AC04_Light::AC04_Light()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UPointLightComponent>(this, &PointLight, "PointLight", Root);
	CHelpers::CreateComponent<UPointLightComponent>(this, &PointLight2, "PointLight2", Root);

	CreateTextRender();

	PointLight->SetRelativeLocation(FVector(0, -50, 0));
	PointLight->LightColor = FColor::Red;
	PointLight->Intensity = 1e+4f; //입실론 오차 1e-6f 10의 지수 표현
	PointLight->AttenuationRadius = 200;	//반경

	PointLight2->SetRelativeLocation(FVector(0, 50, 0));
	PointLight2->LightColor = FColor::Red;
	PointLight2->Intensity = 1e+4f; //입실론 오차 1e-6f 10의 지수 표현
	PointLight2->AttenuationRadius = 200;	//반경
	
}

void AC04_Light::BeginPlay()
{
	Super::BeginPlay();

	PointLight->SetVisibility(false);
	PointLight2->SetVisibility(false);

	//for (AActor* actor : GetWorld()->GetCurrentLevel()->Actors)//월드의 현재 레벨의 모든 액터 순회
	//{
	//	if (!!actor && actor->IsA<AC04_Trigger>()) //IsA 상속이다 : TRUE
	//	{
	//		CLog::Log(actor->GetName());
	//	}
	//}
	//Actor 찾을때 자주 사용된다 GetAllActorsofClass도 마찬가지

	AC04_Trigger* trigger = CHelpers::FindActor<AC04_Trigger>(GetWorld());
	//가끔 펜딩킬 상태의 액터가 들어오므로 널체크가 필수
	if (!!trigger)
	{
		trigger->OnFBoxLightBeginOverlap.BindUFunction(this, "OnLight");
		trigger->OnFBoxLightEndOverlap.BindUFunction(this, "OffLight");

		trigger->OnBoxLightColorOverlap.BindUFunction(this, "OnRandomColor");
	}
}

void AC04_Light::OnLight()
{
	PointLight->SetVisibility(true);
}

void AC04_Light::OffLight()
{
	PointLight->SetVisibility(false);
	PointLight2->SetVisibility(false);

}

FString AC04_Light::OnRandomColor(FLinearColor InColor)
{

	PointLight2->SetVisibility(true);
	PointLight2->SetLightColor(InColor);

	return InColor.ToString();
}