// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#ifndef MIDPOINTDISPLACEMENT
#define MIDPOINTDISPLACEMENT

/*
*	Sources used:
*	https://stevelosh.com/blog/2016/02/midpoint-displacement/
*	https://learn.64bitdragon.com/articles/computer-science/procedural-generation/the-diamond-square-algorithm
*/

namespace MidpointDisplacement
{
	TArray<float> Map(int32 pSize, int32 pSeed, float pSpread, float pSpreadFactor);
}

#endif