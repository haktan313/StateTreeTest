#pragma once
#include "StateTreeConditionBase.h"
#include "FCondition_HasPatrolRoute.generated.h"

USTRUCT()
struct FCondition_HasPatrolRouteInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<AActor> Owner;
	UPROPERTY(EditAnywhere)
	bool bInvertResult = false;
	
};

USTRUCT(meta = (DisplayName = "Has Patrol Route"))
struct FCondition_HasPatrolRoute : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()

	using FInstaceDateType = FCondition_HasPatrolRouteInstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstaceDateType::StaticStruct(); }
	FCondition_HasPatrolRoute() = default;

	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;
};
