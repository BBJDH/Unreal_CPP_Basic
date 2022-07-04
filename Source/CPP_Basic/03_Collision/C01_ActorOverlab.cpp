

#include "03_Collision/C01_ActorOverlab.h"
#include "Global.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC01_ActorOverlab::AC01_ActorOverlab()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box",Root);
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text",Root);


	Box->SetRelativeScale3D(FVector(3));  //XYZ ���� 3��
	Box->bHiddenInGame = false;

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 100, 0));


	/*************************************
	 ������ ȸ�� ���� : Roll Pitch Yaw 
	 C++	: Pitch(Y) Yaw(Z) Roll(X) �� �ٸ�

	**************************************/
	
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName().Replace(TEXT("Default__"), TEXT("")));


}

// Called when the game starts or when spawned
void AC01_ActorOverlab::BeginPlay()
{
	Super::BeginPlay();
	
}


/*************************************
 ��������Ʈ�� ������ ������ �������� ���� �ݹ� �Լ��� ȣ���ϱ� ���� ���.
 Ư¡
 - �Լ� �������� ���� ������ �ƴ� �븮�ڸ� ���� �Լ� ȣ�� ���

- ȣ���� �Լ��� �̸� �����ϴ� ��ü�� �������� �븮�ڰ� üũ�� �����ϰ� ó���� �� ����.

- ������ ���� ���� �Լ� ���� ���� �븮�ڰ� ��� �����ϰ�, �ʿ��� �� ���ÿ� ��� ȣ���ϴ� ���� ������.

**************************************/