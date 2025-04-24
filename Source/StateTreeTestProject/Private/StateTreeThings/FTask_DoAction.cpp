
#include "StateTreeThings/FTask_DoAction.h"
#include "StateTreeExecutionContext.h"
#include "EnemyThings/EnemyBase.h"

EStateTreeRunStatus FTask_DoAction::EnterState(FStateTreeExecutionContext& Context,const FStateTreeTransitionResult& Transition) const
{
	FTask_DoActionInstanceDate* InstanceData = Context.GetInstanceDataPtr<FTask_DoActionInstanceDate>(*this);
	if (InstanceData && InstanceData->Owner)
	{
		AEnemyBase* Enemy = Cast<AEnemyBase>(InstanceData->Owner);
		if (Enemy)
		{
			Enemy->DoAction(InstanceData->ActionIndex);
		}
		return EStateTreeRunStatus::Running;
	}
	return EStateTreeRunStatus::Failed;
}
