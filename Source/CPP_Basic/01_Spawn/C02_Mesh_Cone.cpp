// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Spawn/C02_Mesh_Cone.h"
#include "Global.h"

AC02_Mesh_Cone::AC02_Mesh_Cone()
{
	//:AC02_Mesh() 이니셜라이즈 생략, 즉 부모생성자가 반드시 호출됨 

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/Cone_Game.Cone_Game'");
	Mesh->SetStaticMesh(mesh);

}