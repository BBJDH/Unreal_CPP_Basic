

#include "03_Collision/C01_ActorOverlab.h"
#include "Global.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC01_ActorOverlab::AC01_ActorOverlab()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box",Root);
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text",Root);


	Box->SetRelativeScale3D(FVector(3));  //XYZ 전부 3배
	Box->bHiddenInGame = false;

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 100, 0));


	/*************************************
	 에디터 회전 순서 : Roll Pitch Yaw 
	 C++	: Pitch(Y) Yaw(Z) Roll(X) 로 다름

	**************************************/
	
	Text->SetRelativeScale3D(FVector(2)); //BP 자물쇠 잠그고 2설정
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	//가운데 정렬
	Text->Text = FText::FromString(GetName().Replace(TEXT("Default__"), TEXT("")));
	//디폴트로 Default__가 붙으니 없애는 처리

}

// Called when the game starts or when spawned
void AC01_ActorOverlab::BeginPlay()
{
	Super::BeginPlay();
	

	OnActorBeginOverlap.AddDynamic(this, &AC01_ActorOverlab::OnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AC01_ActorOverlab::OnEndOverlap);
	//함수포인터 연결

}


/*************************************
 델리게이트는 간편한 문법과 안전성을 갖춰 콜백 함수를 호출하기 위해 고안.
 특징
 - 함수 포인터의 직접 접근이 아닌 대리자를 통한 함수 호출 방식

- 호출할 함수나 이를 포함하는 객체가 없어져도 대리자가 체크해 안전하게 처리할 수 있음.

- 동일한 형을 가진 함수 여러 개를 대리자가 묶어서 관리하고, 필요할 때 동시에 모두 호출하는 것이 가능함.

**************************************/

void AC01_ActorOverlab::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	CLog::Print(TEXT("Begin Overlap : " + OtherActor->GetName()));
}

void AC01_ActorOverlab::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	CLog::Print(TEXT("End Overlap : " + OtherActor->GetName()), -1, 10, FColor::Red);
}