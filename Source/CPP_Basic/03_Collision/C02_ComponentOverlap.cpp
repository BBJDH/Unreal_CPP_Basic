

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


	Box->SetRelativeScale3D(FVector(3));  //XYZ ���� 3��
	Box->bHiddenInGame = false;

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 100, 0));


	/*************************************
	 ������ ȸ�� ���� : Roll Pitch Yaw
	 C++	: Pitch(Y) Yaw(Z) Roll(X) �� �ٸ�

	**************************************/

	Text->SetRelativeScale3D(FVector(2)); //BP �ڹ��� ��װ� 2����
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	//��� ����
	Text->Text = FText::FromString(GetName().Replace(TEXT("Default__"), TEXT("")));
	//����Ʈ�� Default__�� ������ ���ִ� ó��
}

void AC02_ComponentOverlap::BeginPlay()
{
	Super::BeginPlay();
	
}


