// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Projet_UE4_BachelorsTarget : TargetRules
{
	public Projet_UE4_BachelorsTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Projet_UE4_Bachelors" } );
	}
}
