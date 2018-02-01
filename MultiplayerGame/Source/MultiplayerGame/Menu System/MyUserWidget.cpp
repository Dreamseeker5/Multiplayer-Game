// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUserWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"


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

	if (!ensure(JoinMenuAcceptButton != nullptr)) return false;
	JoinMenuAcceptButton->OnClicked.AddDynamic(this, &UMyUserWidget::JoinServer);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UMyUserWidget::ExitGame);

	return true;
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
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}

void UMyUserWidget::JoinServer()
{
	if (MenuInterface != nullptr)
	{
		if (!ensure(IPAddressField != nullptr)) return;
		MenuInterface->Join(IPAddressField->GetText().ToString());
	}
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

void UMyUserWidget::ExitGame()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	//Get hold of the player controller
	PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}
