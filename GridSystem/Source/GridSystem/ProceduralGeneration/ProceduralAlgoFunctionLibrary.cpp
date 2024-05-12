// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralAlgoFunctionLibrary.h"
#include "CustomSimplexNoise.h"
#include "CustomPerlinNoise.h"
#include "CustomWorleyNoise.h"

#include "RHICommandList.h"
#include "Rendering/Texture2DResource.h"

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

    FLinearColor color = FColor::Purple;
    for (uint32 i = 0; i < totalPixels; i++)
    {
        float noise = NoiseMap[i];

        textureData[i * 4]      = noise * 255;
        textureData[i * 4 + 1]  = noise * 255;
        textureData[i * 4 + 2]  = noise * 255;
        textureData[i * 4 + 3]  = noise * 255;
    }

    dynamicTexture->UpdateTextureRegions(0, 1, textureRegion, srcPitch, 4, textureData);

    return dynamicTexture;
}

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

TArray<float> UProceduralAlgoFunctionLibrary::FbmNoiseMapPerlinNoise1D(int32 MapWidth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomPerlinNoise::Map(MapWidth, Scale, Origin, Octaves, Persistance, Lacunarity);
}
TArray<float> UProceduralAlgoFunctionLibrary::FbmNoiseMapPerlinNoise2D(int32 MapWidth, int32 MapHeight, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomPerlinNoise::Map(MapWidth, MapHeight, Scale, Origin, Octaves, Persistance, Lacunarity);
}
TArray<float> UProceduralAlgoFunctionLibrary::FbmNoiseMapPerlinNoise3D(int32 MapWidth, int32 MapHeight, int32 MapDepth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity)
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

TArray<float> UProceduralAlgoFunctionLibrary::FbmNoiseMapSimplexNoise1D(int32 MapWidth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomSimplexNoise::Map(MapWidth, Scale, Origin, Octaves, Persistance, Lacunarity);
}
TArray<float> UProceduralAlgoFunctionLibrary::FbmNoiseMapSimplexNoise2D(int32 MapWidth, int32 MapHeight, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomSimplexNoise::Map(MapWidth, MapHeight, Scale, Origin, Octaves, Persistance, Lacunarity);
}
TArray<float> UProceduralAlgoFunctionLibrary::FbmNoiseMapSimplexNoise3D(int32 MapWidth, int32 MapHeight, int32 MapDepth, float Scale, const FVector& Origin, int32 Octaves, float Persistance, float Lacunarity)
{
	return CustomSimplexNoise::Map(MapWidth, MapHeight, MapDepth, Scale, Origin, Octaves, Persistance, Lacunarity);
}


#pragma endregion


#pragma region WorleyNoise

TArray<float> UProceduralAlgoFunctionLibrary::NoiseMapWorleyNoise2D(int32 Bounds, int32 PointsNumber)
{
	return CustomWorleyNoise::Map(Bounds, PointsNumber);
}

#pragma endregion
