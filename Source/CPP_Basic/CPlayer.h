
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


private:
	UPROPERTY(VisibleDefaultsOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
	class UCameraComponent* Camera;

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


private:
	void OnRun();
	void OffRun();

public:
	UFUNCTION(BlueprintCallable, Category = "Color")
	void ChangeColor(FLinearColor InColor);
	//BlueprintCallable 블프에서 호출가능 블프 함수들이 이걸로 정의됨
private:
	class UMaterialInstanceDynamic* Materials[2];
	
};
