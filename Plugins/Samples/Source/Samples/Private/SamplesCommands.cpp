// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SamplesCommands.h"

#define LOCTEXT_NAMESPACE "FSamplesModule"

void FSamplesCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "Samples", "Execute Samples action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
