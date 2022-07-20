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
	//������ �Ǹ����� 2�� �̻��̾�� ��

	FVector start = Cylinders[0]->GetActorLocation();
	FVector end = Cylinders[1]->GetActorLocation();

	//DrawDebugLine
	//����� ���� �߱�
	{
		start.Z -= 20;
		end.Z -= 20;

		DrawDebugLine(GetWorld(), start, end, FColor::Blue);
	}

	//LineTrace (���� ����, 20���ſ� �ٽ� 40 ����)
	{
		start.Z += 40;
		end.Z += 40;

		TArray<AActor*> ignores;
		ignores.Add(Cylinders[0]);
		ignores.Add(Cylinders[1]);

		FHitResult hitResult;
		//�޾ƿð� �̸� ����
		//GetWorld()->LineTraceSingleByProfile() �� �����ϴ�
		UKismetSystemLibrary::LineTraceSingleByProfile
		(
			GetWorld(),
			start,
			end,
			"Pawn",							//�������� �������� ����Ѵ�
			false,							//�����浹 ����
			ignores,						//���ܸ��
			EDrawDebugTrace::ForOneFrame,	//����� Ÿ��
			hitResult,						//���� ����ü
			true
		);

		if (hitResult.bBlockingHit)//�浹 �Ǿ��ٸ�
		{
			if (OnLineTraceResult.IsBound())
				OnLineTraceResult.Broadcast(hitResult.GetActor(), FLinearColor::MakeRandomColor());
		}
	}
}

void AC02_LineTrace::StartLaunch(AActor* InActor, FLinearColor InColor)
{
	ACharacter* character = Cast<ACharacter>(InActor);
	//��ġ�� ���� ĳ������ ĳ���� �����Ʈ�� �ʿ�

	CheckNull(character);
	character->LaunchCharacter(LaunchAmount, true, false);
}
