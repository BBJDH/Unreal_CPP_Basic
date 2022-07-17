#include "C02_Cylinder.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

AC02_Cylinder::AC02_Cylinder()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", Root);

	CreateTextRender();

	UStaticMesh* mesh;
	//StaticMesh'/Game/Meshes/Cylinder_Game.Cylinder_Game'
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/Cylinder_Game.Cylinder_Game'");
	Mesh->SetStaticMesh(mesh);
	Mesh->SetRelativeScale3D(FVector(1, 1, 2.5f));


}

void AC02_Cylinder::BeginPlay()
{
	Super::BeginPlay();

}
