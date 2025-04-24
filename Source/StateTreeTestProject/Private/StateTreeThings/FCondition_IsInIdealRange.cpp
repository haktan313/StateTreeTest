
#include "StateTreeThings/FCondition_IsInIdealRange.h"

#include "StateTreeExecutionContext.h"
#include "EnemyThings/TestAIController.h"

bool FCondition_IsInIdealRange::TestCondition(FStateTreeExecutionContext& Context) const
{
	FCondition_IsInIdealRangeInstanceData& InstanceData = Context.GetInstanceData<FCondition_IsInIdealRangeInstanceData>(*this);
	if (InstanceData.SelfActor && InstanceData.AIControllerRef)
	{
		ATestAIController* AIControllerr = Cast<ATestAIController>(InstanceData.AIControllerRef);
		if (!AIControllerr || AIControllerr->targetActor == nullptr)
		{
			return false;
		}
		float distance = FVector::Dist(AIControllerr->targetActor->GetActorLocation(), InstanceData.SelfActor->GetActorLocation());
		distance = distance - InstanceData.AcceptableErrorRadius;
		if (InstanceData.bIsInvertResult)
		{
			return distance > InstanceData.idealRangeValue;
		}
		return distance <= InstanceData.idealRangeValue;
	}
	return false;
}
