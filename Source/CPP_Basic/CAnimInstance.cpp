

#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"



void UCAnimInstance::NativeBeginPlay() 
{
	//__super, 부모객체의 함수 콜
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	//캐스팅 실패시 nullptr

	//CLog::Print("Begin Play",0,10,FColor::Red);

}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//CLog::Print("Update",1);
	//ABP를 열기만 해도 Update가 출력된다
	//프리뷰 액터에서 콜, 할당된 애니메이션에서 콜

	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();
	CLog::Print("Update",0, 10, FColor::Green);


}

void UCAnimInstance::BlueprintBeginPlay_Implementation()
{
	CLog::Print("Blueprint_BeginPlay");
	//애니메이션 Beginplay시 콜
}