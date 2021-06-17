#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Animation/WidgetAnimation.h"
#include "TicTacSlideGameModeBase.h"
#include "GameMarker.h"
#include "TicTacSlideHud.generated.h"


UCLASS(Abstract)
class TICTACSLIDE_API UTicTacSlideHud : public UUserWidget
{
	GENERATED_BODY()

public:
	UTicTacSlideHud(const FObjectInitializer& ObjectInitializer);

	virtual void FindAnimations();
	void PlayAnimationsByName(FName AnimationName);

	void ShowWinner(AGameMarker::Marker winner);
	void HideWinner();

	UFUNCTION(BlueprintCallable, Category = "Buttons")
		void QuitGame() { FGenericPlatformMisc::RequestExit(true); };
	UFUNCTION(BlueprintCallable, Category = "Buttons")
		void Replay();

protected:
	TMap<FName, UWidgetAnimation*> AnimationMap;


};
