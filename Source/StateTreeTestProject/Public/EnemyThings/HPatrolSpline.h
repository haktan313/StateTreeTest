
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HPatrolSpline.generated.h"

USTRUCT(BlueprintType)
struct FS_PatrolData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PatrolData")
	int currentPointIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PatrolData",meta=(ClampMin="1",ClampMax="1"))
	int direction;
	
};

UCLASS()
class STATETREETESTPROJECT_API AHPatrolSpline : public AActor
{
	GENERATED_BODY()

	AHPatrolSpline();
public:
	void PatrolRouteIndex(AActor* RequestedBy);
	
	FVector GetPatrolRouteLocation(AActor* RequestedBy);
private:

	UPROPERTY(EditAnywhere)
	TMap<AActor*, FS_PatrolData> PatrolDataMap;

	UPROPERTY()
	class USplineComponent* SplineComponent;



};
