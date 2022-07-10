

#include "03_Collision/C01_ActorOverlab.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC01_ActorOverlab::AC01_ActorOverlab()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);

	CreateTextRender();

//��ũ�� ġȯ
//CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Root);
//Text->SetRelativeLocation(FVector(0, 0, 100));
//Text->SetRelativeRotation(FRotator(0, 100, 0));
///*************************************

// ������ ȸ�� ���� : Roll Pitch Yaw 
// C++	: Pitch(Y) Yaw(Z) Roll(X) �� �ٸ�

//**************************************/
//
//Text->SetRelativeScale3D(FVector(2)); //BP �ڹ��� ��װ� 2����
//Text->TextRenderColor = FColor::Red;
//Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
////��� ����
//Text->Text = FText::FromString(GetName().Replace( TEXT("Default__") , TEXT("") ));
////����Ʈ�� Default__�� ������ ���ִ� ó��, UI������ TEXT���� ���  


	Box->SetRelativeScale3D(FVector(3));  //XYZ ���� 3��
	Box->bHiddenInGame = false;


}

// Called when the game starts or when spawned
void AC01_ActorOverlab::BeginPlay()
{
	Super::BeginPlay();
	

	OnActorBeginOverlap.AddDynamic(this, &AC01_ActorOverlab::OnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AC01_ActorOverlab::OnEndOverlap);
	//�Լ������� ����, ������ ���������� ���۽� ���ε� ���ش�
	//AActor���� �ۺ����� ��������Ʈ���� ����Ǿ� �ִ�

}


/*************************************
 ��������Ʈ�� ������ ������ �������� ���� �ݹ� �Լ��� ȣ���ϱ� ���� ���.
 Ư¡
 - �Լ� �������� ���� ������ �ƴ� �븮�ڸ� ���� �Լ� ȣ�� ���

- ȣ���� �Լ��� �̸� �����ϴ� ��ü�� �������� �븮�ڰ� üũ�� �����ϰ� ó���� �� ����.

- ������ ���� ���� �Լ� ���� ���� �븮�ڰ� ��� �����ϰ�, �ʿ��� �� ���ÿ� ��� ȣ���ϴ� ���� ������.


��������Ʈ ��Ƽĳ��Ʈ
�� �̺�Ʈ�� ���� �Լ� �����͸� ����

��������Ʈ ���̳���
����, �������� ���

��������Ʈ ���̳��� ��Ƽĳ��Ʈ
������ �̺�Ʈ ������

���Ľ���������Ʈ (������) �߰� ���� ��ð� �ʿ��ϴ� 
**************************************/

void AC01_ActorOverlab::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FString str;
	str = FString::Printf
	(
		TEXT("Begin - Overlapped : %s, Other: %s"),
		*OverlappedActor->GetName(),
		*OtherActor->GetName()
	);

	CLog::Print(str);
	//CLog::Print(TEXT("Begin Overlap : " + OtherActor->GetName()));
}

void AC01_ActorOverlab::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FString str;
	str = FString::Printf
	(
		TEXT("End - Overlapped : %s, Other: %s"),
		*OverlappedActor->GetName(),
		*OtherActor->GetName()
	);

	CLog::Print(str);
	//CLog::Print(TEXT("End Overlap : " + OtherActor->GetName()), -1, 10, FColor::Red);
}

/*************************************

������ �浹 ó���� �ʿ��� ��?
������ �浹ü�� �����ϰ�
���ʷ���Ʈ �������� �����־�� �ϸ�
���� �������Ͽ� ��ħ�� �����־����

**************************************/