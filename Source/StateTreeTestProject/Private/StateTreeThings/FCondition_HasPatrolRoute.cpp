
#include "StateTreeThings/FCondition_HasPatrolRoute.h"
#include "StateTreeExecutionContext.h"
#include "EnemyThings/EnemyBase.h"

bool FCondition_HasPatrolRoute::TestCondition(FStateTreeExecutionContext& Context) const
{
	FCondition_HasPatrolRouteInstanceData* InstanceData = Context.GetInstanceDataPtr<FCondition_HasPatrolRouteInstanceData>(*this);
	if (InstanceData && InstanceData->Owner)
	{
		AEnemyBase* Enemy = Cast<AEnemyBase>(InstanceData->Owner.Get());
		if (Enemy && Enemy->PatrolSpline != nullptr)
		{
			return !InstanceData->bInvertResult;
		}
	}
	return InstanceData ? InstanceData->bInvertResult : false;
}
