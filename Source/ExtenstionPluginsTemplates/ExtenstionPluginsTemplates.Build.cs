// Copyright(c) 2023 laycnc

using UnrealBuildTool;

public class ExtenstionPluginsTemplates : ModuleRules
{
	public ExtenstionPluginsTemplates(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "PluginBrowser",
                "UnrealEd",
                "DeveloperSettings",
                "Projects"
				// ... add private dependencies that you statically link with here ...	
			}
			);
	}
}
