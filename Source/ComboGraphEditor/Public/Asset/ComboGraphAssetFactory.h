#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "ComboGraphAssetFactory.generated.h"

UCLASS()
class COMBOGRAPHEDITOR_API UComboGraphAssetFactory : public UFactory
{
	GENERATED_BODY()

public:
	UComboGraphAssetFactory();

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name,
		EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual uint32 GetMenuCategories() const override;
};