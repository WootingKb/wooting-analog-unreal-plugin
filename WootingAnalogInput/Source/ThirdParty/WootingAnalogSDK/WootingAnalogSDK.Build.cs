// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class WootingAnalogSDK : ModuleRules
{
	public WootingAnalogSDK(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

        string binDir = Path.Combine(ModuleDirectory, "bin");
        string headersDir = Path.Combine(ModuleDirectory, "headers");
        string LibraryPath = Path.Combine(ModuleDirectory, "lib");

        PublicIncludePaths.Add(headersDir);

        
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
            // Add the import library
            //PublicAdditionalLibraries.Add(Path.Combine(binDir, "Release", "ExampleLibrary.lib"));
            PublicLibraryPaths.Add(Path.Combine(LibraryPath, "win64"));
            PublicAdditionalLibraries.Add("wooting_analog_wrapper.lib");


            /*string dllPath = Path.Combine(binDir, "win64", "wooting_analog_wrapper.dll");

            // Delay-load the DLL, so we can load it from the right place first
            PublicDelayLoadDLLs.Add(dllPath);

			// Ensure that the DLL is staged along with the executable
			RuntimeDependencies.Add(dllPath);*/
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            /*string dllPath = Path.Combine(binDir, "osx64", "libwooting_analog_wrapper.dylib");

            // Delay-load the DLL, so we can load it from the right place first
            PublicDelayLoadDLLs.Add(dllPath);

            // Ensure that the DLL is staged along with the executable
            RuntimeDependencies.Add(dllPath);*/
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            /*string dllPath = Path.Combine(binDir, "linux64", "libwooting_analog_wrapper.so");

            // Delay-load the DLL, so we can load it from the right place first
            PublicDelayLoadDLLs.Add(dllPath);

            // Ensure that the DLL is staged along with the executable
            RuntimeDependencies.Add(dllPath);*/
        }
	}
}
