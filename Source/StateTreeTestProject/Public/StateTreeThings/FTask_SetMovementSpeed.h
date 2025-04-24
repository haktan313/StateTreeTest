#pragma once
#include "StateTreeTaskBase.h"
#include "FTask_SetMovementSpeed.generated.h"

USTRUCT()
struct FTask_SetMovementSpeedInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Parameters")
	float MovementSpeed = 600.0f;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<AActor> Owner;
};

USTRUCT(meta = (DisplayName = "Set Movement Speed"))
struct FTask_SetMovementSpeed : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FTask_SetMovementSpeedInstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	FTask_SetMovementSpeed() = default;

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
};
