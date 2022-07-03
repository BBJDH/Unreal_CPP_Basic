

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
	//Box�� Min��ǥ, Max ��ǥ, X:100 Y:200 Z:100�� ������ü ����
	//0,0,0 ���� ����
	//ũ��ε� ���� �����ϰ� ��ġ�ε� ���ǰ� ���� ���ǰ��� ��ġ�� �����Ͽ� Min Max

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
	//����, ��ġ, ���� ����
	DrawDebugPoint(GetWorld(), Location[1], 100, FColor::Green);
	//��ġ, ũ��
	DrawDebugSphere(GetWorld(), Location[2], 100, 30, FColor::Blue);
	//��ġ, ũ��, ���� ���е�
	DrawDebugCircle(GetWorld(), Location[3], 100, 50, FColor::Magenta);
	//2D�� ��ġ, ũ��, ���� ���е�
	DrawDebugLine(GetWorld(), Location[2], Location[3], FColor::Yellow, false,-1, 0, 10);
	//������, ����, ����, Default : �ѹ� �׸����� ��� ����(�ƴϸ� false),
	//�дٸ� ���ӽð�(false -1),���� �켱����, �β�
	
	FVector location = Location[1];

	location.X += 10;
	location.Y += 10;
	location.Z += FMath::Sin(GetWorld()->GetTimeSeconds()*3.0f) * 300.0f;

	DrawDebugCapsule(GetWorld(), location, 200, 50, FQuat::Identity, FColor::White);
	//����, ��ġ, ����(��), ������, ȸ����, ����
	DrawDebugDirectionalArrow(GetWorld(), Location[3], location, 400, FColor::White, false, -1, 0, 10);
	//����, ��������, ��������, ȭ��ǥ �β�, ����, Line�� ����(������ �β�)


	
	//FMath::Abs(FMath::Cos(GetWorld()->GetTimeSeconds()*5.0f)); //��¦��¦ �ٴ� �׷��� ����
	bool b = FMath::Cos(GetWorld()->GetTimeSeconds()*5.0f) * 0.5f + 0.5f >= 0.5f;
	PointLight->SetVisibility(b);
	//�ǵ����ٸ� -0.5 ���� 2��

}

