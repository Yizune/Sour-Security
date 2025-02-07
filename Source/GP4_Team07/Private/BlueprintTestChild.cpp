// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintTestChild.h"

void ABlueprintTestChild::BeginPlay()
{
	Super::BeginPlay();

	if (InteractableComponent)
	{
		InteractableComponent->SetActive(bUniqueBoolean); 
	}
}
