


#include "EnemyThings/HEnvQueryContext_TargetActor.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnemyThings/TestAIController.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UHEnvQueryContext_TargetActor::ProvideContext(FEnvQueryInstance& QueryInstance,FEnvQueryContextData& ContextData) const
{
	UObject* querierObject = QueryInstance.Owner.Get();
	if(!querierObject)
	{
		return;
	}
	AActor* querierActor = Cast<AActor>(querierObject);
	if(!querierActor)
	{
		return;
	}
	AAIController* aiController = UAIBlueprintHelperLibrary::GetAIController(querierActor);
	if(!aiController)
	{
		return;
	}
	ATestAIController* hAIController = Cast<ATestAIController>(aiController);
	if(!hAIController)
	{
		return;
	}
	AActor* targetActor = hAIController->targetActor;
	if(targetActor)
	{
		UEnvQueryItemType_Actor::SetContextHelper(ContextData,targetActor);
	}
}
