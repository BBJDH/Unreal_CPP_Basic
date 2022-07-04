

#include "02_Profiler/C02_DrawDebug.h"
#include "Global.h"
#include "Components/PointLightComponent.h"


AC02_DrawDebug::AC02_DrawDebug()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<UPointLightComponent>(this, &PointLight, "Light");

	InitLocation[0] = FVector(0, 0, 0);
	InitLocation[1] = FVector(0, 1000, 0);
	InitLocation[2] = FVector(0, 500, 0);
	InitLocation[3] = FVector(0, 1500, 0);
	InitLocation[4] = FVector(500, 1000, 0);
	//그림들 그릴 상대 좌표

	Box = FBox(FVector(-50, -100, -50), FVector(50, 100, 50));
	//Box의 Min좌표, Max 좌표, X:100 Y:200 Z:100인 직육면체 생성
	//0,0,0 지점 생성
	//크기로도 정의 가능하고 위치로도 정의가 가능 위의경우는 위치로 정의하여 Min Max

	//Transform.SetLocation(FVector(200, 1500, 0));

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
		Location[i] = InitLocation[i] + GetActorLocation();
	//현재 RootComponent 좌표 +지정된 상대 좌표

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
	//둔다면 지속시간 초(false -1),깊이 우선순위, 두께
	
	FVector location = Location[2];

	location.X += 10;
	location.Y += 10;
	location.Z += FMath::Sin(GetWorld()->GetTimeSeconds()*3.0f) * 300.0f;
	//GetWorld()->GetTimeSeconds() 게임이 시작후 현재까지의 시작
	//Sin Table을 사용하여 유사값을 사용(정확하지 않음)

	DrawDebugCapsule(GetWorld(), location, 200, 50, FQuat::Identity, FColor::White);
	//월드, 위치, 높이(반), 반지름, 회전값, 색상
	DrawDebugDirectionalArrow(GetWorld(), Location[3], location, 400, FColor::Black, false, -1, 0, 10);
	//월드, 시작지점, 도착지점, 화살표 두께, 색상, Line과 동일(마지막 두께)



	/*쿼터니언 정리할 것*/
	//짐벌락
	
	//FMath::Abs(FMath::Cos(GetWorld()->GetTimeSeconds()*5.0f)); //폴짝폴짝 뛰는 그래프 형성
	bool b = FMath::Cos(GetWorld()->GetTimeSeconds()*5.0f) * 0.5f + 0.5f >= 0.5f;
	PointLight->SetVisibility(b);
	//되돌린다면 -0.5 이후 2배
	//FMath::Sign()
	//FMath::Sign() : 부호 반환 함수
	//정리할 것
	//easeing 수식 표현(함수 치트 시트)

	/*************************************
	2차원에서의 회전 1자유도 xy평면안에서만 회전 가능
	3차원에서의 회전 3자유도 각 축에대해서 회전 가능

	Z 축 회전
	cosΘ	-sinΘ	0	0
	sinΘ	cosΘ	0	0
	0		0		1	0
	0		0		0	1


	Y 축 회전
	cosΘ	0		sinΘ	0
	0		1		0		0
	-sinΘ	0		cosΘ	0
	0		0		0		1

	X 축 회전
	1		0		0		0
	0		cosΘ	-sinΘ	0
	0		sinΘ	cosΘ	0
	0		0		0		1





	짐벌락 : 오일러각을 이용한 회전 과정에서 두 개 혹은 세 개의 축이 겹쳐 한개 혹은 두개의 축이 자유도를 잃고
				같은 방향으로 오브젝터의 회전 축이 겹치는 현상
	오일러각을 이용한 회전(각 축에 대해 순서대로 회전을 실시 하기 때문에 이 과정에서 다른 축에 영향을 준다) 
	오일러회전의 경우 회전 행력 교환법칙이 성립하지 않으므로 순서를 준수하여야 한다
	짐벌락을 유도하려면 최상위와 최하위 사이에있는 축을 회전하여 최상과 최하위의 축을 일치시키면 된다 

	이를 해결하기위해
	Quaternion : 쿼터니언
	(d,(a,b,c)) = (스칼라(3차원백터))
	다시말해 (회전각 (회전축 3개))로 표현되어 4 자유도를 가지게 한다
	※단, 회전축 백터의 크기는 1이어야 한다

	
	^q = (cosΘ/2, sinΘ/2u)  |u| = 1
	즉 쉽게 말하면 노멀라이즈된 회전축 u를 회전각 Θ만큼 회전 한다라는 의미
	(xyz에 대해 회전할 회전축에 대해서 회전을 가하면 해당 회전하는 회전 축이 생기므로)


	점 P(x,y,z)를 회전한다면
	p = (0,P) 쿼터니언 생성
	r = (cosΘ/2, sinΘ/2v)를  (v는 회전축을 의미한다)
	P' = rpr*
	회전한 점 = r * P * r(켤레 복소수)


	우선 쿼터니언은 오일러보다 연산이 빠르며 정확도도 오일러보다 높다
	짐벌락이 발생할 확률이 낮다
	행렬보다 점유 메모리 영역이 작고 계산 부하가 낮다
	임의의 축에서도 회전을 손쉽게 할 수 있다. 
	오차가 쉽게 발생하지 않는다(기좀 부동소수점 방식이었기 때문에 )
	두 회전 사이의 매끄러운 보간 표현이 가능 

	-> 실제로 우리는 오일러값으로 조정하지만 엔진 내부에서의 계산은 쿼터니언으로 간소화되며
	-> 다시 GPU의 연산을 위해 그래픽스 파이프라인으로 들어갈 때는 결국 Transporm MAtt를 만들어야하므로
	-> 다시 행렬로 변환되어 넘어간다

	**************************************/
	/*





	*/

}

