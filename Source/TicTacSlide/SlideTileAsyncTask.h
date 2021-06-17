// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TicTacSlideGameModeBase.h"
#include "GameMarker.h"
#include "Tile.h"
#include "Core/Public/Async/AsyncWork.h"

class ATicTacSlideGameModeBase;
class ATile;
class AGameMarker;

class SlideTileAsyncTask : public FNonAbandonableTask
{


public:

	ATicTacSlideGameModeBase* _gameMode = nullptr;
	ATile* _tile;
	AGameMarker* _incomeingMarker;
	FVector2D _velocity;

	SlideTileAsyncTask(ATicTacSlideGameModeBase* gameMode, ATile* tile, AGameMarker* incomeingMarker, FVector2D velocity)
	{
		_gameMode = gameMode;
		_tile = tile;
		_incomeingMarker = incomeingMarker;
		_velocity = velocity;
	};

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(PrimeCalculationAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
	}
	
	void DoWork();

	void ExecuteSlide(ATile* tile, AGameMarker* incomeingMarker, FVector2D velocity);
	
};