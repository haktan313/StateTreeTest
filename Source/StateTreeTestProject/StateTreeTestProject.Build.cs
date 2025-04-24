// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class StateTreeTestProject : ModuleRules
{
	public StateTreeTestProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput","StateTreeModule","GameplayStateTreeModule","AIModule","NavigationSystem","UMG","GameplayTags","HStatsManager" });
	}
}
