// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class WootingAnalogInput : ModuleRules
{
	public WootingAnalogInput(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Projects",
                "WootingAnalogSDK",
                "Engine",
                "Slate",
                "InputCore",
                "InputDevice",
            }
            );
    }
}
