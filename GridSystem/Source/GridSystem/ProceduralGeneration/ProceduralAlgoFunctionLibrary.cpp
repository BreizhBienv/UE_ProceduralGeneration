// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralAlgoFunctionLibrary.h"
#include "CustomSimplexNoise.h"
#include "CustomPerlinNoise.h"

#pragma region PerlinNoise

float UProceduralAlgoFunctionLibrary::PerlinNoise1D(float X)
{
	return CustomPerlinNoise::PerlinNoise(X);
}
float UProceduralAlgoFunctionLibrary::PerlinNoise2D(float X, float Y)
{
	return CustomPerlinNoise::PerlinNoise(X, Y);
}
float UProceduralAlgoFunctionLibrary::PerlinNoise3D(float X, float Y, float Z)
{
	return CustomPerlinNoise::PerlinNoise(X, Y, Z);
}

float UProceduralAlgoFunctionLibrary::FbmPerlinNoise1D(float X, float Scale, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomPerlinNoise::Fractal(X, Scale, Octaves, Persistance, Lacunarity);
}
float UProceduralAlgoFunctionLibrary::FbmPerlinNoise2D(float X, float Y, float Scale, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomPerlinNoise::Fractal(X, Y, Scale, Octaves, Persistance, Lacunarity);
}
float UProceduralAlgoFunctionLibrary::FbmPerlinNoise3D(float X, float Y, float Z, float Scale, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomPerlinNoise::Fractal(X, Y, Z, Scale, Octaves, Persistance, Lacunarity);
}

TArray<float> UProceduralAlgoFunctionLibrary::FbmMapPerlinNoise1D(int32 MapWidth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomPerlinNoise::Map(MapWidth, Scale, Origin, Octaves, Persistance, Lacunarity);
}
TArray<float> UProceduralAlgoFunctionLibrary::FbmMapPerlinNoise2D(int32 MapWidth, int32 MapHeight, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomPerlinNoise::Map(MapWidth, MapHeight, Scale, Origin, Octaves, Persistance, Lacunarity);
}
TArray<float> UProceduralAlgoFunctionLibrary::FbmMapPerlinNoise3D(int32 MapWidth, int32 MapHeight, int32 MapDepth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomPerlinNoise::Map(MapWidth, MapHeight, MapDepth, Scale, Origin, Octaves, Persistance, Lacunarity);
}

#pragma endregion


#pragma region SimplexNoise

float UProceduralAlgoFunctionLibrary::SimplexNoise1D(float X)
{
	return CustomSimplexNoise::SimplexNoise(X);
}
float UProceduralAlgoFunctionLibrary::SimplexNoise2D(float X, float Y)
{
	return CustomSimplexNoise::SimplexNoise(X, Y);
}
float UProceduralAlgoFunctionLibrary::SimplexNoise3D(float X, float Y, float Z)
{
	return CustomSimplexNoise::SimplexNoise(X, Y, Z);
}

float UProceduralAlgoFunctionLibrary::FbmSimplexNoise1D(float X, float Scale, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomSimplexNoise::Fractal(X, Scale, Octaves, Persistance, Lacunarity);
}
float UProceduralAlgoFunctionLibrary::FbmSimplexNoise2D(float X, float Y, float Scale, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomSimplexNoise::Fractal(X, Y, Scale, Octaves, Persistance, Lacunarity);
}
float UProceduralAlgoFunctionLibrary::FbmSimplexNoise3D(float X, float Y, float Z, float Scale, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomSimplexNoise::Fractal(X, Y, Z, Scale, Octaves, Persistance, Lacunarity);
}

TArray<float> UProceduralAlgoFunctionLibrary::FbmMapSimplexNoise1D(int32 MapWidth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomSimplexNoise::Map(MapWidth, Scale, Origin, Octaves, Persistance, Lacunarity);
}
TArray<float> UProceduralAlgoFunctionLibrary::FbmMapSimplexNoise2D(int32 MapWidth, int32 MapHeight, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomSimplexNoise::Map(MapWidth, MapHeight, Scale, Origin, Octaves, Persistance, Lacunarity);
}
TArray<float> UProceduralAlgoFunctionLibrary::FbmMapSimplexNoise3D(int32 MapWidth, int32 MapHeight, int32 MapDepth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomSimplexNoise::Map(MapWidth, MapHeight, MapDepth, Scale, Origin, Octaves, Persistance, Lacunarity);
}


#pragma endregion
