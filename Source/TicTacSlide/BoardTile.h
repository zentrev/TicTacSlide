#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
#include <vector>
#include "BoardTile.generated.h"

UCLASS()
class TICTACSLIDE_API ABoardTile : public ATile
{
	GENERATED_BODY()
	
public:	
	ABoardTile();

	void InitializeTile(std::vector<std::vector<ABoardTile*>> board);
	AGameMarker::Marker CheckWinCase();

private:
	enum TileFunction
	{
		NONE = 0,
		VERTICAL = (1 << 0),
		HORIZONTAL = (1 << 1)
	};

	TileFunction tileFunction;
	std::vector<std::vector<ABoardTile*>> winCases;

#pragma region Unreal Functions
public:	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
#pragma endregion

};
