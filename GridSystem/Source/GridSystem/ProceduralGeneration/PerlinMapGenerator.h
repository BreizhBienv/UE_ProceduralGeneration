// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GenericsEnum.h"

#include "PerlinMapGenerator.generated.h"
/**
 * 
 */
UCLASS()
class GRIDSYSTEM_API APerlinMapGenerator : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenerationParameter|Perlin")
	EProceduralGeneration _generationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenerationParameter|Map")
	int32 _mapWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenerationParameter|Map")
	int32 _mapHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenerationParameter|Map")
	float _scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenerationParameter|Perlin",
		meta = (ClampMin = "1", ClampMax = "8", UIMin = "1", UIMax = "8"))
	int32 _octaves;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenerationParameter|Perlin",
		meta = (ClampMin = "0", ClampMax = "1.0", UIMin = "0", UIMax = "1.0"))
	float _persistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenerationParameter|Perlin", 
		meta = (ClampMin = "1.0", ClampMax = "8.0", UIMin = "1.0", UIMax = "8.0"))
	float _lacunarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenerationParameter|Map")
	AActor* _plane = nullptr;

	APerlinMapGenerator();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void DisplayMap();

	TArray<float> GetNoiseMap();
};
