
#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "HEnvQueryContext_TargetActor.generated.h"


UCLASS()
class STATETREETESTPROJECT_API UHEnvQueryContext_TargetActor : public UEnvQueryContext
{
	GENERATED_BODY()

	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
	
};
