#include "TicTacSlideGameModeBase.h"
#include "BoardTile.h"
#include "SlideTile.h"
#include "GameMarker.h"
#include "TicTacSlideHud.h"

void ATicTacSlideGameModeBase::BuildBoard()
{
	FVector location;
	FActorSpawnParameters SpawnPrams;
	ABoardTile* tile;
	ASlideTile* slideTile;
	BoardOffset = FVector2D(TileWidth * -1, TileWidth * -1);
	for (int i = 0; i < BoardSize; i++)
	{
		std::vector<ABoardTile*> column;

		for (int j = 0; j < BoardSize; j++)
		{
			location = FVector(i * TileWidth + BoardOffset.X, j * TileWidth + BoardOffset.Y, 0);
			tile = GetWorld()->SpawnActor<ABoardTile>(TileActor, location, FRotator::ZeroRotator, SpawnPrams);
			tile->Init(i, j);
			column.push_back(tile);
		}
		Board.push_back(column);

		location = FVector(i * TileWidth + BoardOffset.X, -1 * TileWidth + BoardOffset.Y, 0);
		slideTile = GetWorld()->SpawnActor<ASlideTile>(SlideTileActor, location, FRotator::ZeroRotator, SpawnPrams);
		slideTile->Init(i, -1);
		slideTile->SetMarker(AGameMarker::Marker::X);
		XSlide.push_back(slideTile);

		location = FVector(i * TileWidth + BoardOffset.X, BoardSize * TileWidth + BoardOffset.Y, 0);
		slideTile = GetWorld()->SpawnActor<ASlideTile>(SlideTileActor, location, FRotator::ZeroRotator, SpawnPrams);
		slideTile->Init(i, BoardSize);
		slideTile->SetMarker(AGameMarker::Marker::O);
		OSlide.push_back(slideTile);

	}

	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			Board[i][j]->InitializeTile(Board);
		}
	}
}

void ATicTacSlideGameModeBase::ResetGame()
{
	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			Board[i][j]->RemoveMarker();
		}
	}

	for (int i = 0; i < Markers.size(); i++)
	{
		Markers[i]->K2_DestroyActor();
	}
	Markers.clear();

	playerHud->HideWinner();

	canPlay = true;
	ShowPlayableTiles(true);
}


AGameMarker::Marker ATicTacSlideGameModeBase::CheckWin()
{
	AGameMarker::Marker winner = AGameMarker::Marker::NONE;
	AGameMarker::Marker hold = AGameMarker::Marker::NONE;
	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			if (Board[i][j] == nullptr) continue;
			hold = Board[i][j]->CheckWinCase();
			if (hold != AGameMarker::Marker::NONE)
			{
				if (winner == AGameMarker::Marker::NONE)
				{
					winner = hold;
				}
				else
				{
					if (winner != hold)
					{
						winner = AGameMarker::Marker::NONE;
						return AGameMarker::Marker::NONE;
					}
				}
			}
		}
	}

	if (winner == AGameMarker::Marker::NONE) return winner;
	canPlay = false;
	playerHud->ShowWinner(winner);

	return winner;
}

bool ATicTacSlideGameModeBase::CheckBounds(FVector2D position, bool inBounds)
{
	if (inBounds) { return ((position.X >= 0 && position.X < BoardSize) && (position.Y >= 0 && position.Y < BoardSize)); }
	else { return ((position.X < 0 || position.X >= BoardSize) || (position.Y < 0 || position.Y >= BoardSize)); }
}

void ATicTacSlideGameModeBase::ShowPlayableTiles(bool active)
{
	if (!canPlay) active = false;
	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			if (Board[i][j] == nullptr) continue;
			if (active && Board[i][j]->tileMark == CurrentPlayer)
			{
				Board[i][j]->GreenAmount = 1;
			}
			else
			{
				Board[i][j]->GreenAmount = 0;
			}
		}
	}

	if (CurrentPlayer == AGameMarker::Marker::X)
	{
		for (int i = 0; i < XSlide.size(); i++) { XSlide[i]->GreenAmount = active ? 1 : 0; }
	}
	else
	{
		for (int i = 0; i < OSlide.size(); i++) { OSlide[i]->GreenAmount = active ? 1 : 0; }
	}
}

void ATicTacSlideGameModeBase::SetTileActive(ATile* tile, bool active, FVector2D direction)
{
	tile->SetSlidable(active);
	FVector2D nextTilePos;

	nextTilePos.X = tile->xPos + direction.X;
	nextTilePos.Y = tile->yPos + direction.Y;

	if (tile->tileMark == AGameMarker::Marker::NONE)
	{
		if (CheckBounds(nextTilePos, true))
		{
			SetTileActive(Board[nextTilePos.X][nextTilePos.Y], active, direction);
		}
	}
};

void ATicTacSlideGameModeBase::SlideTileAsync(ATile* tile, AGameMarker* incomeingMarker, FVector2D velocity) { (new FAutoDeleteAsyncTask<SlideTileAsyncTask>(this, tile, incomeingMarker, velocity))->StartBackgroundTask(); };


#pragma region Unreal Functions
void ATicTacSlideGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;

	BuildBoard();

	if (playerHudBP != nullptr)
	{
		UUserWidget* hud = CreateWidget<UUserWidget>(GetWorld(), playerHudBP);
		playerHud = Cast<UTicTacSlideHud>(hud);
		playerHud->AddToViewport();
		playerHud->FindAnimations();
	}

	canPlay = true;
}

void ATicTacSlideGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!canPlay && checkWin)
	{
		checkWin = false;
		if (CheckWin() == AGameMarker::Marker::NONE)
		{
			canPlay = true;
			ShowPlayableTiles(true);
		}
	}
}
#pragma endregion
