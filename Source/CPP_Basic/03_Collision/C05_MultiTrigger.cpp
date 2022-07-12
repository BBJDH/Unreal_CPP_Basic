

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