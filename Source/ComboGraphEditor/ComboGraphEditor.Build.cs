using UnrealBuildTool;

public class ComboGraphEditor : ModuleRules
{
    public ComboGraphEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core","UnrealEd", "ComboGraphRuntime"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore", "ComboGraphRuntime", "AssetDefinition","ToolMenus","GraphEditor","GameplayAbilities"
            }
        );
    }
}