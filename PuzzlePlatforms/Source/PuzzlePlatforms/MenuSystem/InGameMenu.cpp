// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenu.h"

#include "Components/Button.h"

bool UInGameMenu::Initialize()
{
	// Override.
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelInGameMenu);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::BackToMainMenu);


	return true;
}

void UInGameMenu::CancelInGameMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("Cancel in game pressed"));
	TearDown();
}

void UInGameMenu::BackToMainMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("Join a server"));
	if (MenuInterface != nullptr)
	{
		TearDown();
		MenuInterface->LoadMainMenu();
	}
}

