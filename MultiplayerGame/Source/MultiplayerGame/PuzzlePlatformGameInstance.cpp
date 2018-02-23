// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSubsystem.h"

#include "PlatformTrigger.h"
#include "Menu System/MenuWidget.h"
#include "MultiplayerGameGameMode.h"

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));

	//Find the widget menu BP and get hold of it as an object
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/UI/WBP_Menu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return; //Pointer protection
	MenuClass = MenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/UI/WBP_InGameMenu"));
	if (!ensure(InGameMenuBPClass.Class != nullptr)) return; //Pointer protection
	InGameMenuClass = InGameMenuBPClass.Class;

}

//Initialize game values just before the game executes
void UPuzzlePlatformGameInstance::Init()
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem != nullptr) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Found subsystem %s"), *Subsystem->GetSubsystemName().ToString());

		IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Found session interface"));
		}
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Found no subsystem"));
	}
}

///Called from the level BP
//Creates and adds the main menu to the viewport 
void UPuzzlePlatformGameInstance::LoadMenuWidget()
{
	//Create a widget
	if (!ensure(MenuClass != nullptr)) return; //Pointer protection
	UMenuWidget* Menu = CreateWidget<UMenuWidget>(this, MenuClass);
	
	if (!ensure(Menu != nullptr)) return; //Pointer protection
	Menu->Setup();

	Menu->SetMenuInterface(this);
}

///Called from the level BP
//Creates and adds the pause menu to the viewport 
void UPuzzlePlatformGameInstance::LoadInGameMenu()
{
	//Create a widget
	if (!ensure(InGameMenuClass != nullptr)) return; //Pointer protection
	UMenuWidget* Menu = CreateWidget<UMenuWidget>(this, InGameMenuClass);

	if (!ensure(Menu != nullptr)) return; //Pointer protection
	Menu->Setup();

	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformGameInstance::LoadMainMenu()
{
	UWorld* World = GetWorld();
	if (World)
	{
		if (World->IsServer())
		{
			AMultiplayerGameGameMode* GM = World->GetAuthGameMode<AMultiplayerGameGameMode>();
			if (GM)
			{
				GM->ReturnToMainMenuHost();
			}
		}
		else
		{
			APlayerController* PC = GetFirstLocalPlayerController();
			if (PC)
			{
				PC->ClientReturnToMainMenu("Back to main menu");
			}
		}
	}
}

void UPuzzlePlatformGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	
	Engine->AddOnScreenDebugMessage(0, 4, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	
	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformGameInstance::Join(const FString& Address)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 4, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
