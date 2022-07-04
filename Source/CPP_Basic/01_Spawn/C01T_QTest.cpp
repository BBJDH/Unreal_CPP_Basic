// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Spawn/C01T_QTest.h"
#include "Global.h"


// Sets default values
AC01T_QTest::AC01T_QTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = FBox(FVector(-50, -100, -50), FVector(50, 100, 50));
}

// Called when the game starts or when spawned
void AC01T_QTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC01T_QTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//길이가 1인 축 벡터, 회전각
	FQuat fquat(FVector(1,0,0) , GetWorld()->GetTimeSeconds()*500.0f* PI / 180);
	DrawDebugSolidBox(GetWorld(), GetActorLocation()+Box.GetCenter(), Box.GetExtent(), fquat, FColor::Blue);
}

