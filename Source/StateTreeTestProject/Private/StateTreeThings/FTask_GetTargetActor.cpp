
#include "StateTreeThings/FTask_GetTargetActor.h"
#include "StateTreeExecutionContext.h"
#include "EnemyThings/TestAIController.h"

EStateTreeRunStatus FTask_GetTargetActor::EnterState(FStateTreeExecutionContext& Context,const FStateTreeTransitionResult& Transition) const
{
	FTask_GetTargetActorInstanceData* InstanceData = Context.GetInstanceDataPtr<FTask_GetTargetActorInstanceData>(*this);
	if (InstanceData && InstanceData->AIController)
	{
		ATestAIController* AIController = Cast<ATestAIController>(InstanceData->AIController);
		if (AIController && AIController->targetActor)
		{
			InstanceData->TargetActor = AIController->targetActor;
		}
	}
	return EStateTreeRunStatus::Running;
}
