

#include "04_Trace/C01_SphereTrace.h"
#include "Global.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"

AC01_SphereTrace::AC01_SphereTrace()
{
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Particle, "Particle");

	UParticleSystem* particle;
	CHelpers::GetAsset<UParticleSystem>(&particle, "ParticleSystem'/Game/M5VFXVOL2/Particles/Explosion/Fire_Exp_00.Fire_Exp_00'");
	Particle->SetTemplate(particle);
	//��ƼŬ �ý��� ������Ʈ�� ���� ����ϱ� ���� ���ø��ȿ� ����
	Particle->bAutoActivate = false;

}

void AC01_SphereTrace::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC01_SphereTrace::OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FVector location = GetActorLocation();

	TArray<TEnumAsByte<EObjectTypeQuery>> types;
	types.Add(EObjectTypeQuery::ObjectTypeQuery4); //4��, �������ٵ�
	//���Ѵٸ� Add�� �߰�

	TArray<AActor*> ignores;		//���� ä�� ����Ʈ�� ����
	TArray<FHitResult> hitResults;	//������� ������ ��
	//�ҽ�/��Ÿ��  -> ���� �ش��� �� ���⿡
	//���� ��ȿ�ϴٸ�
	//World->SweepMultiByObjectType(OutHits, Start, End, FQuat::Identity, ObjectParams, FCollisionShape::MakeSphere(Radius), Params) 
	//��ȯ
	bool b = UKismetSystemLibrary::SphereTraceMultiForObjects
	(
		GetWorld(),				//Ȯ�� �� ����
		location,				//����, ���� �߽�
		location,				//��, �ش����� ���� �����·� Trace
		300,					//�ݰ�
		types,					//������Ʈ Ÿ��(�浹 Ÿ��) TArray<TEnumAsByte<EDrawDebugTrace::Type>> //�ݸ��� - ������Ʈ ����(���彺��ƽ, ��, ������ �ٵ� ���)
		false,					//bTraceComplex
		ignores,				//ActorsIgnor
		DebugType,				//DrawDebugType
		hitResults,				//HitResults
		true,					//bIgnoreSelf
		FLinearColor::Green,	//TraceColor
		FLinearColor::Blue,		//TraceHitColor
		DrawDuration			//����� �׸� �ð�
	);	
	//��ȯ�� static bool�̱� ������ �ϳ��� �浹�ϸ� true ��ȯ

	//�ϳ��� �浹�ϸ� b�� True
	CheckFalse(b);


	Particle->ResetParticles();
	Particle->SetActive(true);
/*************************************
��ƼŬ�� ����ð��� ������ ����ߴٸ�
�ٽ� ����ð��� ó������ ������ ���������� �Ѵ�(������Ʈ �̿��)
ResetParticles()�� �ʿ�
���� Ȱ��ȭ �ϸ� �÷���.

**************************************/
	for (const FHitResult& hitResult : hitResults)
	{
		UStaticMeshComponent * mesh = Cast<UStaticMeshComponent>(hitResult.GetActor()->GetRootComponent());
		//box ���� ����ƽ �޽� ������Ʈ�� ĳ����, ����ƽ �޽� ���͵��� ����ƽ �޽� ������Ʈ�� ��Ʈ�� �Ǿ��ִ�
		if (!!mesh && mesh->IsSimulatingPhysics()) //�������� �޵��� �Ǿ��ִٸ�
			mesh->AddRadialImpulse(location, 1000, mesh->GetMass() * ImpulseAmount, ERadialImpulseFalloff::RIF_Linear);
		//�������� ���������� ���� �ο�, ��ġ, �ݰ�, ��(ma�� ��), Linear�� ���� ���� �پ��,Constant�� ���� ����
	}
}

/*************************************
���� �޸� �����޸�
���� �޸� - ���α׷� ���뿵��
������ ����ũ�� (������ �̱��� �����ϸ� �ȵȴ�)
�̱��� ȣ�� ������ �ѱ������� ������ ��ó�� ����ũ���� �����޸𸮿��� �����÷ο쳪��
ã�� �����..
�����޸� - ���ð� ���� �Ҵ�
������ ������ ���� ũ�⸦ ������
���� �޸𸮿� �����Ͽ� �ش� ������ ���� �����ϴ°��� �Ϲ������� �Ұ��� �ϴ�
�����ϰ� �Ϸ��� reinterpret_cast<>�� ���� ����Ѵ�

https://dataonair.or.kr/db-tech-reference/d-lounge/technical-data/?mod=document&uid=235959
**************************************/