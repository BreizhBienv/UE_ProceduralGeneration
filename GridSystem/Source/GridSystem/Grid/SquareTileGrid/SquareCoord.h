// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericsEnum.h"
#include "SquareCoord.generated.h"

USTRUCT(BlueprintType)
struct GRIDSYSTEM_API FSquareCoord
{
	GENERATED_BODY()

	int32 _x = 0;
	int32 _z = 0;

#pragma region Constructor
	FSquareCoord();

	FSquareCoord(int32 pX, int32 pZ);

	FSquareCoord(const FSquareCoord& pOther);

#pragma endregion

#pragma region Operator
	FSquareCoord& operator=(const FSquareCoord& pOther)
	{
		_x = pOther._x;
		_z = pOther._z;
		return *this;
	}

	bool operator==(const FSquareCoord& pOther)
	{
		return _x == pOther._x && _z == pOther._z;
	}

	bool operator!=(const FSquareCoord& pOther)
	{
		return !(*this == pOther);
	}
#pragma endregion
};

FORCEINLINE uint32 GetTypeHash(const FSquareCoord& pOther)
{
	return FCrc::MemCrc32(&pOther, sizeof(FSquareCoord));
}
