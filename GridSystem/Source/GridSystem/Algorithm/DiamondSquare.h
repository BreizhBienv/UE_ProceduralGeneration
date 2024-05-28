// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#ifndef DIAMONDSQUARE
#define DIAMONDSQUARE

/*
* Sources used:
*
*/

namespace DiamondSquare
{
	TArray<float> Map(int32 pWidth, int32 pHeight, int32 pPointsNum);
	TArray<float> Map(int32 pWidth, int32 pHeight, int32 pDepth, int32 pPointsNum);
}

#endif