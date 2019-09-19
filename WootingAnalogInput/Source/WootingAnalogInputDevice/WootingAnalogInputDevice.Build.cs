// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class WootingAnalogInputDevice : ModuleRules
{
	public WootingAnalogInputDevice(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));
        PrivateIncludePathModuleNames.AddRange(new string[]
         {
            "WootingAnalogInput"
        });

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Projects",
                "WootingAnalogSDK",
                "WootingAnalogInput",
                "Engine",
                "Slate",
                "InputCore",
                "InputDevice",
            }
            );
    }
}
