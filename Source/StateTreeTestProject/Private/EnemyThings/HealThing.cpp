
#include "EnemyThings/HealThing.h"
#include "HStatHandler.h"
#include "Components/CapsuleComponent.h"

AHealThing::AHealThing()
{

	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	HealThingCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HealThingCollision"));
	HealThingCollision->SetupAttachment(Root);
	HealThingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HealThingMesh"));
	HealThingMesh->SetupAttachment(HealThingCollision);
	StatHandler = CreateDefaultSubobject<UHStatHandler>(TEXT("StatHandler"));
}

void AHealThing::BeginPlay()
{
	Super::BeginPlay();
	HealThingCollision->OnComponentBeginOverlap.AddDynamic(this, &AHealThing::OnOverlapBegin);
}

void AHealThing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealThing::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Enemy"))
	{
		StatHandler->HealTo(healAmount,OtherActor);
		Destroy();
	}
}

