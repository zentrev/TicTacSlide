#include "TicTacSlideHud.h"

UTicTacSlideHud::UTicTacSlideHud(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { /*FindAnimations();*/ }

void UTicTacSlideHud::FindAnimations()
{
	AnimationMap = TMap<FName, UWidgetAnimation*>();
	UProperty* Prop = GetClass()->PropertyLink;

	while (Prop != nullptr)
	{
		if (Prop->GetClass() == UObjectProperty::StaticClass())
		{
			UObjectProperty* ObjProp = Cast<UObjectProperty>(Prop);

			if (ObjProp->PropertyClass == UWidgetAnimation::StaticClass())
			{
				UObject* Obj = ObjProp->GetObjectPropertyValue_InContainer(this);
				UWidgetAnimation* WidgetAnim = Cast<UWidgetAnimation>(Obj);

				if (WidgetAnim != nullptr && WidgetAnim->MovieScene != nullptr)
				{
					FName AnimName = WidgetAnim->MovieScene->GetFName();
					AnimationMap.Add(AnimName, WidgetAnim);
					UE_LOG(LogTemp, Warning, TEXT("adding animation"));

				}
			}
		}
		Prop = Prop->PropertyLinkNext;
	}
}

void UTicTacSlideHud::PlayAnimationsByName(FName AnimationName)
{
	UWidgetAnimation* WidgetAnim = *AnimationMap.Find(AnimationName);
	if (WidgetAnim != nullptr) PlayAnimation(WidgetAnim);
}

void UTicTacSlideHud::ShowWinner(AGameMarker::Marker winner)
{
	PlayAnimationsByName("ShowWinner");
	if (winner == AGameMarker::Marker::X) { PlayAnimationsByName("ShowX"); }
	else { PlayAnimationsByName("ShowO"); };
};

void UTicTacSlideHud::HideWinner() { PlayAnimationsByName("HideWinner"); };

void UTicTacSlideHud::Replay() { ((ATicTacSlideGameModeBase*)GetWorld()->GetAuthGameMode())->ResetGame(); };



