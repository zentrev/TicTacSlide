#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameMarker.h"
#include "SlideTile.h"
#include "BoardTile.h"
#include "TicTacPlayerController.generated.h"

class ATicTacSlideGameModeBase;

UCLASS()
class TICTACSLIDE_API ATicTacPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATicTacPlayerController();

#pragma region Input
public:
	ATicTacSlideGameModeBase* gameMode;

	FVector2D mouseXY;

	virtual void SetupInputComponent() override;
	void LeftDown();
	void LeftUp();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


private:
	bool mouseDown = false;
	ATile* clickedTile;
	ATile* hoveredTile;

#pragma endregion


	
};
