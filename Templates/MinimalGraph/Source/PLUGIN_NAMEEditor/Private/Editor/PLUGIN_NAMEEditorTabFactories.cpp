// Copyright Epic Games, Inc. All Rights Reserved.

#include "PLUGIN_NAMEEditorTabFactories.h"

#include "PLUGIN_NAME.h"
#include "PLUGIN_NAMEEditor.h"
#include "PLUGIN_NAMEEditorTabs.h"
#include "Containers/Array.h"
#include "Engine/Blueprint.h"
#include "GraphEditor.h"
#include "Widgets/Docking/SDockTab.h"

class SWidget;
struct FSlateBrush;

#define LOCTEXT_NAMESPACE "PLUGIN_NAMEEditorFactories"

//////////////////////////////////////////////////////////////////////////
// FPLUGIN_NAMEGraphEditorSummoner

FPLUGIN_NAMEGraphEditorSummoner::FPLUGIN_NAMEGraphEditorSummoner(
    TSharedPtr<FPLUGIN_NAMEEditor> InEditorPtr,
    FOnCreateGraphEditorWidget  CreateGraphEditorWidgetCallback)
	: FDocumentTabFactoryForObjects<UEdGraph>(FPLUGIN_NAMEEditorTabs::GraphEditorID, InEditorPtr)
	, EditorPtr(InEditorPtr)
	, OnCreateGraphEditorWidget(CreateGraphEditorWidgetCallback)
{
}

void FPLUGIN_NAMEGraphEditorSummoner::OnTabActivated(TSharedPtr<SDockTab> Tab) const
{
	check(EditorPtr.IsValid());
	TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(Tab->GetContent());
	//EditorPtr.Pin()->OnGraphEditorFocused(GraphEditor);
}

void FPLUGIN_NAMEGraphEditorSummoner::OnTabRefreshed(TSharedPtr<SDockTab> Tab) const
{
	TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(Tab->GetContent());
	GraphEditor->NotifyGraphChanged();
}

TAttribute<FText> FPLUGIN_NAMEGraphEditorSummoner::ConstructTabNameForObject(UEdGraph* DocumentID) const
{
	return TAttribute<FText>( FText::FromString( DocumentID->GetName() ) );
}

TSharedRef<SWidget> FPLUGIN_NAMEGraphEditorSummoner::CreateTabBodyForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const
{
	return OnCreateGraphEditorWidget.Execute(DocumentID);
}

const FSlateBrush* FPLUGIN_NAMEGraphEditorSummoner::GetTabIconForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const
{
	return FAppStyle::Get().GetBrush("BTEditor.BehaviorTree");
}

void FPLUGIN_NAMEGraphEditorSummoner::SaveState(TSharedPtr<SDockTab> Tab, TSharedPtr<FTabPayload> Payload) const
{
	check(EditorPtr.IsValid());
	check(EditorPtr.Pin()->GetAssetEdited());

	TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(Tab->GetContent());

	FVector2D ViewLocation;
	float ZoomAmount;
	GraphEditor->GetViewLocation(ViewLocation, ZoomAmount);

	UEdGraph* Graph = FTabPayload_UObject::CastChecked<UEdGraph>(Payload);
	EditorPtr.Pin()->GetAssetEdited()->LastEditedDocuments.Add(FEditedDocumentInfo(Graph, ViewLocation, ZoomAmount));
}

#undef LOCTEXT_NAMESPACE
