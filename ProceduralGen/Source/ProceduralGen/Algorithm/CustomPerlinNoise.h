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
* https://github.com/keijiro/PerlinNoise/blob/master/Assets/Perlin.cs#L134
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

	float Fractal(float pX, float pScale, int32 pOctaves, float pPersistance, float pLacunarity);
	float Fractal(float pX, float pY, float pScale, int32 pOctaves, float pPersistance, float pLacunarity);
	float Fractal(float pX, float pY, float pZ, float pScale, int32 pOctaves, float pPersistance, float pLacunarity);

	TArray<float> Map(int32 pMapWidth, float pScale, const FVector& pOrigin, int32 pOctaves, float pPersistance, float pLacunarity);
	TArray<float> Map(int32 pMapWidth, int32 pMapHeight, float pScale, const FVector& pOrigin, int32 pOctaves, float pPersistance, float pLacunarity);
	TArray<float> Map(int32 pMapWidth, int32 pMapHeight, int32 pMapDepth, float pScale, const FVector& pOrigin, int32 pOctaves, float pPersistance, float pLacunarity);
}

#endif