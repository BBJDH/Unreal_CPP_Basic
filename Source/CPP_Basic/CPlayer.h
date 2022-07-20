
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

UCLASS()
class CPP_BASIC_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

	/*************************************
	Character 클래스
	Mesh Component
	Arrow Component 포함되어 있음
	**************************************/

		//UPROPERTY(EditDefaultsOnly, Category = "Rifle")
		//TSubclassOf<class ACRifle> RifleClass;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float ZoomSpeed = 1000;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	FVector2D ZoomRange = FVector2D(0, 500);

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float ZoomInterpSpeed = 5;



	UPROPERTY(VisibleDefaultsOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly)
		class UCFeetComponent* Feet;

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	void OnMoveForward(float InAxisValue);
	void OnMoveRight(float InAxisValue);

	void HorizontalLook(float InAxisValue);
	void VerticalLook(float InAxisValue);

	void OnZoom(float InAxisValue);

private:
	void OnRun();
	void OffRun();

public:
	UFUNCTION(BlueprintCallable, Category = "Color")
	void ChangeColor(FLinearColor InColor);
	//BlueprintCallable 블프에서 호출가능 블프 함수들이 이걸로 정의됨
private:
	TArray<class UMaterialInstanceDynamic*> Materials;
	//class UMaterialInstanceDynamic* Materials[2];

private:
	//class ACRifle* Rifle;

private:
	float Zooming;
};
