

#include "PlayerThings/TestCharacterPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerThings/TestPlayerCharacter.h"

void ATestCharacterPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	TestCharacter = Cast<ATestPlayerCharacter>(aPawn);
	if (!TestCharacter) { return; }
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInputComponent) { return; }
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!EnhancedInputSubsystem) { return; }
	EnhancedInputSubsystem->ClearAllMappings();
	EnhancedInputSubsystem->AddMappingContext(DefaultMappingContext, 0);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATestCharacterPlayerController::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATestCharacterPlayerController::Look);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ATestCharacterPlayerController::HandleJump);
	EnhancedInputComponent->BindAction(MagicAttackAction, ETriggerEvent::Triggered, TestCharacter.Get(), &ATestPlayerCharacter::MagicAttackStart);
}

void ATestCharacterPlayerController::Move(const FInputActionInstance& InputActionInstance)
{
	const FVector2D movementVector = InputActionInstance.GetValue().Get<FVector2D>();
	if (!TestCharacter) { return; }
	const FRotator Rotation = TestCharacter->Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	TestCharacter->AddMovementInput(ForwardDirection, movementVector.Y);
	TestCharacter->AddMovementInput(RightDirection, movementVector.X);
}

void ATestCharacterPlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D lookVector = InputActionValue.Get<FVector2D>();
	if (!TestCharacter) { return; }
	AddYawInput(lookVector.X * -1);
	AddPitchInput(lookVector.Y * -1);
}

void ATestCharacterPlayerController::HandleJump()
{
	if (!TestCharacter) { return; }
	TestCharacter->Jump();
}
