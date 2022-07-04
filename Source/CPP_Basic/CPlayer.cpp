

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

	//��� Actor�� �Ҽӵ���/��𿡼� ��������(InActor), �Ҵ���� ������Ʈ ������, �����̸�, �޶���� �θ�(���� ����)	
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetCapsuleComponent());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	GetCharacterMovement()->MaxWalkSpeed = 400;

	//SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'
	USkeletalMesh* mesh = nullptr;

	//���۷����� ���� ��������
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);
	//��ġ ����, �Ʒ��� 90, 
	GetMesh()->SetRelativeLocation(FVector(0,0,-90));
	GetMesh()->SetRelativeRotation(FRotator(0,-90,0)); //Pitch Yaw Roll
	/*************************************
	 ������ ȸ�� ���� : Roll Pitch Yaw
	 C++	: Pitch(Y) Yaw(Z) Roll(X) �� �ٸ�

	**************************************/

	//AnimBlueprint'/Game/ABP_CPlayer.ABP_CPlayer'
	//Ŭ������ �θ����� TSubclassOf
	//Mesh�� AnimInstance �Ҵ�
	TSubclassOf<UCAnimInstance> animInstance;
	CHelpers::GetClass<UCAnimInstance>(&animInstance,"AnimBlueprint'/Game/ABP_CPlayer.ABP_CPlayer_C'");
	GetMesh()->SetAnimClass(animInstance);

	SpringArm->SetRelativeLocation(FVector(0,0,60));
	SpringArm->SocketOffset = FVector(0, 60, 0);
	SpringArm->TargetArmLength = 200;	//���� 200
	SpringArm->bDoCollisionTest = false;	//�������Ͽ� �ɸ��� ���ư�����
	SpringArm->bUsePawnControlRotation = true;	//Pawn���� ȸ������
	SpringArm->bEnableCameraLag = true;		//ī�޶� �ε巴�� ���������


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
���� �Է��� ��Ʈ�ѷ����� ó���ؾ� ��
Character Ŭ�������� ó���Ѵٸ�
SetupPlayerInputComponent�� ���

Actor���� �Է��� �����ؼ� �����̰� �ϰ�ʹٸ�
GetInputComponent�� ���� ����

**************************************/

}

