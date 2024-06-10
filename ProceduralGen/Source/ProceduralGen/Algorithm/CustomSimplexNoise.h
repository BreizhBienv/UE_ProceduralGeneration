// Fill out your copyright notice in the Description page of Project Settings.

#ifndef SIMPLEXNOISE
#define SIMPLEXNOISE

#pragma once

/**
 *  Sources Used: 
 *	https://www.researchgate.net/publication/216813608_Simplex_noise_demystified
 *	https://github.com/SRombauts/SimplexNoise/tree/master
 *	https://redirect.cs.umbc.edu/~olano/s2002c36/ch02.pdf
 *	https://github.com/devdad/SimplexNoise/tree/master
 */

/*
*	Due to the patent on Ken Perlin's Simplex Noise, I recommend using OpenSimplexNoise.
*	This project is purely R&D.
*/

namespace CustomSimplexNoise
{
	float SimplexNoise(float pX);
	float SimplexNoise(float pX, float pY);
	float SimplexNoise(float pX, float pY, float pZ);

	float Fractal(float pX, float pScale, int32 pOctaves, float pPersistance, float pLacunarity);
	float Fractal(float pX, float pY, float pScale, int32 pOctaves, float pPersistance, float pLacunarity);
	float Fractal(float pX, float pY, float pZ, float pScale, int32 pOctaves, float pPersistance, float pLacunarity);

	TArray<float> Map(int32 pMapWidth, float pScale, const FVector& pOrigin, int32 pOctaves, float pPersistance, float pLacunarity);
	TArray<float> Map(int32 pMapWidth, int32 pMapHeight, float pScale, const FVector& pOrigin, int32 pOctaves, float pPersistance, float pLacunarity);
	TArray<float> Map(int32 pMapWidth, int32 pMapHeight, int32 pMapDepth, float pScale, const FVector& pOrigin, int32 pOctaves, float pPersistance, float pLacunarity);
}

#endif