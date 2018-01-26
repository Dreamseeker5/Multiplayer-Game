// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuInterface(class IMenuInterface* MenuInterface);

	void Setup();

protected:
		virtual bool Initialize();

private:
	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* MenuSwitcher;

	//Main menu widgets
	UPROPERTY(meta = (BindWidget))
		class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
		class UButton* HostButton;
	
	UPROPERTY(meta = (BindWidget))
		class UButton* JoinButton;

	UFUNCTION()
		void HostServer();

	UFUNCTION()
		void OpenMainMenu();

	//Join menu widgets
	UPROPERTY(meta = (BindWidget))
		class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
		class UButton* JoinMenuCancelButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* JoinMenuAcceptButton;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* IPAddressField;

	UFUNCTION()
		void OpenJoinMenu();

	UFUNCTION()
		void JoinServer();



	IMenuInterface* MenuInterface;

	virtual void OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld) override;

	APlayerController* PlayerController;
};
