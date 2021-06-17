#include "Tile.h"
#include "TicTacSlideGameModeBase.h"
#include "BoardTile.h"

ATile::ATile() { PrimaryActorTick.bCanEverTick = true; }

void ATile::Init(int x, int y)
{
	xPos = x;
	yPos = y;
}

void ATile::PlaceMarker(AGameMarker* markerToPlace)
{
	gameMarker = markerToPlace;
	gameMarker->SetActorLocation(this->GetActorLocation());
	tileMark = gameMarker->marker;
}

void ATile::RemoveMarker()
{
	gameMarker = nullptr;
	tileMark = AGameMarker::Marker::NONE;
}

void ATile::StartSlide()
{
	UE_LOG(LogTemp, Log, TEXT("Start Slide"));

	SetActiveTiles(true);
}

void ATile::CancelSlide()
{
	UE_LOG(LogTemp, Log, TEXT("Cancel Slide"));
	SetActiveTiles(false);
}

void ATile::SetActiveTiles(bool active)
{
	ATicTacSlideGameModeBase* gameMode = ((ATicTacSlideGameModeBase*)GetWorld()->GetAuthGameMode());
	FVector2D direction;
	FVector2D nextTilePos;

	direction = FVector2D(1, 0);
	nextTilePos.X = xPos + direction.X;
	nextTilePos.Y = yPos + direction.Y;
	if (gameMode->CheckBounds(nextTilePos, true))
	{
		gameMode->SetTileActive(gameMode->Board[nextTilePos.X][nextTilePos.Y], active, direction);
	}

	direction = FVector2D(-1, 0);
	nextTilePos.X = xPos + direction.X;
	nextTilePos.Y = yPos + direction.Y;
	if (gameMode->CheckBounds(nextTilePos, true))
	{
		gameMode->SetTileActive(gameMode->Board[nextTilePos.X][nextTilePos.Y], active, direction);
	}

	direction = FVector2D(0, 1);
	nextTilePos.X = xPos + direction.X;
	nextTilePos.Y = yPos + direction.Y;
	if (gameMode->CheckBounds(nextTilePos, true))
	{
		gameMode->SetTileActive(gameMode->Board[nextTilePos.X][nextTilePos.Y], active, direction);
	}

	direction = FVector2D(0, -1);
	nextTilePos.X = xPos + direction.X;
	nextTilePos.Y = yPos + direction.Y;
	if (gameMode->CheckBounds(nextTilePos, true))
	{
		gameMode->SetTileActive(gameMode->Board[nextTilePos.X][nextTilePos.Y], active, direction);
	}
}

void ATile::SetSlidable(bool slideable)
{
	canSlideTo = slideable;

	if (slideable)
	{
		if (tileMark == AGameMarker::Marker::NONE) { OrangeAmount = .7; }
		else { OrangeAmount = 1; }
	}
	else
	{
		OrangeAmount = 0;
	}
}

void ATile::FindDynMaterial()
{
	DynMaterial = UMaterialInstanceDynamic::Create(Material, this);
	TArray<UStaticMeshComponent*> Components;
	GetComponents<UStaticMeshComponent>(Components);
	if (Components.Num() > 0) Components[0]->SetMaterial(0, DynMaterial);
}

#pragma region Unreal Frunctions

void ATile::BeginPlay()
{
	Super::BeginPlay();
	
	FindDynMaterial();
}

void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DynMaterial == nullptr) FindDynMaterial();

	if (DynMaterial != nullptr)
	{
		CurrentGreenAmount = FMath::Lerp(CurrentGreenAmount, GreenAmount, colorSpeed);
		DynMaterial->SetScalarParameterValue("Green", CurrentGreenAmount);
		CurrentOrangeAmount = FMath::Lerp(CurrentOrangeAmount, OrangeAmount, colorSpeed);
		DynMaterial->SetScalarParameterValue("Orange", CurrentOrangeAmount);
	}
}

#pragma endregion

#pragma region Deprecated
//int ATile::ExecuteSlide(AGameMarker* incomeingMarker, FVector2D velocity)
//{
//	ATicTacSlideGameModeBase* gameMode = ((ATicTacSlideGameModeBase*)GetWorld()->GetAuthGameMode());
//	UE_LOG(LogClass, Log, TEXT("Execute Slide"));
//	AGameMarker* bumpedMarker = nullptr;
//	if (gameMarker != incomeingMarker)
//	{
//		UE_LOG(LogClass, Log, TEXT("gather bump"));
//
//		bumpedMarker = gameMarker;
//		PlaceMarker(incomeingMarker);
//	}
//
//	FVector2D direction = velocity.GetSafeNormal();
//	FVector2D nextTile;
//	nextTile.X = xPos + direction.X;
//	nextTile.Y = yPos + direction.Y;
//	if (bumpedMarker != nullptr)
//	{
//		UE_LOG(LogClass, Log, TEXT("bumpin"));
//
//		if (gameMode->CheckBounds(nextTile, false))
//		{
//			UE_LOG(LogClass, Log, TEXT("knocked off"));
//			bumpedMarker->SetActorHiddenInGame(true);
//		}
//		else
//		{
//			UE_LOG(LogClass, Log, TEXT("bumped onward"));
//			gameMode->board[nextTile.X][nextTile.Y]->ExecuteSlide(bumpedMarker, direction);
//		}
//	}
//	else
//	{
//		velocity = velocity - direction;
//		UE_LOG(LogClass, Log, TEXT("velocity size: %f "), velocity.Size());
//
//		if (velocity.Size() >= .5f)
//		{
//			RemoveMarker();
//			UE_LOG(LogClass, Log, TEXT("sliding threw to %d %d"), nextTile.X, nextTile.Y);
//			gameMode->board[nextTile.X][nextTile.Y]->ExecuteSlide(incomeingMarker, velocity);
//
//		}
//		else
//		{
//			UE_LOG(LogClass, Log, TEXT("Stoping here"));
//		}
//	}
//	return 1;
//}

//void ATile::SetTileActive(bool active, FVector2D direction)
//{
//	SetSlidable(active);
//	FVector2D nextTilePos;
//
//	nextTilePos.X = xPos + direction.X;
//	nextTilePos.Y = yPos + direction.Y;
//	ATicTacSlideGameModeBase* gameMode = ((ATicTacSlideGameModeBase*)GetWorld()->GetAuthGameMode());
//
//	if (tileMark == AGameMarker::Marker::NONE)
//	{
//		if (gameMode->CheckBounds(nextTilePos, true))
//		{
//			gameMode->Board[nextTilePos.X][nextTilePos.Y]->SetTileActive(active, direction);
//		}
//	}
//}
#pragma endregion
