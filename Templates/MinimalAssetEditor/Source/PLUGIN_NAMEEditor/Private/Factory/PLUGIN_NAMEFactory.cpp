// Fill out your copyright notice in the Description page of Project Settings.

#include "Factory/PLUGIN_NAMEFactory.h"
#include "PLUGIN_NAME.h"

UPLUGIN_NAMEFactory::UPLUGIN_NAMEFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew     = true;
	bEditAfterNew  = true;
	SupportedClass = UPLUGIN_NAME::StaticClass();
}

// UFactory interface

UObject* UPLUGIN_NAMEFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UPLUGIN_NAME* NewAsset = NewObject<UPLUGIN_NAME>(InParent, Class, Name, Flags | RF_Transactional);
	return NewAsset;
}

// End of UFactory interface