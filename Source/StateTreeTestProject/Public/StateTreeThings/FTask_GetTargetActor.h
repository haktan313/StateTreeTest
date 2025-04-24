#pragma once
#include "StateTreeTaskBase.h"
#include "FTask_GetTargetActor.generated.h"

USTRUCT()
struct FTask_GetTargetActorInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Output")
	TObjectPtr<AActor> TargetActor;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class AAIController> AIController ;
};

USTRUCT(meta = (DisplayName = "Get Target Actor"))
struct FTask_GetTargetActor : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FTask_GetTargetActorInstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	FTask_GetTargetActor() = default;

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,const FStateTreeTransitionResult& Transition) const override;
};
