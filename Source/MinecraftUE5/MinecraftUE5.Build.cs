// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MinecraftUE5 : ModuleRules
{
	public MinecraftUE5(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
