// 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ComboGraphPropertyEdit.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UComboGraphPropertyEdit : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COMBOGRAPHEDITOR_API IComboGraphPropertyEdit
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UObject* GetUObjectToEditProperty(){return nullptr;}
};
