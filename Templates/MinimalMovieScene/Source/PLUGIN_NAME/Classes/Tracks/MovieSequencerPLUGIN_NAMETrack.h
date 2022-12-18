// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MovieSceneTrack.h"
#include "MovieSequencerPLUGIN_NAMETrack.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UMovieSequencerPLUGIN_NAMETrack : public UMovieSceneTrack
{
	GENERATED_UCLASS_BODY()

public:

    /*
	 * Does this track support this section class type?

	 * @param ClassType The movie scene section class type
	 * @return Whether this track supports this section class type
	 */
	virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;

	/**
	 * Add a section to this track.
	 *
	 * @param Section The section to add.
	 */
	virtual void AddSection(UMovieSceneSection& Section) override;

	/**
	 * Generates a new section suitable for use with this track.
	 *
	 * @return a new section suitable for use with this track.
	 */
	virtual UMovieSceneSection* CreateNewSection() override;
	
	/**
	 * Called when all the sections of the track need to be retrieved.
	 * 
	 * @return List of all the sections in the track.
	 */
	virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;

	/**
	 * Checks to see if the section is in this track.
	 *
	 * @param Section The section to query for.
	 * @return True if the section is in this track.
	 */
	virtual bool HasSection(const UMovieSceneSection& Section) const override;

	/**
	 * Removes a section from this track.
	 *
	 * @param Section The section to remove.
	 */
	virtual void RemoveSection(UMovieSceneSection& Section) override;

	/**
	 * Removes a section from this track at a particular index
	 *
	 * @param SectionIndex The section index to remove.
	 */
	virtual void RemoveSectionAt(int32 SectionIndex) override;

#if WITH_EDITORONLY_DATA

	/**
	 * Get the track's display name.
	 *
	 * @return Display name text.
	 */
	virtual FText GetDisplayName() const override;
#endif

private:
	/** All the sections in this list */
	UPROPERTY()
	TArray<TObjectPtr<UMovieSceneSection>> Sections;
};
