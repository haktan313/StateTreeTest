

#pragma once

#include "CoreMinimal.h"
#include "TestAIController.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class STATETREETESTPROJECT_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()
	
	AEnemyBase();

	UFUNCTION()
	void OnDeath(UAnimMontage* DeathAnimation);
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	TObjectPtr<ATestAIController> AIController;
	UPROPERTY()
	TObjectPtr<UAnimInstance> AnimInstance;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UHStatHandler> StatHandler;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<class AHPatrolSpline> PatrolSpline;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<class AProjectileBase> projectileMagicClass;
	UPROPERTY(EditAnywhere, Category = "AI")
	float magicAttackAmount;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UAnimMontage> magicAttackMontage;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<class UWidgetComponent> WidgetComponent;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<UUserWidget> healthBarWidgetClass;

	void DoAction(int ActionIndexRef);
	
	void MagicAttack();

	UFUNCTION()
	void ProjectileHit(AActor* HitActor);

	UFUNCTION()
	void MagicAttackNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

};
