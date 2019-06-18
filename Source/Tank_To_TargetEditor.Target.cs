// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Tank_To_TargetEditorTarget : TargetRules
{
	public Tank_To_TargetEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Tank_To_Target" } );
	}
}
