// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealPortfolio : ModuleRules
{
	public UnrealPortfolio(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "UnrealPortfolio" });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput" ,"UMG", "Sockets", "Networking" });
        
        PrivateDependencyModuleNames.AddRange(new string[] {
            "GameFeatures",
            "GameplayAbilities",
            "GameplayTasks",
            "GameplayTags"
        });

    }
}
