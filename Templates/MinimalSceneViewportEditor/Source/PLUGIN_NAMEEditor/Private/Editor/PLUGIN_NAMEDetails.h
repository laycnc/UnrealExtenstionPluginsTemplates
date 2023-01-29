#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "IDetailsView.h"

class SPLUGIN_NAMEDetails 
: public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SPLUGIN_NAMEDetails) {}

	/** Optional content to display above the details panel */
	SLATE_ARGUMENT(TSharedPtr<SWidget>, TopContent)

	/** Optional content to display below the details panel */
	SLATE_ARGUMENT(TSharedPtr<SWidget>, BottomContent)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	TSharedPtr<class IDetailsView> DetailsView;
};
