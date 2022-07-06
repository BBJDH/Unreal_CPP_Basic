

#include "03_Collision/C02_ComponentOverlap.h"
#include "Global.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC02_ComponentOverlap::AC02_ComponentOverlap()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Root);


	Box->SetRelativeScale3D(FVector(3));  //XYZ 전부 3배
	Box->bHiddenInGame = false;

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 100, 0));


	/*************************************
	 에디터 회전 순서 : Roll Pitch Yaw
	 C++	: Pitch(Y) Yaw(Z) Roll(X) 로 다름

	**************************************/

	Text->SetRelativeScale3D(FVector(2)); //BP 자물쇠 잠그고 2설정
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	//가운데 정렬
	Text->Text = FText::FromString(GetName().Replace(TEXT("Default__"), TEXT("")));
	//디폴트로 Default__가 붙으니 없애는 처리
}

void AC02_ComponentOverlap::BeginPlay()
{
	Super::BeginPlay();
	
}


