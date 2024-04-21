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
	static float PerlinNoise1D(float pX, float pScale);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|PerlinNoise")
	static float PerlinNoise2D(float pX, float pY, float pScale);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|PerlinNoise")
	static float PerlinNoise3D(float pX, float pY, float pZ, float pScale);

	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|PerlinNoise")
	static float FbmPerlinNoise1D(float pX, float pScale, int32 pOctaves, float pPersistance, float pLacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|PerlinNoise")
	static float FbmPerlinNoise2D(float pX, float pY, float pScale, int32 pOctaves, float pPersistance, float pLacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|PerlinNoise")
	static float FbmPerlinNoise3D(float pX, float pY, float pZ, float pScale, int32 pOctaves, float pPersistance, float pLacunarity);

	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|PerlinNoise")
	static TArray<float> FbmMapSPerlinNoise1D(const int32 pMapWidth, float pScale, const FVector& pOrigin, const int32 pOctaves, const float pPersistance, const float pLacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|PerlinNoise")
	static TArray<float> FbmMapPerlinNoise2D(const int32 pMapWidth, const int32 pMapHeight, float pScale, const FVector& pOrigin, const int32 pOctaves, const float pPersistance, const float pLacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|PerlinNoise")
	static TArray<float> FbmMapPerlinNoise3D(const int32 pMapWidth, const int32 pMapHeight, const int32 pMapDepth, float pScale, const FVector& pOrigin, const int32 pOctaves, const float pPersistance, const float pLacunarity);
#pragma endregion


#pragma region SimplexNoise
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static float SimplexNoise1D(float pX);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static float SimplexNoise2D(float pX, float pY);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static float SimplexNoise3D(float pX, float pY, float pZ);

	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static float FbmSimplexNoise1D(float pX, int32 pOctaves, float pPersistance, float pLacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static float FbmSimplexNoise2D(float pX, float pY, int32 pOctaves, float pPersistance, float pLacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static float FbmSimplexNoise3D(float pX, float pY, float pZ, int32 pOctaves, float pPersistance, float pLacunarity);

	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static TArray<float> FbmMapSimplexNoise1D(const int32 pMapWidth, const FVector& pOrigin, const int32 pOctaves, const float pPersistance, const float pLacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static TArray<float> FbmMapSimplexNoise2D(const int32 pMapWidth, const int32 pMapHeight, const FVector& pOrigin, const int32 pOctaves, const float pPersistance, const float pLacunarity);
	UFUNCTION(BlueprintCallable, Category = "ProceduralGeneration|SimplexNoise")
	static TArray<float> FbmMapSimplexNoise3D(const int32 pMapWidth, const int32 pMapHeight, const int32 pMapDepth, const FVector& pOrigin, const int32 pOctaves, const float pPersistance, const float pLacunarity);
#pragma endregion
};
