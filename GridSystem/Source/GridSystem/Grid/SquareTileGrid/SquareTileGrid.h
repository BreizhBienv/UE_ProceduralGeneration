// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SquareTileGrid/SquareCoord.h"
#include "SquareTileGrid.generated.h"

UCLASS()
class GRIDSYSTEM_API ASquareTileGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	UStaticMesh* _basicTile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Option")
	int32 _width = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Option")
	int32 _height = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Option")
	float _offset = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Option")
	float _scale = 1;

	// Sets default values for this actor's properties
	ASquareTileGrid();

protected:
	FVector _tileScale;

	float _xTileHalfextent;
	float _yTileHalfextent;

	TMap<FSquareCoord, class USquareTileComponent*> _grid;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GenerateGrid(float pX, float pY);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
