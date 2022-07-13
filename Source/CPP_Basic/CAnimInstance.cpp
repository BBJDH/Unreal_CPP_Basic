

#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"



void UCAnimInstance::NativeBeginPlay() 
{
	//__super, �θ�ü�� �Լ� ��
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	//ĳ���� ���н� nullptr

	//CLog::Print("Begin Play",0,10,FColor::Red);

}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//CLog::Print("Update",1);
	//ABP�� ���⸸ �ص� Update�� ��µȴ�
	//������ ���Ϳ��� ��, �Ҵ�� �ִϸ��̼ǿ��� ��

	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();
	CLog::Print("Update",0, 10, FColor::Green);


}

void UCAnimInstance::BlueprintBeginPlay_Implementation()
{
	CLog::Print("Blueprint_BeginPlay");
	//�ִϸ��̼� Beginplay�� ��
}