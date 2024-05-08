// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomWorleyNoise.h"

namespace CustomWorleyNoise
{
	TArray<float> Map(int32 pBounds, int32 pPointsNum)
	{
		TArray<float> noiseMap;

		TArray<FVector2f> points;

		for (int32 i = 0; i < pPointsNum; ++i)
			points.Add(FVector2f(FMath::FRand(), FMath::FRand()));

		for (int32 x = 0; x < pBounds; ++x)
		{
			for (int32 y = 0; y < pBounds; ++y)
			{
				FVector2f pixelPos(x, y);
				pixelPos /= pBounds;
				float minDist = MAX_FLT;

				//Get min distance
				for (int32 i = 0; i < points.Num(); ++i)
					minDist = FMath::Min(minDist, FVector2f::Distance(pixelPos, points[i]));

				noiseMap.Add(minDist);
			}
		}

		return noiseMap;
	}
}