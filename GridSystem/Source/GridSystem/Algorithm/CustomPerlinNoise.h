// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
*  Sources used:
* https://www.cs.umd.edu/class/spring2018/cmsc425/Lects/lect13-2d-perlin.pdf
* https://en.wikipedia.org/wiki/Perlin_noise
* https://rtouti.github.io/graphics/perlin-noise-algorithm
* https://citeseerx.ist.psu.edu/viewdoc/download;jsessionid=82687494240280B461582957FD77C7E8?doi=10.1.1.81.6401&rep=rep1&type=pdf
* Unreal Engine source code: File UnrealMath.cpp & UnrealMath.h
* 
**/
class GRIDSYSTEM_API CustomPerlinNoise
{
	//Permutation table of Ken Perlin in his original implementation of the algorithm
	//Table is also toubled to prevent overflow
	const static int32 permutationTable[512];

	/**
	*	Curve w/ derivative (from 0 to 2) as per Ken Perlin's improved noise paper.
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
};
