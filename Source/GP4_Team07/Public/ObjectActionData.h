#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ObjectActionData.generated.h"

UENUM(BlueprintType)
enum class E_ActionCategory : uint8
{
	None UMETA(DisplayName = "None"),
	Interact UMETA(DisplayName = "Interact"),
	Overload UMETA(DisplayName = "Overload"),
	Boobytrap UMETA(DisplayName = "Boobytrap")
};

USTRUCT(BlueprintType)
struct FS_ObjectAction : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ActionName;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	E_ActionCategory ActionCategory;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ActionFunction;
};

