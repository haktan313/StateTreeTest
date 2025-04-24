

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProjectileHit, AActor*, hitActor);

UCLASS()
class STATETREETESTPROJECT_API AProjectileBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category= Collision, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> boxCollision;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category= Collision, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UProjectileMovementComponent> projectileMovement;

	AProjectileBase();
	
	virtual void BeginPlay() override;

	void RotateToTarget();
	
	void RotateThroughForward();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	
	UPROPERTY(BlueprintAssignable)
	FOnProjectileHit onProjectileHit;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "MagicAttack", meta = (ExposeOnSpawn = "true"))
	TObjectPtr<UParticleSystemComponent> particleSystem;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category= "MagicAttack")
	TObjectPtr<UParticleSystem> hittedParticleSystem;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "MagicAttack", meta = (ExposeOnSpawn = "true"))
	TObjectPtr<AActor> targetActor;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "MagicAttack", meta = (ExposeOnSpawn = "true"))
	TObjectPtr<class ATestPlayerCharacter> player;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "MagicAttack", meta = (ExposeOnSpawn = "true"))
	bool bHasTarget;//if enemy using this it must be true because enemy has target and it is player
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "MagicAttack", meta = (ExposeOnSpawn = "true"))
	float maxSpeed;
	
};
