


#include "EnemyThings/EnemyBase.h"

#include "HStatHandler.h"
#include "HWidget_BaseStat.h"
#include "ProjectileBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"


AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
	StatHandler = CreateDefaultSubobject<UHStatHandler>(TEXT("StatHandler"));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(RootComponent);
}

void AEnemyBase::OnDeath(UAnimMontage* DeathAnimation)
{
	StatHandler->CanTakeDamage = false;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::Type::PhysicsOnly);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetSimulatePhysics(true);
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	AIController = Cast<ATestAIController>(GetController());
	AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &AEnemyBase::MagicAttackNotifyBegin);
	StatHandler->OnDeath.AddDynamic(this, &AEnemyBase::OnDeath);

	if (healthBarWidgetClass)
	{
		UHWidget_BaseStat* healthBarWidget = CreateWidget<UHWidget_BaseStat>(GetWorld(), healthBarWidgetClass);
		if (healthBarWidget)
		{
			WidgetComponent->SetWidget(healthBarWidget);
			healthBarWidget->StatHandlerObjects.Add("Enemy",StatHandler);
		}
	}
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBase::DoAction(int ActionIndexRef)
{
	switch (ActionIndexRef)
	{
		case 0:
			AnimInstance->Montage_Play(magicAttackMontage, 1.0f);
			break;
	}
}

void AEnemyBase::MagicAttack()
{
	FTransform spawnTransform = GetMesh()->GetSocketTransform("magic_R");
	AProjectileBase* projectileMagic = GetWorld()->SpawnActorDeferred<AProjectileBase>(projectileMagicClass,spawnTransform,this,GetInstigator(),ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (projectileMagic)
	{
		projectileMagic->bHasTarget = true;
		projectileMagic->targetActor = AIController->targetActor;
		projectileMagic->maxSpeed = 1000.0f;
		UGameplayStatics::FinishSpawningActor(projectileMagic, spawnTransform);
		projectileMagic->onProjectileHit.AddDynamic(this, &AEnemyBase::ProjectileHit);
		GetCapsuleComponent()->IgnoreActorWhenMoving(projectileMagic,true);
	}
}

void AEnemyBase::MagicAttackNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (NotifyName == "MagicAttackTrigger")
	{
		MagicAttack();
	}
}

void AEnemyBase::ProjectileHit(AActor* HitActor)
{
	FS_DamageInfo damageInfo;
	damageInfo.AmountOfDamage = magicAttackAmount;
	StatHandler->DamageTo(damageInfo,HitActor);
}



