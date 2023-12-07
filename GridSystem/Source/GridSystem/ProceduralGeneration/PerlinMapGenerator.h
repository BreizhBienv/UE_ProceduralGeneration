// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PerlinMapGenerator.generated.h"
/**
 * 
 */
UCLASS()
class GRIDSYSTEM_API APerlinMapGenerator : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenerationParameter|Map")
	int32 _mapWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenerationParameter|Map")
	int32 _mapHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenerationParameter|Map")
	float _scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenerationParameter|Perlin")
	int32 _seed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenerationParameter|Perlin")
	int32 _octaves;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenerationParameter|Perlin")
	float _persistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenerationParameter|Perlin")
	float _lacunarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenerationParameter|Perlin")
	FVector2f _offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenerationParameter|Map")
	AActor* _plane = nullptr;

	APerlinMapGenerator();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void DisplayMap();
};
