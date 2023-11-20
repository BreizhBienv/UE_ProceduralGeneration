// Fill out your copyright notice in the Description page of Project Settings.


#include "SquareTileGrid.h"
#include "SquareTileGrid/SquareTileComponent.h"

// Sets default values
ASquareTileGrid::ASquareTileGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* newRoot = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(newRoot);
}

// Called when the game starts or when spawned
void ASquareTileGrid::BeginPlay()
{
	Super::BeginPlay();
	
	_tileScale = FVector(_scale, _scale, 1);
	_xTileHalfextent = _basicTile->GetBoundingBox().Max.X * _scale * 2;
	_yTileHalfextent = _basicTile->GetBoundingBox().Max.Y * _scale * 2;
	
	float halfRow = (_width - 1.f) / 2.f;
	float halfHeight = (_height - 1.f) / 2.f;
	
	for (float i = -halfRow; i <= halfRow; ++i)
		for (float j = -halfHeight; j <= halfHeight; ++j)
			GenerateGrid(i, j);
}

void ASquareTileGrid::GenerateGrid(float pX, float pY)
{
	FName name = *FString::Printf(TEXT("Tile_%g_%g"), pX, pY);

	USquareTileComponent* newTile = NewObject<USquareTileComponent>(this, name);
	newTile->RegisterComponent();
	AddInstanceComponent(newTile);

	newTile->SetStaticMesh(_basicTile);
	newTile->AttachToComponent(
		RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	float X = pY * (_xTileHalfextent + _offset);
	float Y = pX * (_yTileHalfextent + _offset);

	newTile->SetRelativeLocation(FVector(X, Y, 0));
	newTile->SetRelativeScale3D(_tileScale);


	FSquareCoord newCoord(X, Y);
	newTile->SetCoord(newCoord);

	_grid.Add(newCoord, newTile);
}

// Called every frame
void ASquareTileGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

