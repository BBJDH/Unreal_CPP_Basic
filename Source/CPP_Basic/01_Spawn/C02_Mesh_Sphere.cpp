// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Spawn/C02_Mesh_Sphere.h"
#include "Global.h"


AC02_Mesh_Sphere::AC02_Mesh_Sphere()
{
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/Sphere_Game.Sphere_Game'");
	Mesh->SetStaticMesh(mesh);

}