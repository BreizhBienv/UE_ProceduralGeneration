// Fill out your copyright notice in the Description page of Project Settings.

#ifndef PERLINNOISE
#define PERLINNOISE

#pragma once

/**
* Sources used:
* https://www.cs.umd.edu/class/spring2018/cmsc425/Lects/lect13-2d-perlin.pdf
* https://en.wikipedia.org/wiki/Perlin_noise
* https://rtouti.github.io/graphics/perlin-noise-algorithm
* https://www.youtube.com/watch?v=kCIaHqb60Cw&t=230s
* Unreal Engine source code: File UnrealMath.cpp & UnrealMath.h
* 
* 
* https://www.redblobgames.com/maps/terrain-from-noise/
* https://www.youtube.com/playlist?list=PLFt_AvWsXl0eBW2EiBtl_sxmDtSgZBxB3
**/

namespace CustomPerlinNoise
{
	float PerlinNoise(float pX);
	float PerlinNoise(float pX, float pY);
	float PerlinNoise(float pX, float pY, float pZ);

	float Fractal(const float pX, float pScale, const int32 pOctaves, const float pPersistance, const float pLacunarity);
	float Fractal(const float pX, const float pY, float pScale, const int32 pOctaves, const float pPersistance, const float pLacunarity);
	float Fractal(const float pX, const float pY, const float pZ, float pScale, const int32 pOctaves, const float pPersistance, const float pLacunarity);

	TArray<float> Map(const int32 pMapWidth, float pScale, const FVector& pOrigin, const int32 pOctaves, const float pPersistance, const float pLacunarity);
	TArray<float> Map(const int32 pMapWidth, const int32 pMapHeight, float pScale, const FVector& pOrigin, const int32 pOctaves, const float pPersistance, const float pLacunarity);
	TArray<float> Map(const int32 pMapWidth, const int32 pMapHeight, const int32 pMapDepth, float pScale, const FVector& pOrigin, const int32 pOctaves, const float pPersistance, const float pLacunarity);
}

#endif