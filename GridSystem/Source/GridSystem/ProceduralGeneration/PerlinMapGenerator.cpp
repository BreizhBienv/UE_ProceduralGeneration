// Fill out your copyright notice in the Description page of Project Settings.


#include "PerlinMapGenerator.h"
#include "CustomPerlinNoise.h"
#include "CustomSimplexNoise.h"
#include "CustomWorleyNoise.h"
#include "Engine/Texture2D.h"
#include "Math/Color.h"

APerlinMapGenerator::APerlinMapGenerator()
{
}

void APerlinMapGenerator::BeginPlay()
{
	Super::BeginPlay();
}

void APerlinMapGenerator::DisplayMap()
{
	TArray<float> noiseMap = GetNoiseMap();

	TArray<FColor> colorMap;
	for (int32 x = 0; x < _mapWidth; ++x)
	{
		for (int32 y = 0; y < _mapHeight; ++y)
		{
			int32 color = (int32)((noiseMap[y * _mapWidth + x]) * 255);

			colorMap.Add(FColor(color, color, color));
		}
	}

	_plane->SetActorScale3D(FVector(_mapWidth, _mapHeight, 1));

	// Create custom texture and retrieve raw image data
	UTexture2D* CustomTexture = UTexture2D::CreateTransient(_mapWidth, _mapHeight);
	uint8* RawImageData = static_cast<uint8*>(
		CustomTexture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE));

	for (auto [iColor, iData] = TPair<int32, int32>(0, 0);
		iColor < _mapWidth * _mapHeight;
		++iColor, iData += 4)
	{
		FColor color = colorMap[iColor];

		RawImageData[iData]		= color.B;
		RawImageData[iData + 1] = color.G;
		RawImageData[iData + 2] = color.R;
		RawImageData[iData + 3] = color.A;
	}

	CustomTexture->GetPlatformData()->Mips[0].BulkData.Unlock();
	CustomTexture->UpdateResource();

	TArray<UStaticMeshComponent*> components;
	_plane->GetComponents<UStaticMeshComponent>(components);
	UStaticMeshComponent * mesh = components[0];

	UMaterialInstanceDynamic* DynamicMaterial = 
		mesh->CreateDynamicMaterialInstance(0, mesh->GetMaterial(0));
	DynamicMaterial->SetTextureParameterValue("Texture", CustomTexture);
	mesh->SetMaterial(0, DynamicMaterial);
}

TArray<float> APerlinMapGenerator::GetNoiseMap()
{
	TArray<float> result;

	switch (_generationType)
	{
	case EProceduralGeneration::PerlinNoise:
		result = CustomPerlinNoise::Map(
			_mapWidth, _mapHeight, _scale, GetActorLocation(),
			_octaves, _persistance, _lacunarity);
		break;

	case EProceduralGeneration::SimplexNoise:
		result = CustomSimplexNoise::Map(
			_mapWidth, _mapHeight, _scale, GetActorLocation(),
			_octaves, _persistance, _lacunarity);
		break;

	case EProceduralGeneration::Voronoi:
		result = CustomWorleyNoise::Map(_mapWidth, 5);
		break;

	case EProceduralGeneration::MPD:
		break;

	case EProceduralGeneration::Diamond:
		break;

	case EProceduralGeneration::WaveCollapse:
	default:
		break;
	}

	return result;
}
