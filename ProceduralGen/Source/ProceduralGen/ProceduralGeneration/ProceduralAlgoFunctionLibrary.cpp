// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralAlgoFunctionLibrary.h"
#include "CustomSimplexNoise.h"
#include "CustomPerlinNoise.h"
#include "CustomWorleyNoise.h"
#include "MidpointDisplacement.h"
#include "CellularAutomata.h"

#include "RHICommandList.h"
#include "Rendering/Texture2DResource.h"

#pragma region Utils

UTexture2D* UProceduralAlgoFunctionLibrary::TextureFrom2DNoiseMap(int32 MapWidth, int32 MapHeight, const TArray<float>& NoiseMap)
{
    //initialize texture
    uint32 totalPixels = MapWidth * MapHeight;
    uint32 dataSize = totalPixels * 4;
    uint32 srcPitch = MapWidth * 4; //Why not SQRT(totalPixels) ?

    uint8* textureData = new uint8[dataSize];

    UTexture2D* dynamicTexture = UTexture2D::CreateTransient(MapWidth, MapHeight);
    dynamicTexture->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
    dynamicTexture->SRGB = 1;
    dynamicTexture->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
    dynamicTexture->Filter = TextureFilter::TF_Nearest;
    dynamicTexture->AddToRoot();
    dynamicTexture->UpdateResource();

    FUpdateTextureRegion2D* textureRegion = new FUpdateTextureRegion2D(0, 0, 0, 0, MapWidth, MapHeight);

    for (uint32 i = 0; i < totalPixels; i++)
    {
        textureData[i * 4]      = NoiseMap[i] * 255;
        textureData[i * 4 + 1]  = NoiseMap[i] * 255;
        textureData[i * 4 + 2]  = NoiseMap[i] * 255;
        textureData[i * 4 + 3]  = NoiseMap[i] * 255;
    }

    dynamicTexture->UpdateTextureRegions(0, 1, textureRegion, srcPitch, 4, textureData);

    return dynamicTexture;
}

TArray<float> UProceduralAlgoFunctionLibrary::RemapArray(const TArray<float>& Array, const FVector2D& Old, const FVector2D& New)
{
    TArray<float> remapped;
    for (float v : Array)
        remapped.Add(FMath::GetMappedRangeValueClamped(Old, New, v));

    return remapped;
}

float InvLerpInt(int32 From, int32 To, int32 V)
{
    return (V - From) / (To - From);
}

TArray<int32> UProceduralAlgoFunctionLibrary::RemapIntArray(const TArray<int32>& Array, int32 OldMin, int32 OldMax, int32 NewMin, int32 NewMax)
{
    TArray<int32> remapped;
    for (int32 v : Array)
    {
        float rel = InvLerpInt(OldMin, OldMax, v);
        remapped.Add(FMath::Lerp(NewMin, NewMax, rel));
    }

    return remapped;
}

#pragma endregion

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

TArray<float> UProceduralAlgoFunctionLibrary::FbmPerlinNoiseMap1D(int32 MapWidth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomPerlinNoise::Map(MapWidth, Scale, Origin, Octaves, Persistance, Lacunarity);
}
TArray<float> UProceduralAlgoFunctionLibrary::FbmPerlinNoiseMap2D(int32 MapWidth, int32 MapHeight, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomPerlinNoise::Map(MapWidth, MapHeight, Scale, Origin, Octaves, Persistance, Lacunarity);
}
TArray<float> UProceduralAlgoFunctionLibrary::FbmPerlinNoiseMap3D(int32 MapWidth, int32 MapHeight, int32 MapDepth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity)
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

TArray<float> UProceduralAlgoFunctionLibrary::FbmSimplexNoiseMap1D(int32 MapWidth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomSimplexNoise::Map(MapWidth, Scale, Origin, Octaves, Persistance, Lacunarity);
}
TArray<float> UProceduralAlgoFunctionLibrary::FbmSimplexNoiseMap2D(int32 MapWidth, int32 MapHeight, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomSimplexNoise::Map(MapWidth, MapHeight, Scale, Origin, Octaves, Persistance, Lacunarity);
}
TArray<float> UProceduralAlgoFunctionLibrary::FbmSimplexNoiseMap3D(int32 MapWidth, int32 MapHeight, int32 MapDepth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomSimplexNoise::Map(MapWidth, MapHeight, MapDepth, Scale, Origin, Octaves, Persistance, Lacunarity);
}


#pragma endregion


#pragma region WorleyNoise

TArray<float> UProceduralAlgoFunctionLibrary::WorleyNoiseMap2D(int32 Width, int32 Height, int32 PointsNumber)
{
	return CustomWorleyNoise::Map(Width, Height, PointsNumber);
}

TArray<float> UProceduralAlgoFunctionLibrary::WorleyNoiseMap3D(int32 Width, int32 Height, int32 Depth, int32 PointsNumber)
{
    return CustomWorleyNoise::Map(Width, Height, Depth, PointsNumber);
}


#pragma endregion

#pragma region MidpointDisplacement

TArray<float> UProceduralAlgoFunctionLibrary::MidpointDisplacementMap2D(int32 Width, float Spread, float SpreadFactor)
{
    return MidpointDisplacement::Map(Width, Spread, SpreadFactor);
}

TArray<float> UProceduralAlgoFunctionLibrary::DiamondSquareMap2D(int32 Width, float Roughness)
{
    return DiamondSquare::Map(Width, Roughness);
}

#pragma endregion

#pragma region CellularAutomata

TArray<float> UProceduralAlgoFunctionLibrary::CellularAutomata(int32 Width, int32 Height, float NoiseDensity, int32 Iterations, int32 MorphFactor, bool FillBorder)
{
    return CellularAutomata::Map(Width, Height, NoiseDensity, Iterations, MorphFactor, FillBorder);
}

#pragma endregion