//C# ���� �𸮾�5�� ���̽�
using UnrealBuildTool;

public class CPP_Basic : ModuleRules
{
	public CPP_Basic(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        //���� �ϳ��ϳ��� �̸� �����ϵ� ����� ���, �̹� ������ �Ǿ��ٸ�,
        //�ٽ� ���������� �ʴ´�, ���� �ӵ� ���

        PublicIncludePaths.Add(ModuleDirectory);
        //���� ���丮 �߰�,  CPP_Basic ���ذ�θ� ���Խ�Ų��

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
        

	}
}
