

#include "CPlayer.h"
#include "Global.h"
#include "CAnimInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"  //�Է� ������Ʈ

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	//��� Actor�� �Ҽӵ���/��𿡼� ��������(InActor), �Ҵ���� ������Ʈ ������, �����̸�, �޶���� �θ�(���� ����)	
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetCapsuleComponent());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	bUseControllerRotationYaw = false;
	//��Ʈ�ѷ�(���� ī�޶�) Yaw ȸ�� ����
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//�ڵ������� ĳ������ �̵������� �����̴� ���⿡ ���߾� ȸ�� ����


	GetCharacterMovement()->MaxWalkSpeed = 400;

	//������ �޽� SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'
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
	SpringArm->bEnableCameraLag = true;		//ī�޶� �ε巴�� ���������
	SpringArm->bDoCollisionTest = false;	//�������Ͽ� �ɸ��� ���ư�����
	SpringArm->bUsePawnControlRotation = true;	//Pawn���� ȸ������


}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	TArray<UMaterialInterface *> materials = GetMesh()->GetMaterials();
	
	for (int i = 0; i < materials.Num(); i++)
	{
		Materials[i] = UMaterialInstanceDynamic::Create(materials[i], this);
		GetMesh()->SetMaterial(i, Materials[i]);
	}
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

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	//���� ������ �Է¿��� ���ǵ� �̸��� �̺�Ʈ ���ε�
	//����ȭ ���� �ʾƵ� �ȴ� �Լ� ������ ���ε�
	//BindAxis�� ���ڷ� float �ϳ��� �޾ƾ� �Ѵ�


	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::HorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::VerticalLook);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ACPlayer::OnRun);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ACPlayer::OffRun);

}

void ACPlayer::OnMoveForward(float InAxisValue)
{
	//�����̸� InAxisValue 1, �Ĺ��̸� -1

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	//��Ʈ�ѷ��� �ٶ󺸴� ���� ���� Yaw ���� ������
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();//������ ���������� ��ֶ���� �ʿ�
	//rotator(ī�޶� �ٶ󺸴� Yaw)�� Q(X,Y,Z) , GetForwardVector()�� �����Ͽ� ���̸� ���λ���

	AddMovementInput(direction, InAxisValue);
}
void ACPlayer::OnMoveRight(float InAxisValue)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();//������ ���������� ��ֶ���� �ʿ�


	AddMovementInput(direction, InAxisValue);
}

void ACPlayer::HorizontalLook(float InAxisValue)
{
	AddControllerYawInput(InAxisValue);

}
void ACPlayer::VerticalLook(float InAxisValue)
{
	AddControllerPitchInput(InAxisValue);

}
void ACPlayer::OnRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 600;
}
void ACPlayer::OffRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 400;

}

void ACPlayer::ChangeColor(FLinearColor InColor)
{
	for (UMaterialInstanceDynamic* material : Materials)
		material->SetVectorParameterValue("BodyColor", InColor);
}//�̷������� ������ ����ϵ��� ���� ����Ѵ�