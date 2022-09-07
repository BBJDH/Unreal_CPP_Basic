
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "05_IK/CFeetComponent.h"
#include "CAnimInstance.generated.h"

/**
 #include "05_IK/CFeetComponent.h"
 포인터가 아니라면 헤더 선언을 해주자

 */
UCLASS()
class CPP_BASIC_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	bool bfeet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	FFeetData FeetData;



//public:
//	void BlueprintBeginPlay_Implementation();
//블프 콜이라서 무시됨
public:
	void NativeBeginPlay()override;
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;
	//언리얼 에서는 가상함수의 오버라이드 명시가 의무사항이다
private:
	class ACharacter* OwnerCharacter;
	
};
