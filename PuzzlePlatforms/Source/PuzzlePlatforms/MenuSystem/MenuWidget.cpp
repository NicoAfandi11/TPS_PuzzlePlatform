// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"

void UMenuWidget::Setup()
{
	// Load menu to the viewport.
	this->AddToViewport();

	// Configure input mode.
	// Get player controller.
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	// Get input mode data.
	FInputModeUIOnly InputModeData;
	// Set what widget to focus.
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	// Set lock mouse behavior. (DoNotLock = You can move the cursor outside the viewport).
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	// Append the configured input mode to player controller.
	PlayerController->SetInputMode(InputModeData);
	// Show the mouse cursor.
	PlayerController->bShowMouseCursor = true;
}

void UMenuWidget::TearDown()
{
	// Load menu to the viewport.
	this->RemoveFromViewport();

	// Configure input mode.
	// Get player controller.
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	// Get input mode data.
	FInputModeGameOnly InputModeData;

	// Append the configured input mode to player controller.
	PlayerController->SetInputMode(InputModeData);
	// Show the mouse cursor.
	PlayerController->bShowMouseCursor = false;
}

void UMenuWidget::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

