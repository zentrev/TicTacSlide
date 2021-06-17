#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameMarker.generated.h"

UCLASS()
class TICTACSLIDE_API AGameMarker : public AActor
{
	GENERATED_BODY()

public:
	AGameMarker();

	enum Marker
	{
		NONE,
		X,
		O
	};

	Marker marker = Marker::X;
	int xPos;
	int yPos;

#pragma region Unreal Functions
public:	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
#pragma endregion

};

