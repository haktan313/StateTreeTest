

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestPlayerCharacter.generated.h"

UCLASS()
class STATETREETESTPROJECT_API ATestPlayerCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera")
	TObjectPtr<class USpringArmComponent> SpringArm;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Camera")
	TObjectPtr<class UCameraComponent> Camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<class UHStatHandler> StatHandler;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Magic Attack")
	TObjectPtr<class UAnimMontage> magicAttackMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Magic Attack")
	TSubclassOf<class AProjectileBase> projectileMagicClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Magic Attack")
	TSubclassOf<UUserWidget> healthBarWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Magic Attack")
	float magicAttackAmount;
private:
	ATestPlayerCharacter();

	UFUNCTION()
	void MagicAttackNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	UFUNCTION()
	void OnDeath(UAnimMontage* DeathAnimation);

	FTimerHandle restartGameTimerHandle;
	void RestartGame();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	TObjectPtr<class UAnimInstance> AnimInstance;
	bool bDoOnce = true;
public:
	void MagicAttackStart();
private:
	void MagicSpawn();
	UFUNCTION()
	void ProjectileHit(AActor* HitActor);

};
