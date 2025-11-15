// 


#include "ComboGraphLibrary.h"

#include "ComboGraphAsset.h"
#include "Edge/ComboGraphEdge.h"
#include "Node/ComboGraphNode.h"

bool UComboGraphLibrary::TryEvaluateEdgeFunc(const FComboGraphResolveContext& Context,FGuid EdgeId)
{
	auto Edge = Context.GraphAsset->GetEdge(EdgeId);
	if (!Edge)
	{
		UE_LOG(LogTemp,Error,TEXT("%s: Edge %s not found"),TEXT(__FUNCTION__),*EdgeId.ToString());
		return false;
	}
	TSubclassOf<UComboEdgeFunctionLibrary> FunctionClass = Edge->FunctionClass;
	FName FunctionName = Edge->FunctionName;
	if (!FunctionClass)
	{
		UE_LOG(LogTemp,Error,TEXT("%s: Edge FunctionClass Is nullptr"),TEXT(__FUNCTION__));
		return false;
	}
	if (FunctionName.IsNone())
	{
		UE_LOG(LogTemp,Error,TEXT("%s: Edge FunctionName Is None"),TEXT(__FUNCTION__));
		return false;
	}
	UFunction* Func = FunctionClass->FindFunctionByName(FunctionName);
	if (!Func)
	{
		UE_LOG(LogTemp,Error,TEXT("%s: Function %s not found"),TEXT(__FUNCTION__),*FunctionName.ToString());
		return false;
	}
	UObject* CDO = FunctionClass->GetDefaultObject();
	struct FDynamicInvokeParams
	{
		FComboGraphResolveContext Context;
		bool ReturnValue;
	};

	FDynamicInvokeParams Params;
	Params.Context = Context;

	CDO->ProcessEvent(Func, &Params);

	return Params.ReturnValue;
}

FComboGraphResolveResult UComboGraphLibrary::TryResolveNextNode(const FComboGraphResolveContext& Context)
{
	FComboGraphResolveResult Result;
	if (!Context.GraphAsset)
	{
		UE_LOG(LogTemp,Error,TEXT("%s: GraphAsset is nullptr"),TEXT(__FUNCTION__));
		return Result;
	}
	auto CurrentNode = Context.GraphAsset->GetNode(Context.CurrentNodeId);
	if (!CurrentNode)
	{
		UE_LOG(LogTemp,Error,TEXT("%s: CurrentNode Is nullptr"),TEXT(__FUNCTION__));
		return Result;
	}
	auto TryResolveAnyNode = [&Result,&Context]()->float
	{
		float MinSort = INT_MAX;
		for (FGuid& AnyNodeId : Context.GraphAsset->AnyNodeIds)
		{
			auto AnyNode = Context.GraphAsset->GetNode(AnyNodeId);
			if (!AnyNode)
			{
				UE_LOG(LogTemp,Error,TEXT("%s: AnyNode %s Is nullptr"),TEXT(__FUNCTION__),*AnyNodeId.ToString());
				continue;
			}
			for (auto& Pair : AnyNode->Output)
			{
				bool CanTransitionTo = TryEvaluateEdgeFunc(Context,Pair.Key);
				if (CanTransitionTo)
				{
					MinSort = FMath::Min(MinSort,Pair.Value->Sort);
					Result.NextNodeId = Pair.Value->Id;
				}
			}
		}
		return MinSort;
	};
	float AnyNodeSort = TryResolveAnyNode();
	
	if (CurrentNode->IsLeafNode())
	{
		return Result;
	}
	for (auto& Pair : CurrentNode->Output)
	{
		bool CanTransitionTo = TryEvaluateEdgeFunc(Context,Pair.Key);
		if (CanTransitionTo)
		{
			if (Pair.Value->Sort < AnyNodeSort)
			{
				Result.NextNodeId = Pair.Value->Id;
			}
		}
	}
	return Result;
	
}
