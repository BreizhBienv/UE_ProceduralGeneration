// Fill out your copyright notice in the Description page of Project Settings.


#include "SquareCoord.h"

#pragma region Constructor
FSquareCoord::FSquareCoord()
	: _x(0), _y(0)
{
}

FSquareCoord::FSquareCoord(int32 pX, int32 pY)
	: _x(pX), _y(pY)
{
}

FSquareCoord::FSquareCoord(const FSquareCoord& pOther)
	: _x(pOther._x), _y(pOther._y)
{
}
#pragma endregion