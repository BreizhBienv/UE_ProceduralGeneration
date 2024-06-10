

#include "CellularAutomata.h"

int32 ZeroOrOne(float pNoiseDensity)
{
	float rand = FMath::FRand();
	return rand > pNoiseDensity ? 1 : 0;
}

TArray<float> InitialiseNoiseGrid(int32 pWidth, int32 pHeight, float pNoiseDensity)
{
	TArray<float> grid;

	for (int32 i = 0; i < pWidth * pHeight; ++i)
		grid.Add(ZeroOrOne(pNoiseDensity));

	return grid;
}

bool IsWithinMapBounds(int32 pWidth, int32 pHeight, int32 pX, int32 pY)
{
	return pX >= 0 && pY >= 0 && pX < pWidth && pY < pHeight;
}

int32 NumberOfZeroAroundCoord(int32 pWidth, int32 pHeight, int32 pRow, int32 pCol, bool pFillBorder, const TArray<float>& pGrid)
{
	int32 neighbourZeroCount = 0;
	for (int32 y = pCol - 1; y <= pCol + 1; ++y)
	{
		for (int32 x = pRow - 1; x <= pRow + 1; ++x)
		{
			if (IsWithinMapBounds(pWidth, pHeight, x, y))
			{
				if (x == pRow && y == pCol)
					continue;

				//Get ID based on column major indexing
				if (pGrid[pWidth * y + x] == 0)
					neighbourZeroCount++;

				continue;
			}

			if (pFillBorder)
				return 8;

			neighbourZeroCount++;
		}
	}

	return neighbourZeroCount;
}

TArray<float> CellularAutomata::Map(int32 pWidth, int32 pHeight, float pNoiseDensity, int32 pIterations, int32 pMorphFactor, bool pFillBorder)
{
	if (0.f > pNoiseDensity || pNoiseDensity > 1.f)
	{
		pNoiseDensity = FMath::Clamp(pNoiseDensity, 0.f, 1.f);
		UE_LOG(LogTemp, Error, TEXT("CellularAutomata: NoiseDensity is below 0 or above 1"));
	}
	
	if (pIterations < 0)
	{
		pIterations = 0;
		UE_LOG(LogTemp, Error, TEXT("CellularAutomata: pIteration is below 0"));
	}

	if (0 > pMorphFactor || pMorphFactor > 8)
	{
		pMorphFactor = FMath::Clamp(pMorphFactor, 0, 8);
		UE_LOG(LogTemp, Error, TEXT("CellularAutomata: pMorphFactor is below 0 or above 8"));
	}

	FMath::RandInit(0);

	TArray<float> grid = InitialiseNoiseGrid(pWidth, pHeight, pNoiseDensity);

	for (int32 i = 0; i < pIterations; ++i)
	{
		TArray<float> tempGrid = grid;
		for (int32 y = 0; y < pHeight; ++y)
		{
			for (int32 x = 0; x < pWidth; ++x)
			{
				int32 zeroCount = NumberOfZeroAroundCoord(pWidth, pHeight, x, y, pFillBorder, tempGrid);

				//Get ID based on column major indexing
				grid[pWidth * y + x] = zeroCount > pMorphFactor ? 0 : 1;
			}
		}
	}

	return grid;
}
