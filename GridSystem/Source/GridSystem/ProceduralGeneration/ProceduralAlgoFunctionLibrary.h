// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ProceduralAlgoFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GRIDSYSTEM_API UProceduralAlgoFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
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
	static TArray<float> FbmMapPerlinNoise1D(int32 MapWidth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|PerlinNoise")
	static TArray<float> FbmMapPerlinNoise2D(int32 MapWidth, int32 MapHeight, float Scale, const FVector& pOrigin, int32 Octaves, float Persistance, float Lacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|PerlinNoise")
	static TArray<float> FbmMapPerlinNoise3D (int32 MapWidth, int32 MapHeight, int32 MapDepth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity);
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
	static TArray<float> FbmMapSimplexNoise1D(int32 MapWidth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static TArray<float> FbmMapSimplexNoise2D(int32 MapWidth, int32 MapHeight, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static TArray<float> FbmMapSimplexNoise3D(int32 MapWidth, int32 MapHeight, int32 MapDepth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity);
#pragma endregion
};
