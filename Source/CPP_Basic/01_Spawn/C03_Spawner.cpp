

#include "C03_Spawner.h"
#include "Global.h"
#include "C02_Mesh.h"

AC03_Spawner::AC03_Spawner()
{

}

void AC03_Spawner::BeginPlay()
{
	Super::BeginPlay();
	

	for (int32 i = 0; i < 3; i++)
	{
		FTransform transform;
		//transform 单捞磐 积己

		FVector location = GetActorLocation();
		transform.SetLocation(FVector(location.X, location.Y + i * Padding, location.Z));

		GetWorld()->SpawnActor<AC02_Mesh>(SpawnClasses[i], transform);
		//World惑俊 Actor甫 积己
	}
	
}

