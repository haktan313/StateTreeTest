
#include "PlayerThings/TestPlayerCharacter.h"
#include "HStatHandler.h"
#include "HWidget_BaseStat.h"
#include "ProjectileBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Damage.h"


ATestPlayerCharacter::ATestPlayerCharacter()
{

	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	StatHandler = CreateDefaultSubobject<UHStatHandler>(TEXT("StatHandler"));
	
}

void ATestPlayerCharacter::MagicAttackNotifyBegin(FName NotifyName,const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (NotifyName == "MagicAttackTrigger")
	{
		MagicSpawn();	
	}
	if (NotifyName == "magicCombo")
	{
		bDoOnce = true;
	}
}

void ATestPlayerCharacter::OnDeath(UAnimMontage* DeathAnimation)
{
	StatHandler->CanTakeDamage = false;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::Type::PhysicsOnly);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetSimulatePhysics(true);
	GetWorld()->GetTimerManager().SetTimer(restartGameTimerHandle, this, &ATestPlayerCharacter::RestartGame, 3.0f, false);
}

void ATestPlayerCharacter::RestartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false);
}

void ATestPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &ATestPlayerCharacter::MagicAttackNotifyBegin);
	StatHandler->OnDeath.AddDynamic(this, &ATestPlayerCharacter::OnDeath);
	if (healthBarWidgetClass)
	{
		UHWidget_BaseStat* healthBarWidget = CreateWidget<UHWidget_BaseStat>(GetWorld(), healthBarWidgetClass);
		if (healthBarWidget)
		{
			healthBarWidget->AddToViewport();
			healthBarWidget->StatHandlerObjects.Add("Player", StatHandler);
		}
	}
}

void ATestPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestPlayerCharacter::MagicAttackStart()
{
	if (AnimInstance && bDoOnce)
	{
		bDoOnce = false;
		AnimInstance->Montage_Play(magicAttackMontage, 1.0f);
	}
}

void ATestPlayerCharacter::MagicSpawn()
{
	FTransform spawnTransform = GetMesh()->GetSocketTransform("magic_R");
	AProjectileBase* projectileMagic = GetWorld()->SpawnActorDeferred<AProjectileBase>(projectileMagicClass, spawnTransform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (projectileMagic)
	{
		projectileMagic->player = this;
		projectileMagic->maxSpeed = 1000.0f;
		projectileMagic->bHasTarget = false;
		UGameplayStatics::FinishSpawningActor(projectileMagic, spawnTransform);
		projectileMagic->onProjectileHit.AddDynamic(this, &ATestPlayerCharacter::ProjectileHit);
		GetCapsuleComponent()->IgnoreActorWhenMoving(projectileMagic, true);
	}
}

void ATestPlayerCharacter::ProjectileHit(AActor* HitActor)
{
	FS_DamageInfo damageInfo;
	damageInfo.AmountOfDamage = magicAttackAmount;
	UAISense_Damage::ReportDamageEvent(GetWorld(),HitActor,this,0,GetActorLocation(),HitActor->GetActorLocation());
	StatHandler->DamageTo(damageInfo, HitActor);
}

