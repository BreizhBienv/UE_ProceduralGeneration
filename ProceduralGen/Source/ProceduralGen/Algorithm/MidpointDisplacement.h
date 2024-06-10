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
	TArray<float> Map(int32 pWidth, float pSpread, float pSpreadFactor);
}


/*
* Sources used:
* https://learn.64bitdragon.com/articles/computer-science/procedural-generation/the-diamond-square-algorithm
* https://www.youtube.com/watch?v=4GuAV1PnurU&t=48s
* https://www.youtube.com/watch?v=qNoSliX_6Gc&t=298s
* https://www.youtube.com/watch?v=bs0BQk2hH6I
*/
namespace DiamondSquare
{
	TArray<float> Map(int32 pWidth, float pRoughness);
}

#endif