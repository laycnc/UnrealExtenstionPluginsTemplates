

#pragma once

#include "CoreMinimal.h"
#include "Input/Reply.h"
#include "GraphEditor.h"
#include "UObject/GCObject.h"
#include "EditorUndoClient.h"
#include "Framework/Docking/TabManager.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

class UPLUGIN_NAME;
class SGraphEditor;
class FDocumentTracker;
class FDocumentTabFactory;

class FPLUGIN_NAMEEditor
    : public FWorkflowCentricApplication
    , public FEditorUndoClient
    , public FGCObject
{
public:
	void InitPLUGIN_NAMEEditor(const EToolkitMode::Type        Mode,
	                           const TSharedPtr<IToolkitHost>& InitToolkitHost,
	                           UPLUGIN_NAME*                   InitAsset);

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

	//~ Begin FEditorUndoClient Interface
	virtual void PostUndo(bool bSuccess) override;
	virtual void PostRedo(bool bSuccess) override;
	// End of FEditorUndoClient

	// FGCObject interface
	virtual void    AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override;
	// End of FGCObject interface

	FGraphAppearanceInfo     GetGraphAppearance() const;
	TSharedRef<SGraphEditor> CreateGraphEditorWidget(UEdGraph* InGraph);
	void                     RestoreGraphAsset();
	inline UPLUGIN_NAME*     GetAssetEdited() const
	{
		return AssetEdited;
	}

	void OnGraphEditorFocused(const TSharedRef<SGraphEditor>& InGraphEditor);
	FGraphPanelSelectionSet GetSelectedNodes() const;
	virtual void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection);

public:
	void BindCommands();

private:
	// Delegates for graph editor commands
	void SelectAllNodes();
	bool CanSelectAllNodes() const;
	void DeleteSelectedNodes();
	bool CanDeleteNodes() const;
	void DeleteSelectedDuplicatableNodes();
	void CutSelectedNodes();
	bool CanCutNodes() const;
	void CopySelectedNodes();
	bool CanCopyNodes() const;
	void PasteNodes();
	void PasteNodesHere(const FVector2D& Location);
	bool CanPasteNodes() const;
	void DuplicateNodes();
	bool CanDuplicateNodes() const;

	bool CanCreateComment() const;
	void OnCreateComment();

private:
	/** Currently focused graph */
	TWeakPtr<SGraphEditor> UpdateGraphEdPtr;

	TSharedPtr<FDocumentTracker>  DocumentManager;
	TWeakPtr<FDocumentTabFactory> GraphEditorTabFactoryPtr;
	TSharedPtr<FUICommandList>    GraphEditorCommands;
	UPLUGIN_NAME*                 AssetEdited = nullptr;
};