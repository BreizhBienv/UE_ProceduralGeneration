// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ProceduralAlgoFunctionLibrary.generated.h"

/*
*	Sources:
*	Creating Texture at runtime :
*	https://dev.epicgames.com/community/learning/tutorials/ow9v/unreal-engine-creating-a-runtime-editable-texture-in-c
*/

/**
 * 2D Array index formula:
 *		- Row Major	= (X * width) + Y
 *		- Col Major	= (Y * height) + X
 *
 * 3D Array index formula:
 *		- Row Major	= (X * height * depth) + (Y * depth) + Z 
 *		- Col Major	= (Z * width * height) + (Y * height) + X
 */

/*
* 
*/
UCLASS()
class GRIDSYSTEM_API UProceduralAlgoFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|Texture")
	static UTexture2D* TextureFrom2DNoiseMap(int32 MapWidth, int32 MapHeight, const TArray<float>& NoiseMap);

#pragma region PerlinNoise
	
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|PerlinNoise")
	static float PerlinNoise1D(float X);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|PerlinNoise")
	static float PerlinNoise2D(float X, float Y);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|PerlinNoise")
	static float PerlinNoise3D(float X, float Y, float Z);

	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|PerlinNoise")
	static float FbmPerlinNoise1D(float X, float Scale, int32 Octaves, float Persistance, float Lacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|PerlinNoise")
	static float FbmPerlinNoise2D(float X, float Y, float Scale, int32 Octaves, float Persistance, float Lacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|PerlinNoise")
	static float FbmPerlinNoise3D(float X, float Y, float Z, float Scale, int32 Octaves, float Persistance, float Lacunarity);

	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|PerlinNoise")
	static TArray<float> FbmPerlinNoiseMap1D(int32 MapWidth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|PerlinNoise")
	static TArray<float> FbmPerlinNoiseMap2D(int32 MapWidth, int32 MapHeight, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|PerlinNoise")
	static TArray<float> FbmPerlinNoiseMap3D (int32 MapWidth, int32 MapHeight, int32 MapDepth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity);
#pragma endregion


#pragma region SimplexNoise

	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static float SimplexNoise1D(float X);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static float SimplexNoise2D(float X, float Y);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static float SimplexNoise3D(float X, float Y, float Z);

	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static float FbmSimplexNoise1D(float X, float Scale, int32 Octaves, float Persistance, float Lacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static float FbmSimplexNoise2D(float X, float Y, float Scale, int32 Octaves, float Persistance, float Lacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static float FbmSimplexNoise3D(float X, float Y, float Z, float Scale, int32 Octaves, float Persistance, float Lacunarity);

	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static TArray<float> FbmSimplexNoiseMap1D(int32 MapWidth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static TArray<float> FbmSimplexNoiseMap2D(int32 MapWidth, int32 MapHeight, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static TArray<float> FbmSimplexNoiseMap3D(int32 MapWidth, int32 MapHeight, int32 MapDepth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity);

#pragma endregion


#pragma region WorleyNoise

	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|WorleyNoise")
	static TArray<float> WorleyNoiseMap2D(int32 Width, int32 Height, int32 PointsNumber);

	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|WorleyNoise")
	static TArray<float> WorleyNoiseMap3D(int32 Width, int32 Height, int32 Depth, int32 PointsNumber);

#pragma endregion

#pragma region MidpointDisplacement

	/*
	* The size of the map have to be 1 + 2^n for proper use.
	*/
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|MidpointDisplacement")
	static TArray<float> MidpointDisplacementMap2D(int32 Width, int32 Seed, float Spread, float SpreadFactor);

	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|MidpointDisplacement")
	static TArray<float> DiamondSquareMap2D(int32 Width, int32 Seed, float Roughness);

#pragma endregion
};
