// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
*  Sources used:
* https://www.cs.umd.edu/class/spring2018/cmsc425/Lects/lect13-2d-perlin.pdf
* https://en.wikipedia.org/wiki/Perlin_noise
* https://rtouti.github.io/graphics/perlin-noise-algorithm
* Unreal Engine source code: File UnrealMath.cpp & UnrealMath.h
* 
**/
struct GRIDSYSTEM_API CustomPerlinNoise
{

#pragma region SampleGeneration

	//Permutation table of Ken Perlin in his original implementation of the algorithm
	//Table is also toubled to prevent overflow
	static const int32 permutationTable[512];

	/**
	*	Curve w/ derivatives (from 0 to 2) as per Ken Perlin's improved noise paper.
	**/
	static float Fade(float p);

	/**
	*	Compute conversion of hash into gradient direction.
	**/
	static float Grad2D(int32 pHash, float pX, float pY);

	/**
	*	Generates a 2D Perlin noise sample at the given location.
	*	Returns a random value between -1.0 and 1.0 or between 0 and 1.0
	*
	*	@param pX X location where to sample.
	*	@param pY Y location where to sample.
	*	@param pChangeRange Return -1.0 to 1.0 (false), or 0 to 1.0 (true).
	*
	*	@return Perlin noise in the range -1.0 to 1.0 or 0 to 1.0.
	**/
	static float Noise2D(float pX, float pY, bool pChangeRange);

#pragma endregion SampleGeneration

#pragma region NoiseGeneration

	/**
	*	Sources: 
	*	https://www.redblobgames.com/maps/terrain-from-noise/
	*	https://www.youtube.com/playlist?list=PLFt_AvWsXl0eBW2EiBtl_sxmDtSgZBxB3
	* 
	**/

	static int32 xRandRange;
	static int32 yRandRange;

	/**
	* @param 1 & 2: Width and height of the texture in pixels.
	* @param 3 & 4: The origin of the sampled area in the plane.
	* @param 5:     The number of cycles of the basic noise pattern that are repeated over the width and height of the texture.
	**/
	static TArray<TArray<float>> GenerateNoiseMap(
		const int32 pMapWidth, const int32 pMapHeight, const int32 pSeed,  float pScale,
		const int32 pOctaves, const float pPersistance, const float pLacunarity, FVector2f pOffset);

#pragma endregion NoiseGeneration
};
