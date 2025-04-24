

#include "StateTreeThings/FTask_SetFocusToTargetActor.h"

#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FTask_SetFocusToTargetActor::EnterState(FStateTreeExecutionContext& Context,const FStateTreeTransitionResult& Transition) const
{
	FTask_SetFocusToTargetActorInstanceData* InstanceData = Context.GetInstanceDataPtr<FTask_SetFocusToTargetActorInstanceData>(*this);
	if (InstanceData && InstanceData->AIControllerRef)
	{
		InstanceData->AIControllerRef->SetFocus(InstanceData->TargetActor);
		return EStateTreeRunStatus::Running;
	}
	return EStateTreeRunStatus::Failed;
}
