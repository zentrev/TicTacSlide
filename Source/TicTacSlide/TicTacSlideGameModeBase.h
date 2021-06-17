#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Async/AsyncWork.h"
#include "Blueprint/UserWidget.h"
#include "CoreTypes.h"
#include "GameMarker.h"
#include "SlideTileAsyncTask.h"
#include <vector>
#include "TicTacSlideGameModeBase.generated.h"

class ATile;
class ABoardTile;
class ASlideTile;
class AGameMarker;
class UTicTacSlideHud;

UCLASS()
class TICTACSLIDE_API ATicTacSlideGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
		int BoardSize = 3;

	std::vector<std::vector<ABoardTile*>> Board;
	std::vector<AGameMarker*> Markers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileActor")
		TSubclassOf<class ABoardTile> TileActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileActor")
		TSubclassOf<class ASlideTile> SlideTileActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileActor")
		float TileWidth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMarker")
		TSubclassOf<class AGameMarker> XMarker;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMarker")
		TSubclassOf<class AGameMarker> OMarker;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hud")
		TSubclassOf<class UUserWidget> playerHudBP;
	UTicTacSlideHud* playerHud;

	AGameMarker::Marker CurrentPlayer = AGameMarker::Marker::X;
	bool canPlay = false;
	bool checkWin = false;

	void BuildBoard();
	void ResetGame();

	AGameMarker::Marker CheckWin();
	bool CheckBounds(FVector2D position, bool inBounds);
	void ShowPlayableTiles(bool active);

	void SetTileActive(ATile* tile, bool active, FVector2D direction);
	void SlideTileAsync(ATile* tile, AGameMarker* incomeingMarker, FVector2D velocity);


private:
	FVector2D BoardOffset;
	std::vector<ASlideTile*> XSlide;
	std::vector<ASlideTile*> OSlide;

#pragma region Unreal Functions
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

#pragma endregion


};



