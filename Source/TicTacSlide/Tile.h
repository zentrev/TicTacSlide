#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameMarker.h"
#include "Tile.generated.h"

UCLASS()
class TICTACSLIDE_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	ATile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TilePosition")
	int xPos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TilePosition")
	int yPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileActor")
	float colorSpeed = .05f;

	AGameMarker::Marker tileMark = AGameMarker::Marker::NONE;
	AGameMarker* gameMarker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	UMaterialInterface* Material;

	float GreenAmount = 0;
	float OrangeAmount = 0;
	float CurrentGreenAmount = 0;
	float CurrentOrangeAmount = 0;

	virtual void Init(int x, int y);

	virtual void StartSlide();
	virtual void CancelSlide();
	virtual void PlaceMarker(AGameMarker* markerToPlace);
	virtual void RemoveMarker();
	virtual void SetActiveTiles(bool active);
	void SetSlidable(bool slideable);

	bool canSlideTo = false;

protected:
	void FindDynMaterial();
	UMaterialInstanceDynamic* DynMaterial;

#pragma region Unreal Function
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

#pragma endregion

#pragma region Deprecated
public:
    // Moved To SlideTileAsyncTask for animations
    // virtual int ExecuteSlide(AGameMarker* incomeingMarker, FVector2D velocity);

	// Moved To TicTacSlideGameModeBase for efficiency 
	// virtual void SetTileActive(bool active, FVector2D direction);
#pragma endregion

};
