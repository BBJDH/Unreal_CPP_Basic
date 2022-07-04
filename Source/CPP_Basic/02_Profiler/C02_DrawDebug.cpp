

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
	//�׸��� �׸� ��� ��ǥ

	Box = FBox(FVector(-50, -100, -50), FVector(50, 100, 50));
	//Box�� Min��ǥ, Max ��ǥ, X:100 Y:200 Z:100�� ������ü ����
	//0,0,0 ���� ����
	//ũ��ε� ���� �����ϰ� ��ġ�ε� ���ǰ� ���� ���ǰ��� ��ġ�� �����Ͽ� Min Max

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
	//���� RootComponent ��ǥ +������ ��� ��ǥ

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
	//�дٸ� ���ӽð� ��(false -1),���� �켱����, �β�
	
	FVector location = Location[2];

	location.X += 10;
	location.Y += 10;
	location.Z += FMath::Sin(GetWorld()->GetTimeSeconds()*3.0f) * 300.0f;
	//GetWorld()->GetTimeSeconds() ������ ������ ��������� ����
	//Sin Table�� ����Ͽ� ���簪�� ���(��Ȯ���� ����)

	DrawDebugCapsule(GetWorld(), location, 200, 50, FQuat::Identity, FColor::White);
	//����, ��ġ, ����(��), ������, ȸ����, ����
	DrawDebugDirectionalArrow(GetWorld(), Location[3], location, 400, FColor::Black, false, -1, 0, 10);
	//����, ��������, ��������, ȭ��ǥ �β�, ����, Line�� ����(������ �β�)



	/*���ʹϾ� ������ ��*/
	//������
	
	//FMath::Abs(FMath::Cos(GetWorld()->GetTimeSeconds()*5.0f)); //��¦��¦ �ٴ� �׷��� ����
	bool b = FMath::Cos(GetWorld()->GetTimeSeconds()*5.0f) * 0.5f + 0.5f >= 0.5f;
	PointLight->SetVisibility(b);
	//�ǵ����ٸ� -0.5 ���� 2��
	//FMath::Sign()
	//FMath::Sign() : ��ȣ ��ȯ �Լ�
	//������ ��
	//easeing ���� ǥ��(�Լ� ġƮ ��Ʈ)

	/*************************************
	2���������� ȸ�� 1������ xy���ȿ����� ȸ�� ����
	3���������� ȸ�� 3������ �� �࿡���ؼ� ȸ�� ����

	Z �� ȸ��
	cos��	-sin��	0	0
	sin��	cos��	0	0
	0		0		1	0
	0		0		0	1


	Y �� ȸ��
	cos��	0		sin��	0
	0		1		0		0
	-sin��	0		cos��	0
	0		0		0		1

	X �� ȸ��
	1		0		0		0
	0		cos��	-sin��	0
	0		sin��	cos��	0
	0		0		0		1





	������ : ���Ϸ����� �̿��� ȸ�� �������� �� �� Ȥ�� �� ���� ���� ���� �Ѱ� Ȥ�� �ΰ��� ���� �������� �Ұ�
				���� �������� ���������� ȸ�� ���� ��ġ�� ����
	���Ϸ����� �̿��� ȸ��(�� �࿡ ���� ������� ȸ���� �ǽ� �ϱ� ������ �� �������� �ٸ� �࿡ ������ �ش�) 
	���Ϸ�ȸ���� ��� ȸ�� ��� ��ȯ��Ģ�� �������� �����Ƿ� ������ �ؼ��Ͽ��� �Ѵ�
	�������� �����Ϸ��� �ֻ����� ������ ���̿��ִ� ���� ȸ���Ͽ� �ֻ�� �������� ���� ��ġ��Ű�� �ȴ� 

	�̸� �ذ��ϱ�����
	Quaternion : ���ʹϾ�
	(d,(a,b,c)) = (��Į��(3��������))
	�ٽø��� (ȸ���� (ȸ���� 3��))�� ǥ���Ǿ� 4 �������� ������ �Ѵ�
	�ش�, ȸ���� ������ ũ��� 1�̾�� �Ѵ�

	
	^q = (cos��/2, sin��/2u)  |u| = 1
	�� ���� ���ϸ� ��ֶ������ ȸ���� u�� ȸ���� �ȸ�ŭ ȸ�� �Ѵٶ�� �ǹ�
	(xyz�� ���� ȸ���� ȸ���࿡ ���ؼ� ȸ���� ���ϸ� �ش� ȸ���ϴ� ȸ�� ���� ����Ƿ�)


	�� P(x,y,z)�� ȸ���Ѵٸ�
	p = (0,P) ���ʹϾ� ����
	r = (cos��/2, sin��/2v)��  (v�� ȸ������ �ǹ��Ѵ�)
	P' = rpr*
	ȸ���� �� = r * P * r(�ӷ� ���Ҽ�)


	�켱 ���ʹϾ��� ���Ϸ����� ������ ������ ��Ȯ���� ���Ϸ����� ����
	�������� �߻��� Ȯ���� ����
	��ĺ��� ���� �޸� ������ �۰� ��� ���ϰ� ����
	������ �࿡���� ȸ���� �ս��� �� �� �ִ�. 
	������ ���� �߻����� �ʴ´�(���� �ε��Ҽ��� ����̾��� ������ )
	�� ȸ�� ������ �Ų����� ���� ǥ���� ���� 

	-> ������ �츮�� ���Ϸ������� ���������� ���� ���ο����� ����� ���ʹϾ����� ����ȭ�Ǹ�
	-> �ٽ� GPU�� ������ ���� �׷��Ƚ� �������������� �� ���� �ᱹ Transporm MAtt�� �������ϹǷ�
	-> �ٽ� ��ķ� ��ȯ�Ǿ� �Ѿ��

	**************************************/
	/*





	*/

}

