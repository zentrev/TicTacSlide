#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TicTacPlayerPawn.generated.h"

UCLASS()
class TICTACSLIDE_API ATicTacPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	ATicTacPlayerPawn();

#pragma region Unreal Functions
public:	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma endregion


};
