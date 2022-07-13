

#include "03_Collision/C04_Trigger.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC04_Trigger::AC04_Trigger()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);

	CreateTextRender();

	Box->SetRelativeScale3D(FVector(3));  //XYZ 전부 3배
	Box->bHiddenInGame = false;
}

void AC04_Trigger::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &AC04_Trigger::OnComponentBeginOverlap);
	//FComponentEndOverlapSignature 자료형
	Box->OnComponentEndOverlap.AddDynamic(this, &AC04_Trigger::OnComponentEndOverlap);
}

void AC04_Trigger::OnComponentBeginOverlap
(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult
)
{
	if (OnBoxLightBeginOverlap.IsBound())//해당 델리게이션에 연결된 함수가 있다면
		OnBoxLightBeginOverlap.Execute();

	if (OnBoxLightColorOverlap.IsBound())
	{
		FLinearColor color = FLinearColor::MakeRandomColor();
		FString str = OnBoxLightColorOverlap.Execute(color);
		//Single Bind라면 Execute안에 파라미터갯수 만큼 넣어서 전달

		CLog::Print(str);
	}
}

void AC04_Trigger::OnComponentEndOverlap
(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex
)
{

	if (OnBoxLightEndOverlap.IsBound())
		OnBoxLightEndOverlap.Execute();
}
/*************************************
임의의 델리게이션을 정하여 사용

DECLARE_Delegate 싱글 캐스트 1대1 블프 공개 안됨, 리턴 가능
파라메터 안받으면 위에 그대로 사용 파라메터가 있다면

DECLARE_Delegate_TwoParams(델리게이트 이름(사용자 정의), 파라미터 타입1, 파라미터 타입2)

DECLARE_Delegate Multicast 하나의 델리게이션에 여러개의 함수를 연결 가능 블프 공개 안됨

DECLARE_Delegate Dynamic_DELEGATE		 블프 공개 가능, 리턴 가능
DECLARE_Delegate_Dynamic_DELEGATE_TwoParams
(델리게이트 이름, 파라미터 타입1, 파라미터 이름1, 파라미터 타입2,파라미터 이름2)

DECLARE_Delegate Dynamic Multicast  블프 공개 가능, 리턴 불가

DECLARE_Delegate Dynamic SPARS_DELEGATE		블프가능, 리턴가능(싱글만, 멀티는 여러개에대한 리턴을 판별할 수 없다)
DECLARE_Delegate Dynamic SPARS_DELEGATE_TwoParams(델리게이트 이름, 소속 클래스명(델리게이션이 선언된(소속) 클래스), 변수명,
파라미터 타입1, 파라미터 이름1, 파라미터 타입2,파라미터 이름2))



DECLARE_EVENT 다이나믹 델리게이트와 상당히 유사, 리턴 불가
모든 델리게이트는 전역으로 취급되지만 이벤트는 클래스에 소속하여 클래스 범위 안에서만 사용 가능
//자주 사용하지 않으면 대신에 스파스 델리게이트를 사용함
**************************************/