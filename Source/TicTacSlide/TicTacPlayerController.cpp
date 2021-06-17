#include "TicTacPlayerController.h"
#include "TicTacSlideGameModeBase.h"
#include "DrawDebugHelpers.h"
#include <limits>
#include <string>

ATicTacPlayerController::ATicTacPlayerController() { }

void ATicTacPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftCLK", IE_Pressed, this, &ATicTacPlayerController::LeftDown);
	InputComponent->BindAction("LeftCLK", IE_Released, this, &ATicTacPlayerController::LeftUp);
}

void ATicTacPlayerController::LeftDown()
{
	if (!gameMode->canPlay) return;
	mouseDown = true;


	if (hoveredTile != nullptr)
	{
		clickedTile = hoveredTile;

		if (hoveredTile->tileMark == gameMode->CurrentPlayer)
		{
			gameMode->ShowPlayableTiles(false);

			if (hoveredTile->IsA<ASlideTile>())
			{
				((ASlideTile*)hoveredTile)->SpawnMarker();
			}

			if (clickedTile->gameMarker != nullptr)
			{
				clickedTile->StartSlide();
			}
		}
	}
}

void ATicTacPlayerController::LeftUp()
{
	if (!gameMode->canPlay) return;
	mouseDown = false;

	if (clickedTile->tileMark == gameMode->CurrentPlayer)
	{
		if (clickedTile == hoveredTile || hoveredTile == nullptr || !hoveredTile->canSlideTo)
		{
			clickedTile->CancelSlide();
			gameMode->ShowPlayableTiles(true);
			return;
		}

		if (clickedTile->gameMarker != nullptr)
		{
			FVector2D veloctiy = FVector2D(hoveredTile->xPos - clickedTile->xPos, hoveredTile->yPos - clickedTile->yPos);
			veloctiy = veloctiy + veloctiy.GetSafeNormal();

			clickedTile->SetActiveTiles(false);
			gameMode->canPlay = false;
			((ATicTacSlideGameModeBase*)GetWorld()->GetAuthGameMode())->SlideTileAsync(clickedTile, clickedTile->gameMarker, veloctiy);

			gameMode->CurrentPlayer = (gameMode->CurrentPlayer == AGameMarker::Marker::X) ? AGameMarker::Marker::O : AGameMarker::Marker::X;
		}
	}

}

void ATicTacPlayerController::BeginPlay()
{
	Super::BeginPlay();
	gameMode = ((ATicTacSlideGameModeBase*)GetWorld()->GetAuthGameMode());
	gameMode->ShowPlayableTiles(true);
}

void ATicTacPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult hit;

	FVector startLoc;
	FVector direction;
	FVector endLoc;

	DeprojectMousePositionToWorld(startLoc, direction);
	endLoc = startLoc + (direction * 100000);
	bool didHit = GetWorld()->LineTraceSingleByChannel(hit, startLoc, endLoc, ECC_Visibility);

	if (didHit)
	{
		if (hit.GetActor()->IsA<ATile>())
		{
			hoveredTile = Cast<ATile>(hit.GetActor());
		}
	}

	// Tick not being called on gamemode / temp workaround
	((ATicTacSlideGameModeBase*)GetWorld()->GetAuthGameMode())->Tick(DeltaTime);

}





