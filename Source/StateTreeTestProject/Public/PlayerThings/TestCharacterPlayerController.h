

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "TestCharacterPlayerController.generated.h"


UCLASS()
class STATETREETESTPROJECT_API ATestCharacterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void OnPossess(APawn* aPawn) override;
	
	void Move(const FInputActionInstance& InputActionInstance);
	void Look(const FInputActionValue& InputActionValue);
	void HandleJump();
	
	UPROPERTY()
	TObjectPtr<class ATestPlayerCharacter> TestCharacter;
	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Movement")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Movement")
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Movement")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Movement")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Movement")
	TObjectPtr<UInputAction> MagicAttackAction;
};
