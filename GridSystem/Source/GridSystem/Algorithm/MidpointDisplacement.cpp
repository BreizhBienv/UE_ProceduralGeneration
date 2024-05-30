// Fill out your copyright notice in the Description page of Project Settings.


#include "MidpointDisplacement.h"

/*
* Compute columnMajor
*/
int32 GetID(int32 pWidth, int32 pX, int32 pY)
{
	return pY * pWidth + pX;
}

bool IsSizePowerOf2(int32 pV)
{
	return pV > 0 && !(pV & (pV - 1));
}

float Average(float A, float B)
{
	return (A + B) / 2.f;
}

float Average(float A, float B, float C, float D)
{
	return (A + B + C + D) / 4.f;
}

namespace MidpointDisplacement
{
	int32 Midpoint(int32 A, int32 B)
	{
		return (A + B) / 2;
	}

	float Jitter(float pValue, float pSpread)
	{
		//gives rand between [-Spread, Spread]
		float rand = (pSpread * FMath::FRand() * 2) - pSpread;

		//Do rand * 0.1f to add/remove a value between [-0.1, 0.1]
		return FMath::Clamp(pValue + rand * 0.1f, 0.f, 1.f);
	}

	void DisplaceHeightMap(TArray<float>& pHeightMap, int32 pWidth, int32 pLx, int32 pRx, int32 pBy, int32 pTy, float pSpread)
	{
		int32 cx = Midpoint(pLx, pRx);
		int32 cy = Midpoint(pBy, pTy);

		//Values
		float vbl = pHeightMap[GetID(pWidth, pLx, pBy)];
		float vbr = pHeightMap[GetID(pWidth, pRx, pBy)];
		float vtl = pHeightMap[GetID(pWidth, pLx, pTy)];
		float vtr = pHeightMap[GetID(pWidth, pRx, pTy)];

		float t = Average(vtl, vtr);
		float b = Average(vbl, vbr);
		float l = Average(vtl, vbl);
		float r = Average(vtr, vbr);
		float c = Average(t, b, l, r);

		pHeightMap[GetID(pWidth, cx, pBy)]	= Jitter(b, pSpread);
		pHeightMap[GetID(pWidth, cx, pTy)]	= Jitter(t, pSpread);
		pHeightMap[GetID(pWidth, pLx, cy)]	= Jitter(l, pSpread);
		pHeightMap[GetID(pWidth, pRx, cy)]	= Jitter(r, pSpread);
		pHeightMap[GetID(pWidth, cx, cy)]	= Jitter(c, pSpread);
	}

	TArray<float> Map(int32 pWidth, float pSpread, float pSpreadFactor)
	{
		TArray<float> heightMap;
		heightMap.Init(1, pWidth * pWidth);

		if (!IsSizePowerOf2(pWidth - 1))
		{
			UE_LOG(LogTemp, Error, TEXT("Midpoint Displacement 2D: Map size is not equal to (1 + 2^n)"));
			return heightMap;
		}

		//Set corners random value between 0 and 1
		heightMap[GetID(pWidth, 0, 0)]						= FMath::FRand();
		heightMap[GetID(pWidth, 0, pWidth - 1)]				= FMath::FRand();
		heightMap[GetID(pWidth, pWidth - 1, 0)]				= FMath::FRand();
		heightMap[GetID(pWidth, pWidth - 1, pWidth - 1)]	= FMath::FRand();

		float spread = pSpread;

		int32 expo = FMath::Loge(float(pWidth - 1)) / FMath::Loge((float)2);
	
		for (int32 i = 0; i < expo; ++i, spread *= pSpreadFactor)
		{
			//process chunk
			int32 chunk = FMath::Pow((float)2, (float)i);
			int32 chunkWidth = (pWidth - 1) / chunk;

			for (int32 y = 0; y < chunk; ++y)
			{
				for (int32 x = 0; x < chunk; ++x)
				{
					int32 lx = chunkWidth * x;
					int32 rx = lx + chunkWidth;
					int32 by = chunkWidth * y;
					int32 ty = by + chunkWidth;
					DisplaceHeightMap(heightMap, pWidth, lx, rx, by, ty, pSpread);
				}
			}
		}

		return heightMap;
	}
}

namespace DiamondSquare
{
	void SquareStep(TArray<float>& pHeightMap, int32 pWidth, int32 pChunkSize, float pRoughness)
	{
		int32 halfSide = pChunkSize / 2;

		for (int32 y = 0; y < pWidth - 1; y += pChunkSize)
		{
			for (int32 x = 0; x < pWidth - 1; x += pChunkSize)
			{
				float bl = pHeightMap[GetID(pWidth, x,				y				)];
				float tl = pHeightMap[GetID(pWidth, x,				y + pChunkSize	)];
				float br = pHeightMap[GetID(pWidth, x + pChunkSize,	y				)];
				float tr = pHeightMap[GetID(pWidth, x + pChunkSize, y + pChunkSize	)];

				float avg = Average(bl, br, tl, tr);
				avg += FMath::FRandRange(-pRoughness, pRoughness);

				pHeightMap[GetID(pWidth, x + halfSide, y + halfSide)] = FMath::Clamp(avg, 0.f, 1.f);
			}
		}
	}

	void DiamondStep(TArray<float>& pHeightMap, int32 pWidth, int32 pChunkSize, float pRoughness)
	{
		int32 halfSide = pChunkSize / 2;

		for (int32 y = 0; y < pWidth; y += halfSide)
		{
			for (int32 x = (y + halfSide) % pChunkSize; x < pWidth - 1; x += pChunkSize)
			{
				//float lx = pHeightMap[GetID(pWidth, (x - halfSide + pWidth - 1) % (pWidth - 1), y)];
				//float rx = pHeightMap[GetID(pWidth, (x + halfSide) % (pWidth - 1), y)];
				//float ty = pHeightMap[GetID(pWidth, x, (y + halfSide) % (pWidth - 1))];
				//float by = pHeightMap[GetID(pWidth, x, (y - halfSide + pWidth - 1) % (pWidth - 1))];
				//

				//float avg = Average(by, lx, rx, ty);
				//avg += FMath::FRandRange(-pRoughness, pRoughness);
				//avg = FMath::Clamp(avg, 0.f, 1.f);

				//pHeightMap[GetID(pWidth, x, y)] = avg;

				//// because the values wrap round, the left and right edges are equal, same with top and bottom
				//if (x == 0)
				//	pHeightMap[GetID(pWidth, pWidth - 1, y)] = avg;

				//if (y == 0)
				//	pHeightMap[GetID(pWidth, x, pWidth - 1)] = avg;

				float sum = 0;
				float count = 0;

				if (x - halfSide > 0)
				{
					sum += pHeightMap[GetID(pWidth, x - halfSide, y)];
					count++;
				}

				if (x + halfSide <= pWidth - 1)
				{
					sum += pHeightMap[GetID(pWidth, x + halfSide, y)];
					count++;
				}

				if (y - halfSide > 0)
				{
					sum += pHeightMap[GetID(pWidth, x, y - halfSide)];
					count++;
				}

				if (y + halfSide <= pWidth - 1)
				{
					sum += pHeightMap[GetID(pWidth, x, y + halfSide)];
					count++;
				}

				sum /= count;
				sum += FMath::FRandRange(-pRoughness, pRoughness);
				sum = FMath::Clamp(sum, 0.f, 1.f);
				pHeightMap[GetID(pWidth, x, y)] = sum;
			}
		}
	}

	TArray<float> DiamondSquare::Map(int32 pWidth, float pRoughness)
	{
		TArray<float> heightMap;
		heightMap.Init(1, pWidth * pWidth);

		if (!IsSizePowerOf2(pWidth - 1))
		{
			UE_LOG(LogTemp, Error, TEXT("Midpoint Displacement 2D: Map size is not equal to (1 + 2^n)"));
			return heightMap;
		}

		//Set corners random value between 0 and 1
		heightMap[GetID(pWidth, 0, 0)]						= FMath::FRand();
		heightMap[GetID(pWidth, 0, pWidth - 1)]				= FMath::FRand();
		heightMap[GetID(pWidth, pWidth - 1, 0)]				= FMath::FRand();
		heightMap[GetID(pWidth, pWidth - 1, pWidth - 1)]	= FMath::FRand();

		float roughness = pRoughness;
		float chunkSize = pWidth - 1;

		while (chunkSize > 1)
		{
			SquareStep(heightMap, pWidth, chunkSize, roughness);
			DiamondStep(heightMap, pWidth, chunkSize, roughness);

			roughness = FMath::Max(roughness / 2.f, 0.1f);
			chunkSize /= 2;
		}

		return heightMap;
	}
}