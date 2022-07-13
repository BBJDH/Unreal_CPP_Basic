

#include "CPlayer.h"
#include "Global.h"
#include "CAnimInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"  //입력 컴포넌트

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	//어느 Actor에 소속될지/어디에서 생성될지(InActor), 할당받을 컴포넌트 포인터, 생성이름, 달라붙을 부모(유무 포함)	
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetCapsuleComponent());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	bUseControllerRotationYaw = false;
	//컨트롤러(하위 카메라) Yaw 회전 끄기
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//자동적으로 캐릭터의 이동방향을 움직이는 방향에 맞추어 회전 보간


	GetCharacterMovement()->MaxWalkSpeed = 400;

	//가져올 메시 SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'
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
	SpringArm->bEnableCameraLag = true;		//카메라 부드럽게 따라오도록
	SpringArm->bDoCollisionTest = false;	//스프링암에 걸리면 돌아가도록
	SpringArm->bUsePawnControlRotation = true;	//Pawn따라서 회전할지


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
본래 입력은 컨트롤러에서 처리해야 함
Character 클래스에서 처리한다면
SetupPlayerInputComponent를 사용

Actor에게 입력을 전달해서 움직이게 하고싶다면
GetInputComponent를 만들어서 전달

**************************************/

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	//엔진 세팅의 입력에서 정의된 이름의 이벤트 바인딩
	//직렬화 하지 않아도 된다 함수 포인터 바인딩
	//BindAxis는 인자로 float 하나를 받아야 한다


	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::HorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::VerticalLook);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ACPlayer::OnRun);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ACPlayer::OffRun);

}

void ACPlayer::OnMoveForward(float InAxisValue)
{
	//전방이면 InAxisValue 1, 후방이면 -1

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	//컨트롤러가 바라보는 전방 벡터 Yaw 값을 가져옴
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();//포워드 벡터이지만 노멀라이즈가 필요
	//rotator(카메라가 바라보는 Yaw)의 Q(X,Y,Z) , GetForwardVector()는 외적하여 길이를 늘인상태

	AddMovementInput(direction, InAxisValue);
}
void ACPlayer::OnMoveRight(float InAxisValue)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();//포워드 벡터이지만 노멀라이즈가 필요


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
}//이런식으로 블프와 통신하도록 많이 사용한다