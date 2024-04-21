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


namespace CustomSimplexNoise
{
	float SimplexNoise(float pX);
	float SimplexNoise(float pX, float pY);
	float SimplexNoise(float pX, float pY, float pZ);

	float Fractal(float pX, int32 pOctaves, float pPersistance, float pLacunarity);
	float Fractal(float pX, float pY, int32 pOctaves, float pPersistance, float pLacunarity);
	float Fractal(float pX, float pY, float pZ, int32 pOctaves, float pPersistance, float pLacunarity);

	TArray<float> Map(const int32 pMapWidth, const FVector& pOrigin, const int32 pOctaves, const float pPersistance, const float pLacunarity);
	TArray<float> Map(const int32 pMapWidth, const int32 pMapHeight, const FVector& pOrigin, const int32 pOctaves, const float pPersistance, const float pLacunarity);
	TArray<float> Map(const int32 pMapWidth, const int32 pMapHeight, const int32 pMapDepth, const FVector& pOrigin, const int32 pOctaves, const float pPersistance, const float pLacunarity);
}

#endif