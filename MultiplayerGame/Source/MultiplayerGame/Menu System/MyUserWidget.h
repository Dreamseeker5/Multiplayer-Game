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
		class UButton* Host;
	
	UPROPERTY(meta = (BindWidget))
		class UButton* Join;

	UFUNCTION()
		void HostServer();

	IMenuInterface* MenuInterface;

	virtual void OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld) override;

	APlayerController* PlayerController;
};
