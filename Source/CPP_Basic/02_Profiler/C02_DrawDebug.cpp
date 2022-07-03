

#include "02_Profiler/C02_DrawDebug.h"
#include "Global.h"
#include "Components/PointLightComponent.h"


AC02_DrawDebug::AC02_DrawDebug()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<UPointLightComponent>(this, &PointLight, "Light");

	InitLoation[0] = FVector(0, 0, 0);
	InitLoation[1] = FVector(0, 1000, 0);
	InitLoation[2] = FVector(0, 500, 0);
	InitLoation[3] = FVector(0, 1500, 0);
	InitLoation[4] = FVector(500, 1000, 0);

	Box = FBox(FVector(-50, -100, -50), FVector(50, 100, 50));
	//Box의 Min좌표, Max 좌표, X:100 Y:200 Z:100인 직육면체 생성
	//0,0,0 지점 생성
	//크기로도 정의 가능하고 위치로도 정의가 가능 위의경우는 위치로 정의하여 Min Max

	Transform.SetLocation(FVector(200, 1500, 0));

}

void AC02_DrawDebug::BeginPlay()
{
	Super::BeginPlay();

	PointLight->SetVisibility(false);
	
}

void AC02_DrawDebug::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int32 i = 0; i < 5; i++)
		Location[i] = InitLoation[i] + GetActorLocation();

	DrawDebugSolidBox(GetWorld(), Location[0] + Box.GetCenter(), Box.GetExtent(), FColor::Red);
	//월드, 위치, 높이 색상
	DrawDebugPoint(GetWorld(), Location[1], 100, FColor::Green);
	//위치, 크기
	DrawDebugSphere(GetWorld(), Location[2], 100, 30, FColor::Blue);
	//위치, 크기, 구의 정밀도
	DrawDebugCircle(GetWorld(), Location[3], 100, 50, FColor::Magenta);
	//2D원 위치, 크기, 원의 정밀도
	DrawDebugLine(GetWorld(), Location[2], Location[3], FColor::Yellow, false,-1, 0, 10);
	//시작점, 끝점, 색깔, Default : 한번 그리고나서 계속 둘지(아니면 false),
	//둔다면 지속시간(false -1),깊이 우선순위, 두께
	
	FVector location = Location[1];

	location.X += 10;
	location.Y += 10;
	location.Z += FMath::Sin(GetWorld()->GetTimeSeconds()*3.0f) * 300.0f;

	DrawDebugCapsule(GetWorld(), location, 200, 50, FQuat::Identity, FColor::White);
	//월드, 위치, 높이(반), 반지름, 회전값, 색상
	DrawDebugDirectionalArrow(GetWorld(), Location[3], location, 400, FColor::White, false, -1, 0, 10);
	//월드, 시작지점, 도착지점, 화살표 두께, 색상, Line과 동일(마지막 두께)


	
	//FMath::Abs(FMath::Cos(GetWorld()->GetTimeSeconds()*5.0f)); //폴짝폴짝 뛰는 그래프 형성
	bool b = FMath::Cos(GetWorld()->GetTimeSeconds()*5.0f) * 0.5f + 0.5f >= 0.5f;
	PointLight->SetVisibility(b);
	//되돌린다면 -0.5 이후 2배

}

