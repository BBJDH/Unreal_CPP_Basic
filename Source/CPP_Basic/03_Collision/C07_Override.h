#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C07_Override.generated.h"

UCLASS()
class CPP_BASIC_API AC07_Override : public AActor
{
	GENERATED_BODY()

	private:
	UPROPERTY(VisibleDefaultsOnly)
	class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
	class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
	class UTextRenderComponent* Text;

public:
	AC07_Override();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	//자식들에서 접근할 함수 정의
	//ImplementableEvent
	UFUNCTION(BlueprintImplementableEvent)
	void ChangeColorRed();
	//자직에서 재정의 가능함 뒤에_Implementation 붙여서 정의
	//블프에서 이벤트로 나타남

	UFUNCTION(BlueprintNativeEvent)
	void ChangeColorWhite(); //선언부가 없어도됨 정의를 자식에서 써도됨 가상함수
	void ChangeColorWhite_Implementation();  //실제 정의는 이렇게 붙여야 함 이줄은 없어도됨
	//하지만 지우면 인텔리센스 지원이 안됨

};
