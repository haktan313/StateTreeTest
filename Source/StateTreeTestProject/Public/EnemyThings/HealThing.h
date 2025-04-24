

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealThing.generated.h"

UCLASS()
class STATETREETESTPROJECT_API AHealThing : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<class UStaticMeshComponent> HealThingMesh;
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<class UCapsuleComponent> HealThingCollision;
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<class UHStatHandler> StatHandler;
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<class USceneComponent> Root;

	AHealThing();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditAnywhere)
	float healAmount = 35.f;

};
