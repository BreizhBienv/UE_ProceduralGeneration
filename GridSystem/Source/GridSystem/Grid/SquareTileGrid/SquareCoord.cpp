// Fill out your copyright notice in the Description page of Project Settings.


#include "SquareCoord.h"

#pragma region Constructor
FSquareCoord::FSquareCoord()
	: _x(0), _z(0)
{
}

FSquareCoord::FSquareCoord(int32 pX, int32 pZ)
	: _x(pX), _z(pZ)
{
}

FSquareCoord::FSquareCoord(const FSquareCoord& pOther)
	: _x(pOther._x), _z(pOther._z)
{
}
#pragma endregion