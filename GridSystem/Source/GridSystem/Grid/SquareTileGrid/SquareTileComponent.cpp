// Fill out your copyright notice in the Description page of Project Settings.


#include "SquareTileComponent.h"

void USquareTileComponent::SetCoord(const FSquareCoord& pNewCoord)
{
	_coord = pNewCoord;
}

const FSquareCoord& USquareTileComponent::GetCoord()
{
	return _coord;
}
