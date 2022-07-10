

#include "03_Collision/C01_ActorOverlab.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC01_ActorOverlab::AC01_ActorOverlab()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);

	CreateTextRender();

//매크로 치환
//CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Root);
//Text->SetRelativeLocation(FVector(0, 0, 100));
//Text->SetRelativeRotation(FRotator(0, 100, 0));
///*************************************

// 에디터 회전 순서 : Roll Pitch Yaw 
// C++	: Pitch(Y) Yaw(Z) Roll(X) 로 다름

//**************************************/
//
//Text->SetRelativeScale3D(FVector(2)); //BP 자물쇠 잠그고 2설정
//Text->TextRenderColor = FColor::Red;
//Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
////가운데 정렬
//Text->Text = FText::FromString(GetName().Replace( TEXT("Default__") , TEXT("") ));
////디폴트로 Default__가 붙으니 없애는 처리, UI에서는 TEXT형을 사용  


	Box->SetRelativeScale3D(FVector(3));  //XYZ 전부 3배
	Box->bHiddenInGame = false;


}

// Called when the game starts or when spawned
void AC01_ActorOverlab::BeginPlay()
{
	Super::BeginPlay();
	

	OnActorBeginOverlap.AddDynamic(this, &AC01_ActorOverlab::OnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AC01_ActorOverlab::OnEndOverlap);
	//함수포인터 연결, 블프와 마찬가지로 시작시 바인딩 해준다
	//AActor에서 퍼블릭으로 델리게이트들이 선언되어 있다

}


/*************************************
 델리게이트는 간편한 문법과 안전성을 갖춰 콜백 함수를 호출하기 위해 고안.
 특징
 - 함수 포인터의 직접 접근이 아닌 대리자를 통한 함수 호출 방식

- 호출할 함수나 이를 포함하는 객체가 없어져도 대리자가 체크해 안전하게 처리할 수 있음.

- 동일한 형을 가진 함수 여러 개를 대리자가 묶어서 관리하고, 필요할 때 동시에 모두 호출하는 것이 가능함.


델리게이트 멀티캐스트
한 이벤트에 여러 함수 포인터를 연결

델리게이트 다이나믹
동적, 블프에서 사용

델리게이트 다이나믹 멀티캐스트
블프의 이벤트 디스패쳐

스파스델리게이트 (엄격한) 추가 정보 명시가 필요하다 
**************************************/

void AC01_ActorOverlab::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FString str;
	str = FString::Printf
	(
		TEXT("Begin - Overlapped : %s, Other: %s"),
		*OverlappedActor->GetName(),
		*OtherActor->GetName()
	);

	CLog::Print(str);
	//CLog::Print(TEXT("Begin Overlap : " + OtherActor->GetName()));
}

void AC01_ActorOverlab::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FString str;
	str = FString::Printf
	(
		TEXT("End - Overlapped : %s, Other: %s"),
		*OverlappedActor->GetName(),
		*OtherActor->GetName()
	);

	CLog::Print(str);
	//CLog::Print(TEXT("End Overlap : " + OtherActor->GetName()), -1, 10, FColor::Red);
}

/*************************************

오버랩 충돌 처리에 필요한 것?
양쪽이 충돌체를 보유하고
제너레이트 오버랩이 켜져있어야 하며
양쪽 프로파일에 겹침이 켜져있어야함

**************************************/