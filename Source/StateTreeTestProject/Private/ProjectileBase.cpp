


#include "ProjectileBase.h"

#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "PlayerThings/TestPlayerCharacter.h"


AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("projectileMovement"));
	
	boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("boxCollision"));
	boxCollision->SetupAttachment(RootComponent);

	particleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("particleSystem"));
	particleSystem->SetupAttachment(boxCollision);
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	boxCollision->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	boxCollision->IgnoreActorWhenMoving(GetOwner(),true);
	if(bHasTarget)
	{
		RotateToTarget();
	}
	else
	{
		RotateThroughForward();
	}
}

void AProjectileBase::RotateToTarget()
{
	FVector actorLocation = GetActorLocation();
	FVector targetLocation = targetActor->GetActorLocation() + targetActor->GetVelocity() * 0.35f;//we are trying to predict the target location
	FVector direction = UKismetMathLibrary::GetDirectionUnitVector(actorLocation,targetLocation);
	projectileMovement->Velocity = direction * maxSpeed;
}

void AProjectileBase::RotateThroughForward()
{
	//FVector cameraForward = player->Camera->GetForwardVector(); //with that you can throw projectile through where camera is looking
	FVector forward = player->GetActorForwardVector(); //with that you can throw projectile through where player is looking
	UKismetMathLibrary::Normal(forward);
	projectileMovement->Velocity = forward * maxSpeed;
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit)
{
	onProjectileHit.Broadcast(OtherActor);
	
	UGameplayStatics::SpawnEmitterAtLocation(
	GetWorld(),
	hittedParticleSystem,
	Hit.ImpactPoint,
	FRotator::ZeroRotator,
	 FVector(1.0f,1.0f,1.0f),
	 true,EPSCPoolMethod::None, 
	 true);
	
	Destroy();
}

