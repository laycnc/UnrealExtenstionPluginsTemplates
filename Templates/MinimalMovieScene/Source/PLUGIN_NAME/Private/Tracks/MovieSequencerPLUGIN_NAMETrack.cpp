// Fill out your copyright notice in the Description page of Project Settings.

#include "Tracks/MovieSequencerPLUGIN_NAMETrack.h"
#include "Sections/MovieScenePLUGIN_NAMESection.h"

#define LOCTEXT_NAMESPACE "MovieSequencerPLUGIN_NAMETrack"

UMovieSequencerPLUGIN_NAMETrack::UMovieSequencerPLUGIN_NAMETrack(
    const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

bool UMovieSequencerPLUGIN_NAMETrack::SupportsType(
    TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return false;
}

void UMovieSequencerPLUGIN_NAMETrack::AddSection(UMovieSceneSection& Section) 
{
	Sections.Add(&Section);
}

UMovieSceneSection* UMovieSequencerPLUGIN_NAMETrack::CreateNewSection() 
{
	return NewObject<UMovieScenePLUGIN_NAMESection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSequencerPLUGIN_NAMETrack::GetAllSections() const
{
	return Sections;
}

bool UMovieSequencerPLUGIN_NAMETrack::HasSection(const UMovieSceneSection& Section) const 
{
	return Sections.Contains(&Section);
}

void UMovieSequencerPLUGIN_NAMETrack::RemoveSection(UMovieSceneSection& Section) 
{
	Sections.Remove(&Section);
}

void UMovieSequencerPLUGIN_NAMETrack::RemoveSectionAt(int32 SectionIndex) 
{
	Sections.RemoveAt(SectionIndex);
}

#if WITH_EDITORONLY_DATA

FText UMovieSequencerPLUGIN_NAMETrack::GetDisplayName() const
{
	return LOCTEXT("MovieScenePLUGIN_NAMETrack_DisplayName", "PLUGIN_NAME");
}

#endif

#undef LOCTEXT_NAMESPACE
