
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C03_Spawner.generated.h"

UCLASS()
class CPP_BASIC_API AC03_Spawner : public AActor
{
	GENERATED_BODY()
	
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
		TSubclassOf<class AC02_Mesh> SpawnClasses[3];

	UPROPERTY(EditDefaultsOnly, Category = "Padding")
	float Padding = 350;
public:	
	AC03_Spawner();

protected:
	virtual void BeginPlay() override;

public:	

};
