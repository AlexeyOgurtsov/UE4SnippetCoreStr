// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjCoreStrEditorTarget : TargetRules
{
	public ProjCoreStrEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		ExtraModuleNames.AddRange( new string[] { "ProjCoreStr" } );

		bUseUnityBuild = false;
		bUsePCHFiles = false;
	}
}
