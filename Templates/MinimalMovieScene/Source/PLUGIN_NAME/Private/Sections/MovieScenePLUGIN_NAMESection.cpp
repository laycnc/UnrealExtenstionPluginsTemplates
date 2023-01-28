// Fill out your copyright notice in the Description page of Project Settings.


#include "Sections/MovieScenePLUGIN_NAMESection.h"

UMovieScenePLUGIN_NAMESection::UMovieScenePLUGIN_NAMESection(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
	SetRange(TRange<FFrameNumber>::All());
}