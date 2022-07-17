#include "C03_MultiLineTrace.h"
#include "Global.h"
#include "Components/TextRenderComponent.h"

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
	FVector start1 = FVector(start.X + 50, start.Y, start.Z); 
	FVector start2 = FVector(start.X - 50, start.Y, start.Z);

	FVector end1 = start1 * GetActorForwardVector() * 500;
	FVector end2 = start2 * GetActorForwardVector() * 500;


	TArray<AActor*> ignores;
	TArray<FHitResult> hitResult1;
	TArray<FHitResult> hitResult2;

	TArray<TEnumAsByte<EObjectTypeQuery>> queries;
	queries.Add(EObjectTypeQuery::ObjectTypeQuery1);	//WorldStatic을 의미

	UKismetSystemLibrary::LineTraceMulti
	(
		GetWorld(),
		start1,
		end1,
		ETraceTypeQuery::TraceTypeQuery1,	//1번이 Visibility
		false,								//복합충돌 유무
		ignores,							//예외목록 없음
		EDrawDebugTrace::ForOneFrame, 
		hitResult1, 
		true
	);
	
	UKismetSystemLibrary::LineTraceMultiForObjects
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

	TotalTime += DeltaTime;
	if (TotalTime >= 2.0f)
	{
		TotalTime = 0;

		CLog::Log("Channel");
		for (FHitResult& hitResult : hitResult1)
			CLog::Log(hitResult.GetActor()->GetName());

		CLog::Log("Objects");
		for (FHitResult& hitResult : hitResult2)
			CLog::Log(hitResult.GetActor()->GetName());
	}

}

