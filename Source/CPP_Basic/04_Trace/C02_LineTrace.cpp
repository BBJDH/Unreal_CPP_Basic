#include "C02_LineTrace.h"
#include "Global.h"
#include "C02_Cylinder.h"
#include "GameFramework/Character.h"
#include "Components/TextRenderComponent.h"

AC02_LineTrace::AC02_LineTrace()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");

	CreateTextRender();
}

void AC02_LineTrace::BeginPlay()
{
	Super::BeginPlay();

	CHelpers::FindActors<AC02_Cylinder>(GetWorld(), Cylinders);
	OnLineTraceResult.AddDynamic(this, &AC02_LineTrace::StartLaunch);
}

void AC02_LineTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(Cylinders.Num() >= 2);
	//가져온 실린더가 2개 이상이어야 함

	FVector start = Cylinders[0]->GetActorLocation();
	FVector end = Cylinders[1]->GetActorLocation();

	//DrawDebugLine
	//디버그 라인 긋기
	{
		start.Z -= 20;
		end.Z -= 20;

		DrawDebugLine(GetWorld(), start, end, FColor::Blue);
	}

	//LineTrace (실제 라인, 20뺀거에 다시 40 위로)
	{
		start.Z += 40;
		end.Z += 40;

		TArray<AActor*> ignores;
		ignores.Add(Cylinders[0]);
		ignores.Add(Cylinders[1]);

		FHitResult hitResult;
		//받아올곳 미리 생성
		//GetWorld()->LineTraceSingleByProfile() 도 가능하다
		UKismetSystemLibrary::LineTraceSingleByProfile
		(
			GetWorld(),
			start,
			end,
			"Pawn",							//프로파일 폰설정을 사용한다
			false,							//복합충돌 여부
			ignores,						//예외목록
			EDrawDebugTrace::ForOneFrame,	//디버그 타입
			hitResult,						//받을 구조체
			true
		);

		if (hitResult.bBlockingHit)//충돌 되었다면
		{
			if (OnLineTraceResult.IsBound())
				OnLineTraceResult.Broadcast(hitResult.GetActor(), FLinearColor::MakeRandomColor());
		}
	}
}

void AC02_LineTrace::StartLaunch(AActor* InActor, FLinearColor InColor)
{
	ACharacter* character = Cast<ACharacter>(InActor);
	//런치를 위해 캐릭터의 캐릭터 무브먼트가 필요

	CheckNull(character);
	character->LaunchCharacter(LaunchAmount, true, false);
}
