#pragma once
#include "AIController.h"
#include "StateTreeTaskBase.h"
#include "FTask_SetFocusToTargetActor.generated.h"

USTRUCT()
struct FTask_SetFocusToTargetActorInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<AActor> TargetActor = nullptr;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<AAIController> AIControllerRef;
};

USTRUCT(meta = (DisplayName = "Set Focus To Target Actor"))
struct FTask_SetFocusToTargetActor : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FTask_SetFocusToTargetActorInstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	FTask_SetFocusToTargetActor() = default;

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,const FStateTreeTransitionResult& Transition) const override;
};
