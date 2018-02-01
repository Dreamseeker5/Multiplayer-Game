// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenu.h"

#include "Components/Button.h"


bool UInGameMenu::Initialize()
{
	bool Succes = Super::Initialize();
	if (!Succes) return false;

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelPressed);
	
	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitPressed);

	return true;
}

void UInGameMenu::CancelPressed()
{
	this->RemoveFromViewport();

	FInputModeGameOnly InputModeData;

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;
}

void UInGameMenu::QuitPressed()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->LoadMainMenu();
	}
}

//Method called when the world is being destroyed
//Used to remove every widget on the screen before the world comes to an end
void UInGameMenu::OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
}

