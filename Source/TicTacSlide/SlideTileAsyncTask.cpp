// Fill out your copyright notice in the Description page of Project Settings.


#include "SlideTileAsyncTask.h"

void SlideTileAsyncTask::DoWork()
{
	ExecuteSlide(_tile, _incomeingMarker, _velocity);
}

void SlideTileAsyncTask::ExecuteSlide(ATile* tile, AGameMarker* incomeingMarker, FVector2D velocity)
{
	AGameMarker* bumpedMarker = nullptr;
	if (tile->gameMarker != incomeingMarker)
	{
		bumpedMarker = tile->gameMarker;
		tile->PlaceMarker(incomeingMarker);
	}

	FVector2D direction = velocity.GetSafeNormal();
	FVector2D nextTile;
	nextTile.X = tile->xPos + direction.X;
	nextTile.Y = tile->yPos + direction.Y;
	if (bumpedMarker != nullptr)
	{
		if (_gameMode->CheckBounds(nextTile, false))
		{
			// ADD - play and wait for Knocked off Animation
			UE_LOG(LogTemp, Log, TEXT("knocked off"));
			bumpedMarker->SetActorHiddenInGame(true);
			_gameMode->checkWin = true;
		}
		else
		{
			// ADD - play and wait for bumped Animation
			UE_LOG(LogTemp, Log, TEXT("bumped onward"));
			ExecuteSlide((ATile*)(_gameMode->Board[nextTile.X][nextTile.Y]), bumpedMarker, direction);
		}
	}
	else
	{
		velocity = velocity - direction;
		if (velocity.Size() >= .5f)
		{
			// ADD - play and wait for sliding Animation
			tile->RemoveMarker();
			UE_LOG(LogTemp, Log, TEXT("sliding threw"));
			ExecuteSlide((ATile*)(_gameMode->Board[nextTile.X][nextTile.Y]), incomeingMarker, velocity);
		}
		else
		{
			// ADD - play and wait for stoping Animation
			UE_LOG(LogTemp, Log, TEXT("Stoping here"));
			_gameMode->checkWin = true;
		}
	}
};