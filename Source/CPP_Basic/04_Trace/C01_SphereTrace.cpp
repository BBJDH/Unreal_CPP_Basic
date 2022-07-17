

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
	//파티클 시스템 컴포넌트를 통해 재생하기 위해 템플릿안에 세팅
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
	types.Add(EObjectTypeQuery::ObjectTypeQuery4); //4번, 피직스바디
	//원한다면 Add로 추가

	TArray<AActor*> ignores;		//값을 채울 디폴트값 선언
	TArray<FHitResult> hitResults;	//결과값을 저장할 곳
	//소스/런타임  -> 게임 해더는 다 여기에
	//월드 유효하다면
	//World->SweepMultiByObjectType(OutHits, Start, End, FQuat::Identity, ObjectParams, FCollisionShape::MakeSphere(Radius), Params) 
	//반환
	bool b = UKismetSystemLibrary::SphereTraceMultiForObjects
	(
		GetWorld(),				//확인 할 월드
		location,				//시작, 구의 중심
		location,				//끝, 해당지점 까지 구형태로 Trace
		300,					//반경
		types,					//오브젝트 타입(충돌 타입) TArray<TEnumAsByte<EDrawDebugTrace::Type>> //콜리전 - 오브젝트 유형(월드스테틱, 폰, 피직스 바디 등등)
		false,					//bTraceComplex
		ignores,				//ActorsIgnor
		DebugType,				//DrawDebugType
		hitResults,				//HitResults
		true,					//bIgnoreSelf
		FLinearColor::Green,	//TraceColor
		FLinearColor::Blue,		//TraceHitColor
		DrawDuration			//디버그 그릴 시간
	);	
	//반환이 static bool이기 때문에 하나라도 충돌하면 true 반환

	//하나라도 충돌하면 b는 True
	CheckFalse(b);


	Particle->ResetParticles();
	Particle->SetActive(true);
/*************************************
파티클은 재생시간을 끝까지 재생했다면
다시 재생시간을 처음으로 돌려서 재생시켜줘야 한다(컴포넌트 이용시)
ResetParticles()이 필요
이후 활성화 하면 플레이.

**************************************/
	for (const FHitResult& hitResult : hitResults)
	{
		UStaticMeshComponent * mesh = Cast<UStaticMeshComponent>(hitResult.GetActor()->GetRootComponent());
		//box 들의 스태틱 메시 컴포넌트로 캐스팅, 스태틱 메시 액터들은 스태틱 메시 컴포넌트가 루트로 되어있다
		if (!!mesh && mesh->IsSimulatingPhysics()) //물리값을 받도록 되어있다면
			mesh->AddRadialImpulse(location, 1000, mesh->GetMass() * ImpulseAmount, ERadialImpulseFalloff::RIF_Linear);
		//구면으로 퍼져나가는 힘을 부여, 위치, 반경, 힘(ma로 줌), Linear는 점점 힘이 줄어듬,Constant는 힘이 일정
	}
}

/*************************************
상위 메모리 하위메모리
상위 메모리 - 프로그램 공용영역
상위는 고정크기 (때문에 싱글턴 남발하면 안된다)
싱글턴 호출 삭제는 한구간에서 해주자 위처럼 고정크기인 상위메모리에서 오버플로우나면
찾기 힘들다..
하위메모리 - 스택과 힙이 할당
때문에 하위가 유동 크기를 가진다
상위 메모리에 접근하여 해당 내용을 임의 해제하는것은 일반적으로 불가능 하다
가능하게 하려면 reinterpret_cast<>를 통해 사용한다

https://dataonair.or.kr/db-tech-reference/d-lounge/technical-data/?mod=document&uid=235959
**************************************/