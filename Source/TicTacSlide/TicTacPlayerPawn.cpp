#include "TicTacPlayerPawn.h"

ATicTacPlayerPawn::ATicTacPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

#pragma region Unreal Functions

void ATicTacPlayerPawn::BeginPlay() { Super::BeginPlay(); }

void ATicTacPlayerPawn::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void ATicTacPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) { Super::SetupPlayerInputComponent(PlayerInputComponent); }

#pragma endregion


