#include "BoardTile.h"

ABoardTile::ABoardTile() { PrimaryActorTick.bCanEverTick = true; }

void ABoardTile::InitializeTile(std::vector<std::vector<ABoardTile*>> board)
{
	tileFunction = TileFunction::NONE;
	std::vector<ABoardTile*> winCase;

	if (xPos - 1 >= 0 && xPos + 1 < board.size())
	{
		tileFunction = static_cast<TileFunction>(tileFunction | TileFunction::HORIZONTAL);
		winCase.clear();
		winCase.push_back(board[xPos - 1][yPos]);
		winCase.push_back(board[xPos + 1][yPos]);
		winCases.push_back(winCase);
	}

	if (yPos - 1 >= 0 && yPos + 1 < board[0].size())
	{
		tileFunction = static_cast<TileFunction>(tileFunction | TileFunction::VERTICAL);
		winCase.clear();
		winCase.push_back(board[xPos][yPos - 1]);
		winCase.push_back(board[xPos][yPos + 1]);
		winCases.push_back(winCase);
	}

	if (tileFunction == (TileFunction::HORIZONTAL | TileFunction::VERTICAL))
	{
		winCase.clear();
		winCase.push_back(board[xPos - 1][yPos - 1]);
		winCase.push_back(board[xPos + 1][yPos + 1]);
		winCases.push_back(winCase);
		winCase.clear();
		winCase.push_back(board[xPos - 1][yPos + 1]);
		winCase.push_back(board[xPos + 1][yPos - 1]);
		winCases.push_back(winCase);
	}
}

AGameMarker::Marker ABoardTile::CheckWinCase()
{
	if (tileFunction == TileFunction::NONE || tileMark == AGameMarker::Marker::NONE) return AGameMarker::Marker::NONE;

	bool foundWin;
	for (int i = 0; i < winCases.size(); i++)
	{
		foundWin = true;
		for (int j = 0; j < winCases[i].size(); j++)
		{
			if (tileMark != winCases[i][j]->tileMark) foundWin = false;
		}

		if (foundWin)
		{
			return tileMark;
		}
	}

	return AGameMarker::Marker::NONE;
}

#pragma region Unreal Functions

void ABoardTile::BeginPlay() { Super::BeginPlay(); }

void ABoardTile::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

#pragma endregion

