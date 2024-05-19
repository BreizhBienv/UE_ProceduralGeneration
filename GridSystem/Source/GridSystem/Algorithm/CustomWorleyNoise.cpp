// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomWorleyNoise.h"

namespace CustomWorleyNoise
{
	TArray<float> Map(int32 pWidth, int32 pHeight, int32 pPointsNum)
	{
		TArray<FVector2f> points;
		for (int32 i = 0; i < pPointsNum; ++i)
			points.Add(FVector2f(FMath::FRand(), FMath::FRand()));

		TArray<float> noiseMap;
		for (int32 x = 0; x < pWidth; ++x)
		{
			for (int32 y = 0; y < pHeight; ++y)
			{
				FVector2f pixelPos(x, y);
				pixelPos.X /= pWidth;
				pixelPos.Y /= pHeight;

				//Get min distance
				float minDist = MAX_FLT;
				for (int32 i = 0; i < pPointsNum; ++i)
					minDist = FMath::Min(minDist, FVector2f::Distance(pixelPos, points[i]));

				noiseMap.Add(minDist);
			}
		}

		return noiseMap;
	}

	TArray<float> Map(int32 pWidth, int32 pHeight, int32 pDepth, int32 pPointsNum)
	{
		TArray<FVector> points;
		for (int32 i = 0; i < pPointsNum; ++i)
			points.Add(FVector(FMath::FRand(), FMath::FRand(), FMath::FRand()));

		TArray<float> noiseMap;
		for (int32 x = 0; x < pWidth; ++x)
		{
			for (int32 y = 0; y < pHeight; ++y)
			{
				for (int32 z = 0; z < pDepth; ++z)
				{
					FVector pixelPos(x, y, z);
					pixelPos.X /= pWidth;
					pixelPos.Y /= pHeight;
					pixelPos.Z /= pDepth;

					//Get min distance
					float minDist = MAX_FLT;
					for (int32 i = 0; i < pPointsNum; ++i)
						minDist = FMath::Min(minDist, FVector::Distance(pixelPos, points[i]));

					noiseMap.Add(minDist);
				}
			}
		}

		return noiseMap;
	}
}