// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Spawn/C02_Mesh_Cone.h"
#include "Global.h"

AC02_Mesh_Cone::AC02_Mesh_Cone()
{
	//:AC02_Mesh() �̴ϼȶ����� ����, �� �θ�����ڰ� �ݵ�� ȣ��� 

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/Cone_Game.Cone_Game'");
	Mesh->SetStaticMesh(mesh);

}