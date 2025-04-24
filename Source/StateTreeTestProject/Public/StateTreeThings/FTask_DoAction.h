#pragma once
#include "StateTreeTaskBase.h"
#include "FTask_DoAction.generated.h"

USTRUCT()
struct FTask_DoActionInstanceDate
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class AActor> Owner;
	UPROPERTY(EditDefaultsOnly, Category = "Parameter")
	int ActionIndex;
};

USTRUCT(meta = (DisplayName = "Do Action"))
struct FTask_DoAction : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FTask_DoActionInstanceDate;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	FTask_DoAction() = default;

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,const FStateTreeTransitionResult& Transition) const override;
};
