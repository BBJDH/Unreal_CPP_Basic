

#include "C02_Mesh.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
//#include "Materials/MaterialInstanceConstatnt"
#include "Materials/MaterialInstanceConstant.h"

AC02_Mesh::AC02_Mesh()
{


	/*************************************
	//Root에 StaticMeshComponent 생성
	//CreateDefaultSubobject<T> 동적 할당, UObject*를 반환
	//Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	//RootComponent = Mesh;
	//템플릿으로 간소화
	**************************************/
	/*************************************
	소속 클래스, 생성될 컴포넌트 포인터, 컴포넌트의 이름으로 구성된 동적할당 생성
	CreateDefaultSubobject<T>(InName);사용
	**************************************/
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh,"Mesh");
	




	/*************************************
	//StaticMesh'/Game/Meshes/Cube.Cube' 의 복사된 레퍼런스에서
	// /Game/Meshes/Cube.Cube 만으로도 가능하지만 간혹 인식 되지 않는다
	//만든 StaticMeshComponent에 지정 경로 StaticMesh 할당
	//UstaticMesh 타입의 FObjectFinder 구조체 인스턴스 생성 (해당 파일 레퍼런스를 값으로 받음)
	//ConstructorHelpers 는 생성자에서만 사용 가능
	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("StaticMesh'/Game/Meshes/Cube.Cube'"));
	if (mesh.Succeeded())		//성공했다면 true
		Mesh->SetStaticMesh(mesh.Object);
	**************************************/

	/*************************************
	반환될 타입포인터, 해당 레퍼런스(경로)를 통해 오브젝트를 찾아서 반환
	ConstructorHelpers::FObjectFinder<T> asset(*InPath);
	**************************************/
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/Cube.Cube'");
	Mesh->SetStaticMesh(mesh);
	
	/*************************************
	//TEXT() L"" 차이 (ANSI 문자(7+1) 캐스팅)
	//L" MBCS방식 1바이트로 쓸 수 있는것은 1바이트로 캐스팅
	//TEXT Unicode방식 모두 2바이트로 캐스팅
	 **************************************/


}

void AC02_Mesh::BeginPlay()
{

	Super::BeginPlay();

	/*************************************
	UObject (최상위 클래스)
	UObject를 상속받으면
	Static TypeID가 생성 (리플렉션에 이용)
	UClass* StaticClass() -> 리플렉션기능 제공(객체의 타입을 변수로 사용) = UClass* 타입
	//MaterialInstanceConstant'/Game/Materials/M_White_Inst.M_White_Inst'
	**************************************/


	/*************************************
	StaticLoadObject(); ->템플릿이 아니고 UClass* 인자를 받는다
	//필요할때 동적으로 불러오고 싶다면 사용
	**************************************/
	


	/*************************************
	Cast<Typename>(); 해당 타입으로 캐스팅
	**************************************/
	//UObject* obj = StaticLoadObject
	//(
	//	UMaterialInstanceConstant::StaticClass(),
	//	nullptr,
	//	TEXT("MaterialInstanceConstant'/Game/Materials/M_White_Inst.M_White_Inst'")
	//);
	//UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(obj);
		/*************************************
	Cast<Typename>(); 해당 타입으로 캐스팅
	**************************************/
	UMaterialInstanceConstant* material = nullptr;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>
		(
			&material,
			"MaterialInstanceConstant'/Game/Materials/M_White_Inst.M_White_Inst'"
		);
	
}


/*************************************
Material
UMaterialInterface 최상위 (UObject가 진짜 최상위)
UMaterial	실시간 컴파일될 것
UMaterial InstanceConstant 에디터이서만 생성/편집가능
UMaterial InstanceDynamic  프로그래밍 상에서 생성/ 편집
**************************************/