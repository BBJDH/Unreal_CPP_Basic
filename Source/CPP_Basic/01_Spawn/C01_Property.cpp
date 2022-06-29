#include "C01_Property.h"
//같은 경로에 있으므로 상위 경로 필요 없음

AC01_Property::AC01_Property()
	:B(20)
{
	C = 30;
}

void AC01_Property::BeginPlay()
{

	Super::BeginPlay();
	//BP의 BeginPlay가 먼저


	FString str;
	str.Append(GetActorLabel());
	//GetActorLavel() Actor의 이름을 보여줌

	str.Append(" / A: ");
	str.Append(FString::FromInt(A));

	str.Append(" / B: ");
	str.Append(FString::FromInt(B));

	str.Append(" / C: ");
	str.Append(FString::FromInt(C));

	GLog->Log(*str);


}




/*************************************
직렬화(Serialization)

- 정보를 다른 환경에서 불러와 동일한 상황으로 만드는 기법
	->	객체와 속성 정보를 안전하게 보관하고 로딩
	->	바이너리 데이터와 객체 데이터 사이의 인코딩과 디코딩
	->	데이터를 스트링, 혹은 일차원 배열 형태로 변환해서 외부로 전송
		-> 그래픽스에서 렌더링에 필요한 정보를 GPU의 스트림 배열에 넣는 것과 동일

- 객체를 다른 환경들과 호환되도록 바이트 배열로 변환


- 언리얼 직렬화의 동작은 2단계로 구분
	-> 객체와 속성 정보를 저장, 보관 -> 패키징
	-> 데이터가 필요한 플랫폼에서 패키징 데이터를 로딩


	UObject (최상위 클래스)
	  /\
AActor  UActorComponent

UObject로부터 상속 받는 클래스에는 공통점이 있다
.generated.h 라는  include 문이 추가
UCLASS()
이 사이에는 어떠한 코드도 들어가면 안된다
GENERATED_BODY()


에셋과 패키지
 - 에디터에는 직렬화된 데이터만 나갈 수 있다(에디터에서 접근 할 수 있다)
 - 콘텐츠 브라우저의 모든 애셋은 패키징을 통해 저장된 애셋
	-> 프로그래밍 관점에서 패키징 된것이 *.uasset 파일을 의미

-  애셋은 파일에 시리얼라이즈하여 저장된 UObject
	-> UPackage 클래스를 사용하여 저장

**************************************/