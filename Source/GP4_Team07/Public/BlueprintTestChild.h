// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable_Distractable_Parent.h"
#include "BlueprintTestChild.generated.h"

/**
 * 
 */
UCLASS()
class GP4_TEAM07_API ABlueprintTestChild : public AInteractable_Distractable_Parent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	bool bUniqueBoolean;

protected:
	virtual void BeginPlay() override;
};
