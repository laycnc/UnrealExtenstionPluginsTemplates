

#include "TrackEditors/PLUGIN_NAMETrackEditor.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Styling/AppStyle.h"
#include "LevelSequence.h"

#include "Tracks/MovieSequencerPLUGIN_NAMETrack.h"

class ISequencerTrackEditor;
struct FSlateBrush;

#define LOCTEXT_NAMESPACE "FPLUGIN_NAMETrackEditor"


/* FPLUGIN_NAMETrackEditor static functions
 *****************************************************************************/

TSharedRef<ISequencerTrackEditor> FPLUGIN_NAMETrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer)
{
	return MakeShareable(new FPLUGIN_NAMETrackEditor(InSequencer));
}


/* FPLUGIN_NAMETrackEditor structors
 *****************************************************************************/

FPLUGIN_NAMETrackEditor::FPLUGIN_NAMETrackEditor(TSharedRef<ISequencer> InSequencer)
    : FMovieSceneTrackEditor(InSequencer)
{ }

/* ISequencerTrackEditor interface
 *****************************************************************************/

TSharedRef<ISequencerSection> FPLUGIN_NAMETrackEditor::MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding)
{
    // Implementation is required to customize the appearance of the section
	return FMovieSceneTrackEditor::MakeSectionInterface(
	    SectionObject, Track, ObjectBinding);
}

void FPLUGIN_NAMETrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddPLUGIN_NAMETrack", "PLUGIN_NAME Track"),
		LOCTEXT("AddPLUGIN_NAMETrackTooltip", "Adds a new track that controls the PLUGIN_NAME of the sequence."),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FPLUGIN_NAMETrackEditor::HandleAddPLUGIN_NAMETrackMenuEntryExecute),
			FCanExecuteAction::CreateRaw(this, &FPLUGIN_NAMETrackEditor::HandleAddPLUGIN_NAMETrackMenuEntryCanExecute)
		)
	);
}

bool FPLUGIN_NAMETrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const
{
	if ( InSequence->GetClass() == ULevelSequence::StaticClass() )
	{
		return true;
    }
	return false;
}

bool FPLUGIN_NAMETrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const
{
	return (Type == UMovieSequencerPLUGIN_NAMETrack::StaticClass());
}

const FSlateBrush* FPLUGIN_NAMETrackEditor::GetIconBrush() const
{
	return FMovieSceneTrackEditor::GetIconBrush();
}


/* FPLUGIN_NAMETrackEditor callbacks
 *****************************************************************************/

void FPLUGIN_NAMETrackEditor::HandleAddPLUGIN_NAMETrackMenuEntryExecute()
{
	UMovieScene* MovieScene = GetFocusedMovieScene();

	if (MovieScene == nullptr)
	{
		return;
	}

	if (MovieScene->IsReadOnly())
	{
		return;
	}

	if ( nullptr != MovieScene->FindMasterTrack<UMovieSequencerPLUGIN_NAMETrack>()  )
	{
		return;
	}

	const FScopedTransaction Transaction(LOCTEXT("AddPLUGIN_NAMETrack_Transaction", "Add PLUGIN_NAME Track"));

	MovieScene->Modify();

	const auto Result = FindOrCreateMasterTrack<UMovieSequencerPLUGIN_NAMETrack>();

    if ( Result.bWasCreated )
	{
		UMovieSceneTrack* NewTrack = Result.Track;
		check(NewTrack);

		UMovieSceneSection* NewSection = NewTrack->CreateNewSection();
		check(NewSection);

		NewTrack->Modify();
		NewTrack->AddSection(*NewSection);

		if ( GetSequencer().IsValid() )
		{
			GetSequencer()->OnAddTrack(NewTrack, FGuid());
		}
	}
}

bool FPLUGIN_NAMETrackEditor::HandleAddPLUGIN_NAMETrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();
	
	return (
	    (FocusedMovieScene != nullptr) &&
	    (FocusedMovieScene->FindMasterTrack<UMovieSequencerPLUGIN_NAMETrack>() == nullptr));
}

#undef LOCTEXT_NAMESPACE
