
#include "StateTreeThings/FTask_GetRandomPoint.h"
#include "NavigationSystem.h"
#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FTask_GetRandomPoint::EnterState(FStateTreeExecutionContext& Context,const FStateTreeTransitionResult& Transition) const
{
	FGetRandomPointInstanceData* InstanceData = Context.GetInstanceDataPtr<FGetRandomPointInstanceData>(*this);
	if (InstanceData && InstanceData->Owner)
	{
		FVector origin = InstanceData->Owner->GetActorLocation();
		FNavLocation location;
		UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(InstanceData->Owner->GetWorld());
		if (NavSys && NavSys->GetRandomPointInNavigableRadius(origin, InstanceData->Radius, location))
		{
			InstanceData->RandomPoint = location.Location;
		}
	}
	return EStateTreeRunStatus::Running;
}
