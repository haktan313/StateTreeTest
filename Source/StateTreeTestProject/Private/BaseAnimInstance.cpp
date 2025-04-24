


#include "BaseAnimInstance.h"

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (character)
	{
		FVector velocity = character->GetVelocity();
		speed = velocity.Size();

		FRotator rotation = character->GetActorRotation();//GetControlRotation();
		direction = CalculateDirection(velocity, rotation);
	}
}

void UBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	character = TryGetPawnOwner();
}
