

#include "03_Collision/C04_Trigger.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC04_Trigger::AC04_Trigger()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);

	CreateTextRender();

	Box->SetRelativeScale3D(FVector(3));  //XYZ ���� 3��
	Box->bHiddenInGame = false;
}

void AC04_Trigger::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &AC04_Trigger::OnComponentBeginOverlap);
	//FComponentEndOverlapSignature �ڷ���
	Box->OnComponentEndOverlap.AddDynamic(this, &AC04_Trigger::OnComponentEndOverlap);
}

void AC04_Trigger::OnComponentBeginOverlap
(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult
)
{
	if (OnFBoxLightBeginOverlap.IsBound())//�ش� �������̼ǿ� ����� �Լ��� �ִٸ�
		OnFBoxLightBeginOverlap.Execute();

	if (OnBoxLightColorOverlap.IsBound())
	{
		FLinearColor color = FLinearColor::MakeRandomColor();
		FString str = OnBoxLightColorOverlap.Execute(color);

		CLog::Print(str);
	}
}

void AC04_Trigger::OnComponentEndOverlap
(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex
)
{

	if (OnFBoxLightEndOverlap.IsBound())
		OnFBoxLightEndOverlap.Execute();
}
/*************************************
������ �������̼��� ���Ͽ� ���

DECLARE_Delegate �̱� ĳ��Ʈ 1��1 ���� ���� �ȵ�, ���� ����
�Ķ���� �ȹ����� ���� �״�� ��� �Ķ���Ͱ� �ִٸ�

DECLARE_Delegate_TwoParams(��������Ʈ �̸�(����� ����), �Ķ���� Ÿ��1, �Ķ���� Ÿ��2)

DECLARE_Delegate Multicast �ϳ��� �������̼ǿ� �������� �Լ��� ���� ���� ���� ���� �ȵ�

DECLARE_Delegate Dynamic_DELEGATE		 ���� ���� ����, ���� ����
DECLARE_Delegate_Dynamic_DELEGATE_TwoParams
(��������Ʈ �̸�, �Ķ���� Ÿ��1, �Ķ���� �̸�1, �Ķ���� Ÿ��2,�Ķ���� �̸�2)

DECLARE_Delegate Dynamic Multicast  ���� ���� ����, ���� �Ұ�

DECLARE_Delegate Dynamic SPARS_DELEGATE		��������, ���ϰ���(�̱۸�, ��Ƽ�� ������������ ������ �Ǻ��� �� ����)
DECLARE_Delegate Dynamic SPARS_DELEGATE_TwoParams(��������Ʈ �̸�, �Ҽ� Ŭ������(�������̼��� �����(�Ҽ�) Ŭ����), ������,
�Ķ���� Ÿ��1, �Ķ���� �̸�1, �Ķ���� Ÿ��2,�Ķ���� �̸�2))



DECLARE_EVENT ���̳��� ��������Ʈ�� ����� ����, ���� �Ұ�
��� ��������Ʈ�� �������� ��޵����� �̺�Ʈ�� Ŭ������ �Ҽ��Ͽ� Ŭ���� ���� �ȿ����� ��� ����
//���� ������� ������ ��ſ� ���Ľ� ��������Ʈ�� �����
**************************************/