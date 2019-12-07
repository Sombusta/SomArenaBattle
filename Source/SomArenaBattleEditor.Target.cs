// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SomArenaBattleEditorTarget : TargetRules
{
	public SomArenaBattleEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "SomArenaBattle", "SomArenaBattleSetting" } );
	}
}
