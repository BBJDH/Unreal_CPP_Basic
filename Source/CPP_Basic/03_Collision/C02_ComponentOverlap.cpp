

#include "03_Collision/C02_ComponentOverlap.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC02_ComponentOverlap::AC02_ComponentOverlap()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);

	CreateTextRender();

	Box->SetRelativeScale3D(FVector(3));  //XYZ ���� 3��
	Box->bHiddenInGame = false;

	//CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Root);
	//Text->SetRelativeLocation(FVector(0, 0, 100));
	//Text->SetRelativeRotation(FRotator(0, 100, 0));

	
	///*************************************
	// ������ ȸ�� ���� : Roll Pitch Yaw
	// C++	: Pitch(Y) Yaw(Z) Roll(X) �� �ٸ�

	//**************************************/

	//Text->SetRelativeScale3D(FVector(2)); //BP �ڹ��� ��װ� 2����
	//Text->TextRenderColor = FColor::Red;
	//Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	////��� ����
	//Text->Text = FText::FromString(GetName().Replace(TEXT("Default__"), TEXT("")));
	////����Ʈ�� Default__�� ������ ���ִ� ó��
}

void AC02_ComponentOverlap::BeginPlay()
{
	Super::BeginPlay();
	
	//FComponentBeginOverlapSignature �ڷ���
	Box->OnComponentBeginOverlap.AddDynamic(this, &AC02_ComponentOverlap::OnComponentBeginOverlap);
	//FComponentEndOverlapSignature �ڷ���
	Box->OnComponentEndOverlap.AddDynamic(this, &AC02_ComponentOverlap::OnComponentEndOverlap);

	//UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult &, SweepResult
}

void AC02_ComponentOverlap::OnComponentBeginOverlap
(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult
)
{
	FString str;

	str = "--------- Begin ---------";


	str.Append("Begin Overlap Component : ");
	str.Append(OverlappedComponent->GetName());
	CLog::Log(str);

	str = "";
	str.Append("Other Actor : ");
	str.Append(OtherActor->GetName());
	CLog::Log(str);

	str = "";
	str.Append("Other Component : ");
	str.Append(OtherComp->GetName());
	CLog::Log(str);
}

void AC02_ComponentOverlap::OnComponentEndOverlap
(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex
)
{
	FString str;
	str = "--------- End ---------";

	str.Append("End Overlap Component : ");
	str.Append(OverlappedComponent->GetName());
	CLog::Log(str);

	str = "";
	str.Append("Other Actor : ");
	str.Append(OtherActor->GetName());
	CLog::Log(str);

	str = "";
	str.Append("Other Component : ");
	str.Append(OtherComp->GetName());
	CLog::Log(str);
}
