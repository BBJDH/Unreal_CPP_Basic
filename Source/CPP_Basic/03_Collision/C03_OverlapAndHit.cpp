

#include "03_Collision/C03_OverlapAndHit.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC03_OverlapAndHit::AC03_OverlapAndHit()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);

	CreateTextRender();

	Box->SetRelativeScale3D(FVector(3));  //XYZ ���� 3��
	Box->bHiddenInGame = false;
}

void AC03_OverlapAndHit::BeginPlay()
{
	Super::BeginPlay();
	//FComponentBeginOverlapSignature �ڷ���
	Box->OnComponentBeginOverlap.AddDynamic(this, &AC03_OverlapAndHit::OnComponentBeginOverlap);
	//FComponentEndOverlapSignature �ڷ���
	Box->OnComponentEndOverlap.AddDynamic(this, &AC03_OverlapAndHit::OnComponentEndOverlap);
	
	Box->OnComponentHit.AddDynamic(this, &AC03_OverlapAndHit::OnComponentHit);
		
/*************************************
OnComponentHit ���� �̵�
FComponentHitSignature ���� �̵�
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FiveParams
( FComponentHitSignature, UPrimitiveComponent, OnComponentHit, UPrimitiveComponent*, HitComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, FVector, NormalImpulse, const FHitResult&, Hit );
																												
Ȯ��
FVector, NormalImpulse, const FHitResult&, Hit
�浹 ���� ��ֺ���

**************************************/

}


void AC03_OverlapAndHit::OnComponentBeginOverlap
(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult
)
{
	CLog::Print("BeginOverlap :" + OtherActor->GetName());
}

void AC03_OverlapAndHit::OnComponentEndOverlap
(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex
)
{

	//FString str;
	//str = FString::Printf(TEXT("Begin - Other Actor : %s"), *OtherActor->GetName());

	//CLog::Print(str);
	CLog::Print("EndOverlap :" + OtherActor->GetName());

}

void AC03_OverlapAndHit::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, FHitResult const & Hit)
{

	//FString str;
	//str = FString::Printf(TEXT("End - Other Actor : %s"), *OtherActor->GetName());

	//CLog::Print(str);
	CLog::Print("Hit :" + OtherActor->GetName());

}