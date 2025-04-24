
#include "StateTreeThings/FTask_ClearFocus.h"
#include "AIController.h"
#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FTask_ClearFocus::EnterState(FStateTreeExecutionContext& Context,const FStateTreeTransitionResult& Transition) const
{
	FTask_ClearFocusInstanceData* InstanceData = Context.GetInstanceDataPtr<FTask_ClearFocusInstanceData>(*this);
	if (InstanceData && InstanceData->AIControllerRef)
	{
		InstanceData->AIControllerRef->ClearFocus(EAIFocusPriority::Gameplay);
		return EStateTreeRunStatus::Running;
	}
	return EStateTreeRunStatus::Failed;
}
