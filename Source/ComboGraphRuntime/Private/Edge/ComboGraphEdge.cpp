// 


#include "Edge/ComboGraphEdge.h"

UComboGraphAsset* UComboGraphEdge::GetGraph() const
{
	return GraphAsset;
}
#if WITH_EDITOR
TArray<FName> UComboGraphEdge::GetEdgeFunctionList()
{
	TArray<FName> OutNames;
	if (!FunctionClass)
	{
		return OutNames;
	}
		
	for (TFieldIterator<UFunction> FuncIt(FunctionClass, EFieldIteratorFlags::ExcludeSuper); FuncIt; ++FuncIt)
	{
		UFunction* Func = *FuncIt;
		
		if (Func->HasAllFunctionFlags(FUNC_BlueprintCallable))
		{
			OutNames.Add(Func->GetFName());
		}
	}
	
	return OutNames;
}

void UComboGraphEdge::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropName = PropertyChangedEvent.GetPropertyName();
	if (PropName == GET_MEMBER_NAME_CHECKED(UComboGraphEdge, FunctionClass))
	{
		FunctionName = NAME_None;
	}
}
#endif
