

#include "StateTreeThings/FTask_FindNextPatrolNode.h"

#include "StateTreeExecutionContext.h"
#include "EnemyThings/EnemyBase.h"
#include "EnemyThings/HPatrolSpline.h"

EStateTreeRunStatus FTask_FindNextPatrolNode::EnterState(FStateTreeExecutionContext& Context,const FStateTreeTransitionResult& Transition) const
{
	FTask_FindNextPatrolNodeInstanceData* InstanceData = Context.GetInstanceDataPtr<FTask_FindNextPatrolNodeInstanceData>(*this);
	if (InstanceData && InstanceData->Owner)
	{
		AEnemyBase* EnemyBase = Cast<AEnemyBase>(InstanceData->Owner);
		if (EnemyBase && EnemyBase->PatrolSpline)
		{
			InstanceData->PatrolPointLocation = EnemyBase->PatrolSpline->GetPatrolRouteLocation(EnemyBase);
			EnemyBase->PatrolSpline->PatrolRouteIndex(EnemyBase);
		}
	}
	return EStateTreeRunStatus::Running;
}
