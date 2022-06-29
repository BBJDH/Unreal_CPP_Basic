
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C01_Property.generated.h"
//	GENERATED_BODY() 를 통해 

UCLASS()
class CPP_BASIC_API AC01_Property : public AActor
{
	GENERATED_BODY()	//직렬화에 필요한 코드들


private:
	UPROPERTY(EditAnywhere)			//공통으로 쓰는데 스폰이후로도 바꿔 쓰고 싶은 것
	int32 A = 10;
	UPROPERTY(EditAnywhere)			//공통으로 쓰는데 스폰이후로도 바꿔 쓰고 싶은 것
	int32 F = 50;
	UPROPERTY(EditInstanceOnly)		//스폰이후에 설정 가능
	int32 B;
	UPROPERTY(EditDefaultsOnly)		//스폰되기 이전 디폴트, 스폰에도 이전
									//해당 클래스 공통으로 쓸값
	int32 C;
	UPROPERTY(VisibleAnywhere, Category = "Property")
	int D = 30;

		

protected:
	//ReadOnly: Get만 생성			EditInstanceOnly: 스폰 이후 편집가능, 카테고리명
	//UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Property")
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Property")
		int Variable = 60;
	
public:	
	AC01_Property();
	void print();

protected:
	virtual void BeginPlay() override;

public:	

};
