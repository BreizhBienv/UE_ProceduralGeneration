// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralAlgoFunctionLibrary.h"
#include "CustomSimplexNoise.h"
#include "CustomPerlinNoise.h"

#pragma region SimplexNoise

float UProceduralAlgoFunctionLibrary::SimplexNoise1D(float pX)
{
	return CustomSimplexNoise::SimplexNoise(pX);
}
float UProceduralAlgoFunctionLibrary::SimplexNoise2D(float pX, float pY)
{
	return CustomSimplexNoise::SimplexNoise(pX, pY);
}
float UProceduralAlgoFunctionLibrary::SimplexNoise3D(float pX, float pY, float pZ)
{
	return CustomSimplexNoise::SimplexNoise(pX, pY, pZ);
}

float UProceduralAlgoFunctionLibrary::FbmSimplexNoise1D(float pX, int32 pOctaves, float pPersistance, float pLacunarity)
{
	return CustomSimplexNoise::Fractal(pX, pOctaves, pPersistance, pLacunarity);
}
float UProceduralAlgoFunctionLibrary::FbmSimplexNoise2D(float pX, float pY, int32 pOctaves, float pPersistance, float pLacunarity)
{
	return CustomSimplexNoise::Fractal(pX, pY, pOctaves, pPersistance, pLacunarity);
}
float UProceduralAlgoFunctionLibrary::FbmSimplexNoise3D(float pX, float pY, float pZ, int32 pOctaves, float pPersistance, float pLacunarity)
{
	return CustomSimplexNoise::Fractal(pX, pY, pZ, pOctaves, pPersistance, pLacunarity);
}

TArray<float> UProceduralAlgoFunctionLibrary::FbmMapSimplexNoise1D(const int32 pMapWidth, const FVector& pOrigin, const int32 pOctaves, const float pPersistance, const float pLacunarity)
{
	return CustomSimplexNoise::Map(pMapWidth, pOrigin, pOctaves, pPersistance, pLacunarity);
}
TArray<float> UProceduralAlgoFunctionLibrary::FbmMapSimplexNoise2D(const int32 pMapWidth, const int32 pMapHeight, const FVector& pOrigin, const int32 pOctaves, const float pPersistance, const float pLacunarity)
{
	return CustomSimplexNoise::Map(pMapWidth, pMapHeight, pOrigin, pOctaves, pPersistance, pLacunarity);
}
TArray<float> UProceduralAlgoFunctionLibrary::FbmMapSimplexNoise3D(const int32 pMapWidth, const int32 pMapHeight, const int32 pMapDepth, const FVector& pOrigin, const int32 pOctaves, const float pPersistance, const float pLacunarity)
{
	return CustomSimplexNoise::Map(pMapWidth, pMapHeight, pMapDepth, pOrigin, pOctaves, pPersistance, pLacunarity);
}


#pragma endregion

#pragma region PerlinNoise

float UProceduralAlgoFunctionLibrary::PerlinNoise1D(float pX, float pScale)
{
	return CustomPerlinNoise::PerlinNoise(pX / pScale);
}
float UProceduralAlgoFunctionLibrary::PerlinNoise2D(float pX, float pY, float pScale)
{
	return CustomPerlinNoise::PerlinNoise(pX / pScale, pY / pScale);
}
float UProceduralAlgoFunctionLibrary::PerlinNoise3D(float pX, float pY, float pZ, float pScale)
{
	return CustomPerlinNoise::PerlinNoise(pX / pScale, pY / pScale, pZ / pScale);
}

float UProceduralAlgoFunctionLibrary::FbmPerlinNoise1D(float pX, float pScale, int32 pOctaves, float pPersistance, float pLacunarity)
{
	return CustomPerlinNoise::Fractal(pX, pScale, pOctaves, pPersistance, pLacunarity);
}
float UProceduralAlgoFunctionLibrary::FbmPerlinNoise2D(float pX, float pY, float pScale, int32 pOctaves, float pPersistance, float pLacunarity)
{
	return CustomPerlinNoise::Fractal(pX, pY, pScale, pOctaves, pPersistance, pLacunarity);
}
float UProceduralAlgoFunctionLibrary::FbmPerlinNoise3D(float pX, float pY, float pZ, float pScale, int32 pOctaves, float pPersistance, float pLacunarity)
{
	return CustomPerlinNoise::Fractal(pX, pY, pZ, pScale, pOctaves, pPersistance, pLacunarity);
}

TArray<float> UProceduralAlgoFunctionLibrary::FbmMapSPerlinNoise1D(const int32 pMapWidth, float pScale, const FVector& pOrigin, const int32 pOctaves, const float pPersistance, const float pLacunarity)
{
	return CustomPerlinNoise::Map(pMapWidth, pScale, pOrigin, pOctaves, pPersistance, pLacunarity);
}
TArray<float> UProceduralAlgoFunctionLibrary::FbmMapPerlinNoise2D(const int32 pMapWidth, const int32 pMapHeight, float pScale, const FVector& pOrigin, const int32 pOctaves, const float pPersistance, const float pLacunarity)
{
	return CustomPerlinNoise::Map(pMapWidth, pMapHeight, pScale, pOrigin, pOctaves, pPersistance, pLacunarity);
}
TArray<float> UProceduralAlgoFunctionLibrary::FbmMapPerlinNoise3D(const int32 pMapWidth, const int32 pMapHeight, const int32 pMapDepth, float pScale, const FVector& pOrigin, const int32 pOctaves, const float pPersistance, const float pLacunarity)
{
	return CustomPerlinNoise::Map(pMapWidth, pMapHeight, pMapDepth, pScale, pOrigin, pOctaves, pPersistance, pLacunarity);
}

#pragma endregion