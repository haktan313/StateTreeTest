
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController.h"
#include "GameplayTagContainer.h"
#include "Perception/AIPerceptionComponent.h"
#include "TestAIController.generated.h"

UENUM(Blueprintable)
enum class E_BehaveState : uint8
{
	Passive UMETA(DisplayName = "Passive"),
	Aggressive UMETA(DisplayName = "Aggressive")
};

UENUM(Blueprintable)
enum class E_SenseType : uint8
{
	See UMETA(DisplayName = "See"),
	Damage UMETA(DisplayName = "Damage")
};

UCLASS()
class STATETREETESTPROJECT_API ATestAIController : public AAIController
{
	GENERATED_BODY()
	
	ATestAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY()
	TObjectPtr<class UAISenseConfig_Sight> SightConfig;
	UPROPERTY()
	TObjectPtr<class UAISenseConfig_Damage> DamageConfig;
	UPROPERTY()
	TObjectPtr<class UCrowdFollowingComponent> CrowdFollowingComponent;
	UPROPERTY()
	TObjectPtr<class UAIPerceptionComponent> AIPerceptionComponent;


	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	void HandleSense(AActor* sensedTargetActor);
	bool PlayerSensed(AActor* sensedActor, E_SenseType senseType);
	FTimerHandle PlayerSensedExpiredTimer;
	void SensedAgeExpired();

	void SetStateAsPassive();
	void SetStateAggressive();
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "AI")
	TObjectPtr<class UStateTreeAIComponent> StateTreeAIComponent;
	UPROPERTY(EditDefaultsOnly, category = "GameplayTags")
	FGameplayTag PassiveTag;
	UPROPERTY(EditDefaultsOnly, category = "GameplayTags")
	FGameplayTag AggressiveTag;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<AActor> targetActor;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector pointOfInterest;
	UPROPERTY(EditDefaultsOnly)
	E_BehaveState BehaveState;
};
