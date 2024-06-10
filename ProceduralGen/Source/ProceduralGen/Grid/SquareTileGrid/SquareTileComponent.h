// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "SquareCoord.h"
#include "SquareTileComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALGEN_API USquareTileComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Category = "Coordinate")
	FSquareCoord _coord;

public:

	UFUNCTION(BlueprintCallable)
	void SetCoord(const FSquareCoord& pNewCoord);

	UFUNCTION(BlueprintCallable)
	const FSquareCoord& GetCoord();
};
