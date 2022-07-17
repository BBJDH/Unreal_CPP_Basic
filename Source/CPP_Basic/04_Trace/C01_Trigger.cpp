

#include "04_Trace/C01_Trigger.h"
#include "Global.h"
#include "C01_SphereTrace.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC01_Trigger::AC01_Trigger()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);

	CreateTextRender();

	Box->SetRelativeScale3D(FVector(3));
	Box->bHiddenInGame = false;
}

void AC01_Trigger::BeginPlay()
{
	Super::BeginPlay();

	AC01_SphereTrace* trace = CHelpers::FindActor<AC01_SphereTrace>(GetWorld());
	//월드에서 SphereTrace 인스턴스를 찾음
	
	CheckNull(trace);

	OnActorBeginOverlap.AddDynamic(trace, &AC01_SphereTrace::OnActorBeginOverlap);
	//부모인 Actor가 가지고 있는 오버랩 델리게이션에 함수를 결합

}

