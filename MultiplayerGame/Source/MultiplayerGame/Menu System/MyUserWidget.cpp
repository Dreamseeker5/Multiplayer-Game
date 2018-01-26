// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUserWidget.h"
#include "MenuInterface.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"


bool UMyUserWidget::Initialize()
{
	bool Succes = Super::Initialize();
	if (!Succes) return false;

	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMyUserWidget::HostServer);

	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMyUserWidget::OpenJoinMenu);

	if (!ensure(JoinMenuCancelButton != nullptr)) return false;
	JoinMenuCancelButton->OnClicked.AddDynamic(this, &UMyUserWidget::OpenMainMenu);

	return true;
}

void UMyUserWidget::SetMenuInterface(class IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

void UMyUserWidget::Setup()
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

//Method called when the world is being destroyed
//Override method, change the input mode to game only and hides the mouse cursor
void UMyUserWidget::OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

	FInputModeGameOnly InputModeData;

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;
}

void UMyUserWidget::HostServer()
{
	///UE_LOG(LogTemp, Warning, TEXT("Hosting Server!"));

	MenuInterface->Host();
}

void UMyUserWidget::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr) || !ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMyUserWidget::OpenMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr) || !ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);

}

