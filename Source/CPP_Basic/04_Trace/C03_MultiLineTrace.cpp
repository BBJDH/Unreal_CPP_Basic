#include "C03_MultiLineTrace.h"
#include "Global.h"
#include "Components/TextRenderComponent.h"

//#define LOG_AC03_MultiLineTrace 1


AC03_MultiLineTrace::AC03_MultiLineTrace()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");


	CreateTextRender();
}

void AC03_MultiLineTrace::BeginPlay()
{
	Super::BeginPlay();

}

void AC03_MultiLineTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector start = GetActorLocation();
	FVector start1 = FVector(start.X + 50, start.Y, start.Z);	//�� ���� ��
	FVector start2 = FVector(start.X - 50, start.Y, start.Z);	//����� ��

	FVector end1 = start1 + GetActorForwardVector() * 500;
	FVector end2 = start2 + GetActorForwardVector() * 500;

	//FVector end1 = start1 * GetActorForwardVector()

	TArray<AActor*> ignores;
	TArray<FHitResult> hitResult1;
	TArray<FHitResult> hitResult2;

	TArray<TEnumAsByte<EObjectTypeQuery>> queries;
	queries.Add(EObjectTypeQuery::ObjectTypeQuery1);	//1 : WorldStatic�� �ǹ�, 2�� ���� ���̳���
	//queries.Add(EObjectTypeQuery::ObjectTypeQuery2);	//1 : WorldStatic�� �ǹ�, 2�� ���� ���̳���

	UKismetSystemLibrary::LineTraceMulti	//ByChannel, ByProfile�� �ᱹ�� Channel�� ȣ����
	(
		GetWorld(),
		start1,
		end1,
		ETraceTypeQuery::TraceTypeQuery1,	//1���� Visibility 2���� ī�޶�
		false,								//�����浹 ����
		ignores,							//���ܸ�� ����
		EDrawDebugTrace::ForOneFrame, 
		hitResult1,							//�迭�� ����
		true
	);
/*************************************
�ش� ä�ο� ���Ͽ�,
ù ����� �߻��� �� ���� ��� �������� ��ȯ
**************************************/
	
	
	UKismetSystemLibrary::LineTraceMultiForObjects	//ByObjectType
	(
		GetWorld(),
		start2,
		end2,
		queries,
		false,
		ignores,
		EDrawDebugTrace::ForOneFrame,
		hitResult2, true
	);
	//ObjectTypes�� ���� ������ ������ ��� ������ ��ȯ
	//WorldDynamic���� �ٲٸ� �浹 ���ܵ�

#if LOG_AC03_MultiLineTrace



	TotalTime += DeltaTime;
	if (TotalTime >= 2.0f)
	{
		TotalTime = 0;

		CLog::Log("--- Channel ---");
		for (FHitResult& hitResult : hitResult1)
			CLog::Log(hitResult.GetActor()->GetName());

		CLog::Log("--- Objects ---");
		for (FHitResult& hitResult : hitResult2)
			CLog::Log(hitResult.GetActor()->GetName());
	}

#endif


}

