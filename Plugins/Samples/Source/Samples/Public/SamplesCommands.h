// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "SamplesStyle.h"

class FSamplesCommands : public TCommands<FSamplesCommands>
{
public:

	FSamplesCommands()
		: TCommands<FSamplesCommands>(TEXT("Samples"), NSLOCTEXT("Contexts", "Samples", "Samples Plugin"), NAME_None, FSamplesStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
