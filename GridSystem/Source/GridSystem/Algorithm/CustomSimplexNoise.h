// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *  Sources Used: 
 *	https://www.researchgate.net/publication/216813608_Simplex_noise_demystified
 *	https://github.com/SRombauts/SimplexNoise/tree/master
 *	https://redirect.cs.umbc.edu/~olano/s2002c36/ch02.pdf
 */


namespace CustomSimplexNoise
{
	float Noise2D(float pX, float pY);

	float Fractal(float pX, float pY, float pScale, 
		int32 pOctaves, float pPersistance, float pLacunarity);

	TArray<float> Map(const int32 pMapWidth, const int32 pMapHeight, float pScale,
		const FVector& pOrigin, const int32 pOctaves, const float pPersistance,
		const float pLacunarity);
}