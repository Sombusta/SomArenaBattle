// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SomArenaBattleTarget : TargetRules
{
	public SomArenaBattleTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "SomArenaBattle", "SomArenaBattleSetting" } );
	}
}
