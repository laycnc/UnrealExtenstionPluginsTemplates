// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Input/Reply.h"
#include "UObject/GCObject.h"
#include "Framework/Docking/TabManager.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

class UPLUGIN_NAME;
class FDocumentTracker;
class FDocumentTabFactory;

class FPLUGIN_NAMEEditor
    : public FWorkflowCentricApplication
    , public FGCObject
{
public:
	void InitPLUGIN_NAMEEditor(const EToolkitMode::Type        Mode,
	                        const TSharedPtr<IToolkitHost>& InitToolkitHost,
	                        UPLUGIN_NAME*                  InitAsset);

public:
	FPLUGIN_NAMEEditor();
	~FPLUGIN_NAMEEditor();

	// IToolkit interface
	virtual void RegisterTabSpawners(
	    const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(
	    const TSharedRef<FTabManager>& InTabManager) override;
	// End of IToolkit interface

	// FAssetEditorToolkit interface
	virtual FName        GetToolkitFName() const override;
	virtual FText        GetBaseToolkitName() const override;
	virtual FText        GetToolkitName() const override;
	virtual FText        GetToolkitToolTipText() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString      GetWorldCentricTabPrefix() const override;
	// End of FAssetEditorToolkit interface

	// FGCObject interface
	virtual void    AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override;
	// End of FGCObject interface

	FGraphAppearanceInfo     GetGraphAppearance() const;
	TSharedRef<SGraphEditor> CreateGraphEditorWidget(UEdGraph* InGraph);
	void                     RestoreGraphAsset();
	inline UPLUGIN_NAME*    GetAssetEdited() const
	{
		return AssetEdited;
	}

public:
	void BindCommands();

private:
	TSharedPtr<FDocumentTracker>  DocumentManager;
	TWeakPtr<FDocumentTabFactory> GraphEditorTabFactoryPtr;
	TSharedPtr<FUICommandList>    GraphEditorCommands;
	UPLUGIN_NAME*                AssetEdited = nullptr;
};