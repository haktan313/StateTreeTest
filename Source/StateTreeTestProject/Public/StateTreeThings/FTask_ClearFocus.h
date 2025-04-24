#pragma once
#include "AIController.h"
#include "StateTreeTaskBase.h"
#include "FTask_ClearFocus.generated.h"

USTRUCT()
struct FTask_ClearFocusInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<AAIController> AIControllerRef;
};

USTRUCT(meta = (DisplayName = "Clear Focus"))
struct FTask_ClearFocus : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FTask_ClearFocusInstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	FTask_ClearFocus() = default;

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,const FStateTreeTransitionResult& Transition) const override;
	
};
