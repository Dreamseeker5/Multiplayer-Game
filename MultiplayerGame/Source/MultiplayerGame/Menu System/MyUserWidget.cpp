// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUserWidget.h"

#include "Components/Button.h"


bool UMyUserWidget::Initialize()
{
	bool Succes = Super::Initialize();
	if (!Succes) return false;

	if (!ensure(Host != nullptr)) return false;
	Host->OnClicked.AddDynamic(this, &UMyUserWidget::HostServer);

	return true;
}

void UMyUserWidget::HostServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Hosting Server!"));
}

