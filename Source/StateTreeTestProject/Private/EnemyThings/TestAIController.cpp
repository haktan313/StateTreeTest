


#include "EnemyThings/TestAIController.h"

#include "Components/StateTreeAIComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"


ATestAIController::ATestAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	StateTreeAIComponent = CreateDefaultSubobject<UStateTreeAIComponent>(TEXT("StateTreeAIComponent"));
	CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent());
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SetPerceptionComponent(*AIPerceptionComponent);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 2200.f;
	SightConfig->LoseSightRadius = 2500.f;
	SightConfig->PeripheralVisionAngleDegrees = 90.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->SetMaxAge(5.f);

	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageConfig"));
	DamageConfig->SetMaxAge(3.f);

	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->ConfigureSense(*DamageConfig);
	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ATestAIController::OnPerceptionUpdated);
}

void ATestAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	SetStateAsPassive();
}

void ATestAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for(AActor* sensedActor : UpdatedActors)
	{
		if (sensedActor->ActorHasTag("Player"))
		{
			HandleSense(sensedActor);
		}
	}
}

void ATestAIController::HandleSense(AActor* sensedTargetActor)
{
	if(PlayerSensed(sensedTargetActor, E_SenseType::See))
	{
		targetActor = sensedTargetActor;
		if (BehaveState == E_BehaveState::Passive)
		{
			SetStateAggressive();
		}
	}
	else if(PlayerSensed(sensedTargetActor, E_SenseType::Damage))
	{
		pointOfInterest = sensedTargetActor->GetActorLocation();
		targetActor = sensedTargetActor;
		if (BehaveState == E_BehaveState::Passive)
		{
			SetStateAggressive();
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(PlayerSensedExpiredTimer, this, &ATestAIController::SensedAgeExpired, 2.f, false);
		}
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(PlayerSensedExpiredTimer, this, &ATestAIController::SensedAgeExpired, 5.f, false);
	}
}

bool ATestAIController::PlayerSensed(AActor* sensedActor, E_SenseType senseType)
{
	if (!sensedActor)
	{
		return false;
	}
	FActorPerceptionBlueprintInfo perceptionInfo;
	AIPerceptionComponent->GetActorsPerception(sensedActor, perceptionInfo);
	
	for(const auto& stimulus : perceptionInfo.LastSensedStimuli)
	{
		FAISenseID senseID;
		switch (senseType)
		{
		case E_SenseType::See:senseID = UAISense::GetSenseID<UAISenseConfig_Sight>();break;
		case E_SenseType::Damage:senseID = UAISense::GetSenseID<UAISenseConfig_Damage>(); break;
		}
		if(stimulus.IsValid() || stimulus.Type == senseID)
		{
			if (stimulus.WasSuccessfullySensed())
			{
				if (GetWorld()->GetTimerManager().IsTimerActive(PlayerSensedExpiredTimer))
				{
					GetWorld()->GetTimerManager().ClearTimer(PlayerSensedExpiredTimer);
				}
				pointOfInterest = stimulus.StimulusLocation;
				return true;
			}
		}
	}
	return false;
}

void ATestAIController::SensedAgeExpired()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Sensed Age Expired"));
	SetStateAsPassive();
}


//----------------------------------------------------------------------------


void ATestAIController::SetStateAsPassive()
{
	BehaveState = E_BehaveState::Passive;
	StateTreeAIComponent->SendStateTreeEvent(PassiveTag, nullptr, TEXT(""));
}

void ATestAIController::SetStateAggressive()
{
	BehaveState = E_BehaveState::Aggressive;
	StateTreeAIComponent->SendStateTreeEvent(AggressiveTag, nullptr, TEXT(""));
}
