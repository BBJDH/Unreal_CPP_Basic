

#include "C02_Mesh.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
//#include "Materials/MaterialInstanceConstatnt"
#include "Materials/MaterialInstanceConstant.h"

AC02_Mesh::AC02_Mesh()
{


	/*************************************
	//Root�� StaticMeshComponent ����
	//CreateDefaultSubobject<T> ���� �Ҵ�, UObject*�� ��ȯ
	//Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	//RootComponent = Mesh;
	//���ø����� ����ȭ
	**************************************/
	/*************************************
	�Ҽ� Ŭ����, ������ ������Ʈ ������, ������Ʈ�� �̸����� ������ �����Ҵ� ����
	CreateDefaultSubobject<T>(InName);���
	**************************************/
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh,"Mesh");
	




	/*************************************
	//StaticMesh'/Game/Meshes/Cube.Cube' �� ����� ���۷�������
	// /Game/Meshes/Cube.Cube �����ε� ���������� ��Ȥ �ν� ���� �ʴ´�
	//���� StaticMeshComponent�� ���� ��� StaticMesh �Ҵ�
	//UstaticMesh Ÿ���� FObjectFinder ����ü �ν��Ͻ� ���� (�ش� ���� ���۷����� ������ ����)
	//ConstructorHelpers �� �����ڿ����� ��� ����
	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("StaticMesh'/Game/Meshes/Cube.Cube'"));
	if (mesh.Succeeded())		//�����ߴٸ� true
		Mesh->SetStaticMesh(mesh.Object);
	**************************************/

	/*************************************
	��ȯ�� Ÿ��������, �ش� ���۷���(���)�� ���� ������Ʈ�� ã�Ƽ� ��ȯ
	ConstructorHelpers::FObjectFinder<T> asset(*InPath);
	**************************************/
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/Cube.Cube'");
	Mesh->SetStaticMesh(mesh);
	
	/*************************************
	//TEXT() L"" ���� (ANSI ����(7+1) ĳ����)
	//L" MBCS��� 1����Ʈ�� �� �� �ִ°��� 1����Ʈ�� ĳ����
	//TEXT Unicode��� ��� 2����Ʈ�� ĳ����
	 **************************************/


}

void AC02_Mesh::BeginPlay()
{

	Super::BeginPlay();

	/*************************************
	UObject (�ֻ��� Ŭ����)
	UObject�� ��ӹ�����
	Static TypeID�� ���� (���÷��ǿ� �̿�)
	UClass* StaticClass() -> ���÷��Ǳ�� ����(��ü�� Ÿ���� ������ ���) = UClass* Ÿ��
	//MaterialInstanceConstant'/Game/Materials/M_White_Inst.M_White_Inst'
	**************************************/


	/*************************************
	StaticLoadObject(); ->���ø��� �ƴϰ� UClass* ���ڸ� �޴´�
	//�ʿ��Ҷ� �������� �ҷ����� �ʹٸ� ���
	**************************************/
	


	/*************************************
	Cast<Typename>(); �ش� Ÿ������ ĳ����
	**************************************/
	//UObject* obj = StaticLoadObject
	//(
	//	UMaterialInstanceConstant::StaticClass(),
	//	nullptr,
	//	TEXT("MaterialInstanceConstant'/Game/Materials/M_White_Inst.M_White_Inst'")
	//);
	//UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(obj);
		/*************************************
	Cast<Typename>(); �ش� Ÿ������ ĳ����
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
UMaterialInterface �ֻ��� (UObject�� ��¥ �ֻ���)
UMaterial	�ǽð� �����ϵ� ��
UMaterial InstanceConstant �������̼��� ����/��������
UMaterial InstanceDynamic  ���α׷��� �󿡼� ����/ ����
**************************************/