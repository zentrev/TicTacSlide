#include "GameMarker.h"

AGameMarker::AGameMarker() { PrimaryActorTick.bCanEverTick = true; }

#pragma region Unreal Functions

void AGameMarker::BeginPlay() { Super::BeginPlay(); }

void AGameMarker::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

#pragma endregion



