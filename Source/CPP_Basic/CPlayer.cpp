

#include "CPlayer.h"
#include "Global.h"
#include "CAnimInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "components/SkeletalMeshComponent.h"
#include "components/CapsuleComponent.h"
#include "components/InputComponent.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	//어느 Actor에 소속될지/어디에서 생성될지(InActor), 할당받을 컴포넌트 포인터, 생성이름, 달라붙을 부모(유무 포함)	
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetCapsuleComponent());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	GetCharacterMovement()->MaxWalkSpeed = 400;

	//SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'
	USkeletalMesh* mesh = nullptr;

	//레퍼런스로 에셋 가져오기
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);
	//위치 조정, 아래로 90, 
	GetMesh()->SetRelativeLocation(FVector(0,0,-90));
	GetMesh()->SetRelativeRotation(FRotator(0,-90,0)); //Pitch Yaw Roll
	/*************************************
	 에디터 회전 순서 : Roll Pitch Yaw
	 C++	: Pitch(Y) Yaw(Z) Roll(X) 로 다름

	**************************************/

	//AnimBlueprint'/Game/ABP_CPlayer.ABP_CPlayer'
	//클래스를 부를때는 TSubclassOf
	//Mesh에 AnimInstance 할당
	TSubclassOf<UCAnimInstance> animInstance;
	CHelpers::GetClass<UCAnimInstance>(&animInstance,"AnimBlueprint'/Game/ABP_CPlayer.ABP_CPlayer_C'");
	GetMesh()->SetAnimClass(animInstance);

	SpringArm->SetRelativeLocation(FVector(0,0,60));
	SpringArm->SocketOffset = FVector(0, 60, 0);
	SpringArm->TargetArmLength = 200;	//길이 200
	SpringArm->bDoCollisionTest = false;	//스프링암에 걸리면 돌아가도록
	SpringArm->bUsePawnControlRotation = true;	//Pawn따라서 회전할지
	SpringArm->bEnableCameraLag = true;		//카메라 부드럽게 따라오도록


}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
/*************************************
본래 입력은 컨트롤러에서 처리해야 함
Character 클래스에서 처리한다면
SetupPlayerInputComponent를 사용

Actor에게 입력을 전달해서 움직이게 하고싶다면
GetInputComponent를 만들어서 전달

**************************************/

}

