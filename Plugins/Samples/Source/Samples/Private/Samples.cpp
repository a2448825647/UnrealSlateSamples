// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Samples.h"
#include "SamplesStyle.h"
#include "SamplesCommands.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

static const FName SamplesTabName("Samples");

#define LOCTEXT_NAMESPACE "FSamplesModule"

void FSamplesModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FSamplesStyle::Initialize();
	FSamplesStyle::ReloadTextures();
	//×¢²áÃüÁî
	FSamplesCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);
	//°ó¶¨°´Å¥µã»÷ÊÂ¼þ
	PluginCommands->MapAction(
		FSamplesCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FSamplesModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		//×¢²á²Ëµ¥À¸°´Å¥
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FSamplesModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		//×¢²á¹¤¾ßÀ¸°´Å¥
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FSamplesModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(SamplesTabName, FOnSpawnTab::CreateRaw(this, &FSamplesModule::SpawnSampleTab))
		.SetDisplayName(LOCTEXT("FStandaloneWindowTabTitle", "StandaloneWindow"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FSamplesModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FSamplesStyle::Shutdown();

	FSamplesCommands::Unregister();
}

void FSamplesModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FSamplesModule::PluginButtonClicked()")),
							FText::FromString(TEXT("Samples.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FSamplesModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FSamplesCommands::Get().PluginAction);
}

TSharedRef<SDockTab> FSamplesModule::SpawnSampleTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FStandaloneWindowModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("StandaloneWindow.cpp"))
	);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(WidgetText)
		]
		];
}

void FSamplesModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FSamplesCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSamplesModule, Samples)