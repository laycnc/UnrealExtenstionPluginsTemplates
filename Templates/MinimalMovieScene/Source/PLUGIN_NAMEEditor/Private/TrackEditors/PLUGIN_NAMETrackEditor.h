

#pragma once

#include "CoreMinimal.h"
#include "Templates/SharedPointer.h"
#include "Templates/SubclassOf.h"
#include "MovieSceneTrackEditor.h"

class FMenuBuilder;
class ISequencer;
class ISequencerSection;
class ISequencerTrackEditor;
class UMovieSceneSection;
class UMovieSceneSequence;
class UMovieSceneTrack;
struct FGuid;
struct FSlateBrush;

/**
* A property track editor for PLUGIN_NAME control.
*/
class FPLUGIN_NAMETrackEditor
	: public FMovieSceneTrackEditor
{
public:

	/**
	 * Factory function to create an instance of this class (called by a sequencer).
	 *
	 * @param InSequencer The sequencer instance to be used by this tool.
	 * @return The new instance of this class.
	 */
	static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InSequencer);

public:

	/**
	 * Creates and initializes a new instance.
	 *
	 * @param InSequencer The sequencer instance to be used by this tool.
	 */
	FPLUGIN_NAMETrackEditor(TSharedRef<ISequencer> InSequencer);	

public:

	// ISequencerTrackEditor interface

	virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;
	virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;
	virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;
	virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;
	virtual const FSlateBrush* GetIconBrush() const override;

private:

	/** Callback for executing the "Add PLUGIN_NAME Track" menu entry. */
	void HandleAddPLUGIN_NAMETrackMenuEntryExecute();
	bool HandleAddPLUGIN_NAMETrackMenuEntryCanExecute() const;
};
