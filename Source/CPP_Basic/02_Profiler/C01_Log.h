
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C01_Log.generated.h"

UCLASS()
class CPP_BASIC_API AC01_Log : public AActor
{
	GENERATED_BODY()
	
public:	
	AC01_Log();

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float TotalTime;

};
