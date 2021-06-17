#include "SlideTile.h"
#include "BoardTile.h"
#include "TicTacSlideGameModeBase.h"

ASlideTile::ASlideTile() { PrimaryActorTick.bCanEverTick = true; }

void ASlideTile::SpawnMarker()
{
	FVector location = FVector(this->GetActorLocation().X, this->GetActorLocation().Y, 10);
	FActorSpawnParameters SpawnPrams;
	gameMarker = GetWorld()->SpawnActor<AGameMarker>(markerActor, location, FRotator::ZeroRotator, SpawnPrams);
	gameMarker->marker = tileMark;
	((ATicTacSlideGameModeBase*)GetWorld()->GetAuthGameMode())->Markers.push_back(gameMarker);
}

void ASlideTile::PlaceMarker(AGameMarker* markerToPlace)
{
	gameMarker = markerToPlace;
	gameMarker->SetActorLocation(this->GetActorLocation());
}

void ASlideTile::RemoveMarker() { gameMarker = nullptr; }

void ASlideTile::SetMarker(AGameMarker::Marker marker)
{
	tileMark = marker;
	markerActor = (tileMark == AGameMarker::Marker::X) ? ((ATicTacSlideGameModeBase*)GetWorld()->GetAuthGameMode())->XMarker : ((ATicTacSlideGameModeBase*)GetWorld()->GetAuthGameMode())->OMarker;
}

void ASlideTile::CancelSlide()
{
	SetActiveTiles(false);
	gameMarker->SetActorHiddenInGame(true);
	RemoveMarker();
}

void ASlideTile::SetActiveTiles(bool active)
{
	ATicTacSlideGameModeBase* gameMode = ((ATicTacSlideGameModeBase*)GetWorld()->GetAuthGameMode());
	FVector2D direction;
	FVector2D nextTilePos;

	if (tileMark == AGameMarker::Marker::X)
	{
		direction = FVector2D(0, 1);
		nextTilePos.X = xPos + direction.X;
		nextTilePos.Y = yPos + direction.Y;
		if (gameMode->CheckBounds(nextTilePos, true))
		{
			gameMode->SetTileActive(gameMode->Board[nextTilePos.X][nextTilePos.Y], active, direction);
		}
	}
	else if (tileMark == AGameMarker::Marker::O)
	{
		direction = FVector2D(0, -1);
		nextTilePos.X = xPos + direction.X;
		nextTilePos.Y = yPos + direction.Y;
		if (gameMode->CheckBounds(nextTilePos, true))
		{
			gameMode->SetTileActive(gameMode->Board[nextTilePos.X][nextTilePos.Y], active, direction);
		}
	}
}

#pragma region Unreal Functions

void ASlideTile::BeginPlay()
{
	Super::BeginPlay();
	DynMaterial->SetScalarParameterValue("isSlideTile", 1);
}

void ASlideTile::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

#pragma endregion

