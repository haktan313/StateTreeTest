#pragma once
#include "StateTreeTaskBase.h"
#include "FTask_FindNextPatrolNode.generated.h"

USTRUCT()
struct FTask_FindNextPatrolNodeInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Output")
	FVector PatrolPointLocation;
	UPROPERTY(EditAnywhere, Category = "Input")
	AActor* Owner;
};

USTRUCT(meta = (DisplayName = "Find Next Patrol Node"))
struct FTask_FindNextPatrolNode : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FTask_FindNextPatrolNodeInstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	FTask_FindNextPatrolNode() = default;

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
};
