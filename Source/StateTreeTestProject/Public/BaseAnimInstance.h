

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"


UCLASS()
class STATETREETESTPROJECT_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeInitializeAnimation() override;
	
	UPROPERTY()
	TObjectPtr<AActor> character;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float speed;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float direction;
	
};
