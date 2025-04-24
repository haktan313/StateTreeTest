#pragma once
#include "AIController.h"
#include "StateTreeConditionBase.h"
#include "FCondition_IsInIdealRange.generated.h"

USTRUCT()
struct FCondition_IsInIdealRangeInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<AActor> SelfActor = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<AAIController> AIControllerRef;
	UPROPERTY(EditAnywhere, Category = "Parameter")
	float idealRangeValue;
	UPROPERTY(EditAnywhere, Category="Parameter")
	float AcceptableErrorRadius = 50.0f;
	UPROPERTY(EditAnywhere, Category="Parameter")
	bool bIsInvertResult = false;
	
};

USTRUCT(meta = (DisplayName = "Is In The Ideal Range"))
struct FCondition_IsInIdealRange : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()

	using InstanceDataType = FCondition_IsInIdealRangeInstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return InstanceDataType::StaticStruct(); }
	FCondition_IsInIdealRange() = default;
	
	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;
};
