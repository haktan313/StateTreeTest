
#include "StateTreeThings/FTask_SetMovementSpeed.h"

#include "StateTreeExecutionContext.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

EStateTreeRunStatus FTask_SetMovementSpeed::EnterState(FStateTreeExecutionContext& Context,const FStateTreeTransitionResult& Transition) const
{
	FTask_SetMovementSpeedInstanceData* InstanceData = Context.GetInstanceDataPtr<FTask_SetMovementSpeedInstanceData>(*this);
	if (InstanceData && InstanceData->Owner)
	{
		ACharacter* Character = Cast<ACharacter>(InstanceData->Owner);
		if (Character)
		{
			Character->GetCharacterMovement()->MaxWalkSpeed = InstanceData->MovementSpeed;
			return EStateTreeRunStatus::Running;
		}
	}
	return EStateTreeRunStatus::Failed;
}
