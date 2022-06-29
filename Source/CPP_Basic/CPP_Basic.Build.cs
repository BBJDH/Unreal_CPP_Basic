//C# 파일 언리얼5는 파이썬
using UnrealBuildTool;

public class CPP_Basic : ModuleRules
{
	public CPP_Basic(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        //파일 하나하나를 미리 컴파일된 헤더로 취급, 이미 컴파일 되었다면,
        //다시 컴파일하지 않는다, 빌드 속도 상승

        PublicIncludePaths.Add(ModuleDirectory);
        //포함 디렉토리 추가,  CPP_Basic 기준경로를 포함시킨다

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
        

	}
}
