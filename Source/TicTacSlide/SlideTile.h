#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameMarker.h"
#include "Tile.h"
#include "SlideTile.generated.h"

UCLASS()
class TICTACSLIDE_API ASlideTile : public ATile
{
	GENERATED_BODY()
	
public:	
	ASlideTile();

	TSubclassOf<class AGameMarker> markerActor;

	void SpawnMarker();
	void SetMarker(AGameMarker::Marker marker);
	virtual void PlaceMarker(AGameMarker* markerToPlace) override;
	virtual void RemoveMarker() override;
	virtual void CancelSlide() override;
	virtual void SetActiveTiles(bool active) override;

#pragma region Unreal Functions
public:	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
#pragma endregion
};
