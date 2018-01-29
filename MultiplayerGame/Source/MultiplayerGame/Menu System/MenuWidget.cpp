// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"
#include "MenuInterface.h"

void UMenuWidget::Setup()
{
	//Add Widget to viewport
	this->AddToViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	//Get hold of the player controller
	PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	//Setting the input mode so it's able to interact only with the UI
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);

	//Makes the mouse cursor show on the screen
	PlayerController->bShowMouseCursor = true;
}

void UMenuWidget::SetMenuInterface(class IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}



