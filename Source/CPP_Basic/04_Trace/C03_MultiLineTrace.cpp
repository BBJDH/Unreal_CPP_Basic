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
	FVector start1 = FVector(start.X + 50, start.Y, start.Z);	//더 깊은 쪽
	FVector start2 = FVector(start.X - 50, start.Y, start.Z);	//가까운 쪽

	FVector end1 = start1 + GetActorForwardVector() * 500;
	FVector end2 = start2 + GetActorForwardVector() * 500;

	//FVector end1 = start1 * GetActorForwardVector()

	TArray<AActor*> ignores;
	TArray<FHitResult> hitResult1;
	TArray<FHitResult> hitResult2;

	TArray<TEnumAsByte<EObjectTypeQuery>> queries;
	queries.Add(EObjectTypeQuery::ObjectTypeQuery1);	//1 : WorldStatic을 의미, 2는 월드 다이나믹
	//queries.Add(EObjectTypeQuery::ObjectTypeQuery2);	//1 : WorldStatic을 의미, 2는 월드 다이나믹

	UKismetSystemLibrary::LineTraceMulti	//ByChannel, ByProfile도 결국은 Channel을 호출함
	(
		GetWorld(),
		start1,
		end1,
		ETraceTypeQuery::TraceTypeQuery1,	//1번이 Visibility 2번이 카메라
		false,								//복합충돌 유무
		ignores,							//예외목록 없음
		EDrawDebugTrace::ForOneFrame, 
		hitResult1,							//배열에 저장
		true
	);
/*************************************
해당 채널에 대하여,
첫 블록이 발생할 때 까지 모든 오버랩을 반환
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
	//ObjectTypes에 의해 지정된 유형의 모든 관통을 반환
	//WorldDynamic으로 바꾸면 충돌 제외됨

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

