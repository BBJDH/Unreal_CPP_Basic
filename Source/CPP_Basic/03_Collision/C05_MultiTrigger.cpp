

#include "03_Collision/C05_MultiTrigger.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC05_MultiTrigger::AC05_MultiTrigger()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);

	CreateTextRender();

	Box->SetRelativeScale3D(FVector(3));  //XYZ 전부 3배
	Box->bHiddenInGame = false;
}

void AC05_MultiTrigger::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &AC05_MultiTrigger::OnComponentBeginOverlap);
}


void AC05_MultiTrigger::OnComponentBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult
)
{
	CLog::Print("Success!");

	//false시 함수 종료 
	CheckFalse(OnMultiLightOverlap.IsBound());//해당 델리게이션에 연결된 함수가 있다면
	//값 할당
	int32 index = UKismetMathLibrary::RandomIntegerInRange(0, 2);
	FLinearColor color = FLinearColor::MakeRandomColor();
	
	OnMultiLightOverlap.Broadcast(index, color);
	//파라미터 전파 -> 바인딩된 함수에 index, color를 파라미터로 호출한다
}

/*************************************
EVENT 블프 공개 안됨
EVENT는 클래스에 소속되어 사용된다는 것을 주의하자
델리게이션과 이벤트 차이
연결 하는것은 외부에서 가능하지만(Bind())
Isbound()
Broadcast()
Clear()
이 세가지는 클래스 내부에서만 콜 가능하다

델리게이션과 다르게
Class A
{
	DECLARE_EVENT
	이렇게 나간다
Isbound()
Broadcast()
Clear()
이 클래스 안에서만 가능!

클래스 한정을 시키려고 EVENT를 써왔으나
SPARSE가 생기면서 SPARSE를 채용한다
}


델리게이션 사용시 
해당 클래스 안에서만 사용하도록 권고, 선생님 코드 참고
**************************************/