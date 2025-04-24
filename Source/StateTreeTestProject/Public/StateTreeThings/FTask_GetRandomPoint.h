#pragma once
#include "StateTreeTaskBase.h"
#include "FTask_GetRandomPoint.generated.h"

USTRUCT()
struct FGetRandomPointInstanceData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "Output")
	FVector RandomPoint;
	UPROPERTY(EditAnywhere, Category = "Variables")
	float Radius = 500.0f;
	UPROPERTY(EditAnywhere, Category = "Input")
	AActor* Owner;
};
USTRUCT(meta = (DisplayName = "Get Random Point"))
struct FTask_GetRandomPoint : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FGetRandomPointInstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	FTask_GetRandomPoint() = default;

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,const FStateTreeTransitionResult& Transition) const override;
};
