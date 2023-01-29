// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "PLUGIN_NAMEFactory.generated.h"

/**
 * 
 */
UCLASS()
class UPLUGIN_NAMEFactory : public UFactory
{
	GENERATED_UCLASS_BODY()

public:

	// UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	// End of UFactory interface
};
