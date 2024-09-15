// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NeapolitanHotel : ModuleRules
{
	public NeapolitanHotel(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "NeapolitanHotel" });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
