
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_Mesh.generated.h"

UCLASS()
class CPP_BASIC_API AC02_Mesh : public AActor
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent * Mesh;

public:	
	AC02_Mesh();

protected:
	virtual void BeginPlay() override;

public:	


};
