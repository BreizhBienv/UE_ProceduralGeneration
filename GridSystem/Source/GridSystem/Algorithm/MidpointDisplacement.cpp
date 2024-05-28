// Fill out your copyright notice in the Description page of Project Settings.


#include "MidpointDisplacement.h"

bool IsSizePowerOf2(int32 pSize)
{
	return pSize > 0 && !((pSize - 1) & (pSize - 2));
}

int32 GetID(int32 pSize, int32 pX, int32 pY)
{
	return pY * pSize + pX;
}

float Jitter(float pValue, float pSpread)
{
	//gives rand between [-Spread, Spread]
	float rand = (pSpread * FMath::FRand() * 2) - pSpread;

	//Do rand * 0.1f to add/remove a value between [-0.1, 0.1]
	return FMath::Clamp(pValue + rand * 0.1f, 0.f, 1.f);
}

int32 Midpoint(int32 A, int32 B)
{
	return (A + B) / 2;
}

float Average(float A, float B)
{
	return (A + B) / 2.f;
}

float Average(float A, float B, float C, float D)
{
	return (A + B + C + D) / 4.f;
}

void DisplaceHeightMap(TArray<float>& pHeightMap, int32 pSize, int32 pLx, int32 pRx, int32 pBy, int32 pTy, float pSpread)
{
	int32 cx = Midpoint(pLx, pRx);
	int32 cy = Midpoint(pBy, pTy);

	//Values
	float vbl = pHeightMap[GetID(pSize, pLx, pBy)];
	float vbr = pHeightMap[GetID(pSize, pRx, pBy)];
	float vtl = pHeightMap[GetID(pSize, pLx, pTy)];
	float vtr = pHeightMap[GetID(pSize, pRx, pTy)];

	float t = Average(vtl, vtr);
	float b = Average(vbl, vbr);
	float l = Average(vtl, vbl);
	float r = Average(vtr, vbr);
	float c = Average(t, b, l, r);

	pHeightMap[GetID(pSize, cx, pBy)]	= Jitter(b, pSpread);
	pHeightMap[GetID(pSize, cx, pTy)]	= Jitter(t, pSpread);
	pHeightMap[GetID(pSize, pLx, cy)]	= Jitter(l, pSpread);
	pHeightMap[GetID(pSize, pRx, cy)]	= Jitter(r, pSpread);
	pHeightMap[GetID(pSize, cx, cy)]	= Jitter(c, pSpread);
}

TArray<float> MidpointDisplacement::Map(int32 pSize, int32 pSeed, float pSpread, float pSpreadFactor)
{
	TArray<float> heightMap;
	heightMap.Init(1, pSize * pSize);

	if (!IsSizePowerOf2(pSize))
	{
		UE_LOG(LogTemp, Error, TEXT("Midpoint Displacement 2D: Map size is not equal to (1 + 2^n)"));
		return heightMap;
	}

	FMath::RandInit(pSeed);

	//Set corners random value between 0 and 1
	heightMap[GetID(pSize, 0, 0)]					= FMath::FRand();
	heightMap[GetID(pSize, 0, pSize - 1)]			= FMath::FRand();
	heightMap[GetID(pSize, pSize - 1, 0)]			= FMath::FRand();
	heightMap[GetID(pSize, pSize - 1, pSize - 1)]	= FMath::FRand();

	float spread = pSpread;

	int32 expo = FMath::Loge(float(pSize - 1)) / FMath::Loge((float)2);
	
	for (int32 i = 0; i < expo; ++i, spread *= pSpreadFactor)
	{
		//process chunk
		int32 chunk = FMath::Pow((float)2, (float)i);
		int32 chunkWidth = (pSize - 1) / chunk;

		for (int32 x = 0; x < chunk; ++x)
		{
			for (int32 y = 0; y < chunk; ++y)
			{
				int32 lx = chunkWidth * x;
				int32 rx = lx + chunkWidth;
				int32 by = chunkWidth * y;
				int32 ty = by + chunkWidth;
				DisplaceHeightMap(heightMap, pSize, lx, rx, by, ty, pSpread);
			}
		}
	}

	return heightMap;
}
