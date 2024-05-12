// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ProceduralAlgoFunctionLibrary.generated.h"

/**
 * Creating Texture at runtime:
 * https://dev.epicgames.com/community/learning/tutorials/ow9v/unreal-engine-creating-a-runtime-editable-texture-in-c
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
	static TArray<float> FbmNoiseMapPerlinNoise1D(int32 MapWidth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|PerlinNoise")
	static TArray<float> FbmNoiseMapPerlinNoise2D(int32 MapWidth, int32 MapHeight, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|PerlinNoise")
	static TArray<float> FbmNoiseMapPerlinNoise3D (int32 MapWidth, int32 MapHeight, int32 MapDepth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity);
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
	static TArray<float> FbmNoiseMapSimplexNoise1D(int32 MapWidth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static TArray<float> FbmNoiseMapSimplexNoise2D(int32 MapWidth, int32 MapHeight, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static TArray<float> FbmNoiseMapSimplexNoise3D(int32 MapWidth, int32 MapHeight, int32 MapDepth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity);

#pragma endregion


#pragma region WorleyNoise

	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|WorleyNoise")
	static TArray<float> NoiseMapWorleyNoise2D(int32 Bounds, int32 PointsNumber);

#pragma endregion
};
