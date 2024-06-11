// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomPerlinNoise.h"

namespace CustomPerlinNoise
{
    //Permutation table of Ken Perlin in his original implementation of the algorithm
    //Table is also doubled to prevent overflow
    const int32 perm[512] = {
        151, 160, 137,  91,  90,  15, 131,  13, 201,  95,  96,  53, 194, 233,   7, 225,
        140,  36, 103,  30,  69, 142,   8,  99,  37, 240,  21,  10,  23, 190,   6, 148,
        247, 120, 234,  75,   0,  26, 197,  62,  94, 252, 219, 203, 117,  35,  11,  32,
         57, 177,  33,  88, 237, 149,  56,  87, 174,  20, 125, 136, 171, 168,  68, 175,
         74, 165,  71, 134, 139,  48,  27, 166,  77, 146, 158, 231,  83, 111, 229, 122,
         60, 211, 133, 230, 220, 105,  92,  41,  55,  46, 245,  40, 244, 102, 143,  54,
         65,  25,  63, 161,   1, 216,  80,  73, 209,  76, 132, 187, 208,  89,  18, 169,
        200, 196, 135, 130, 116, 188, 159,  86, 164, 100, 109, 198, 173, 186,   3,  64,
         52, 217, 226, 250, 124, 123,   5, 202,  38, 147, 118, 126, 255,  82,  85, 212,
        207, 206,  59, 227,  47,  16,  58,  17, 182, 189,  28,  42, 223, 183, 170, 213,
        119, 248, 152,   2,  44, 154, 163,  70, 221, 153, 101, 155, 167,  43, 172,   9,
        129,  22,  39, 253,  19,  98, 108, 110,  79, 113, 224, 232, 178, 185, 112, 104,
        218, 246,  97, 228, 251,  34, 242, 193, 238, 210, 144,  12, 191, 179, 162, 241,
         81,  51, 145, 235, 249,  14, 239, 107,  49, 192, 214,  31, 181, 199, 106, 157,
        184,  84, 204, 176, 115, 121,  50,  45, 127,   4, 150, 254, 138, 236, 205,  93,
        222, 114,  67,  29,  24,  72, 243, 141, 128, 195,  78,  66, 215,  61, 156, 180,

        151, 160, 137,  91,  90,  15, 131,  13, 201,  95,  96,  53, 194, 233,   7, 225,
        140,  36, 103,  30,  69, 142,   8,  99,  37, 240,  21,  10,  23, 190,   6, 148,
        247, 120, 234,  75,   0,  26, 197,  62,  94, 252, 219, 203, 117,  35,  11,  32,
         57, 177,  33,  88, 237, 149,  56,  87, 174,  20, 125, 136, 171, 168,  68, 175,
         74, 165,  71, 134, 139,  48,  27, 166,  77, 146, 158, 231,  83, 111, 229, 122,
         60, 211, 133, 230, 220, 105,  92,  41,  55,  46, 245,  40, 244, 102, 143,  54,
         65,  25,  63, 161,   1, 216,  80,  73, 209,  76, 132, 187, 208,  89,  18, 169,
        200, 196, 135, 130, 116, 188, 159,  86, 164, 100, 109, 198, 173, 186,   3,  64,
         52, 217, 226, 250, 124, 123,   5, 202,  38, 147, 118, 126, 255,  82,  85, 212,
        207, 206,  59, 227,  47,  16,  58,  17, 182, 189,  28,  42, 223, 183, 170, 213,
        119, 248, 152,   2,  44, 154, 163,  70, 221, 153, 101, 155, 167,  43, 172,   9,
        129,  22,  39, 253,  19,  98, 108, 110,  79, 113, 224, 232, 178, 185, 112, 104,
        218, 246,  97, 228, 251,  34, 242, 193, 238, 210, 144,  12, 191, 179, 162, 241,
         81,  51, 145, 235, 249,  14, 239, 107,  49, 192, 214,  31, 181, 199, 106, 157,
        184,  84, 204, 176, 115, 121,  50,  45, 127,   4, 150, 254, 138, 236, 205,  93,
        222, 114,  67,  29,  24,  72, 243, 141, 128, 195,  78,  66, 215,  61, 156, 180
    };

    int32 FastFloor(float p)
    {
        return p > 0 ? (int32)p : ((int32)p) - 1;
    }

    float Fade(float p)
    {
        return p * p * p * (p * (p * 6.f - 15.f) + 10.f);
    }

    float Grad(int32 pHash, float pX)
    {
        // Slicing Perlin's 3D improved noise would give us only scales of -1, 0 and 1; this looks pretty bad so let's use a different sampling
        static const float Grad1Scales[16] = { -8 / 8, -7 / 8, -6 / 8, -5 / 8, -4 / 8, -3 / 8, -2 / 8, -1 / 8, 1 / 8, 2 / 8, 3 / 8, 4 / 8, 5 / 8, 6 / 8, 7 / 8, 8 / 8 };
        return Grad1Scales[pHash & 15] * pX;
    }

    float Grad(int32 pHash, float pX, float pY)
    {
        switch (pHash & 7)
        {
        case 0: return pX;
        case 1: return pX + pY;
        case 2: return pY;
        case 3: return -pX + pY;
        case 4: return -pX;
        case 5: return -pX - pY;
        case 6: return -pY;
        case 7: return pX - pY;
        default:    return 0;
        }
    }

    float Grad(int32 pHash, float pX, float pY, float pZ)
    {
        auto h = pHash & 15;
        auto u = h < 8 ? pX : pY;
        auto v = h < 4 ? pY : (h == 12 || h == 14 ? pX : pZ);
        return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }



    float PerlinNoise(float pX)
    {
        int32 fxi = FastFloor(pX) & 0xff;
        pX -= FastFloor(pX);
        float u = Fade(pX);

        // 2.0 factor to ensure (-1, 1) range
        return 2.f * FMath::Lerp(Grad(perm[fxi], pX), Grad(perm[fxi] + 1.f, pX - 1.f), u);
    }

    float PerlinNoise(float pX, float pY)
    {
        //Find unit cube that contains location
        int32 fxi = FastFloor(pX) & 0xff;
        int32 fyi = FastFloor(pY) & 0xff;

        //Find Relative x, y of location in unit cube
        pX -= FastFloor(pX);
        pY -= FastFloor(pY);

        //Comput fade curve for X and Y
        float u = Fade(pX);
        float v = Fade(pY);

        //Hash coord of the square's corners
        //A = 0, B = 1
        const int32* P = perm;
        int32 AA = P[fxi] + fyi;        //BottomLeft
        int32 AB = AA + 1;              //TopLeft
        int32 BA = P[fxi + 1] + fyi;    //BottomRight
        int32 BB = BA + 1;              //TopRight

        //Blend result of coords hashing
        return FMath::Lerp(
            FMath::Lerp(Grad(P[AA], pX, pY          ),  Grad(P[BA], pX - 1.f, pY        ), u),
            FMath::Lerp(Grad(P[AB], pX, pY - 1.f    ),  Grad(P[BB], pX - 1.f, pY - 1.f  ), u),
            v);
    }

    float PerlinNoise(float pX, float pY, float pZ)
    {
        int32 fxi = FastFloor(pX) & 0xff;
        int32 fyi = FastFloor(pY) & 0xff;
        int32 fzi = FastFloor(pZ) & 0xff;

        pX -= FastFloor(pX);
        pY -= FastFloor(pY);
        pZ -= FastFloor(pZ);

        float u = Fade(pX);
        float v = Fade(pY);
        float w = Fade(pZ);

        const int32* P = perm;
        int32 A = P[fxi] + fyi;
        int32 AA = P[A] + fzi;	int32 AB = P[A + 1] + fzi;

        int32 B = P[fxi + 1] + fyi;
        int32 BA = P[B] + fzi;	int32 BB = P[B + 1] + fzi;

        // Note: range is already approximately -1,1 because of the specific choice of direction vectors for the Grad3 function
        // This analysis (http://digitalfreepen.com/2017/06/20/range-perlin-noise.html) suggests scaling by 1/sqrt(3/4) * 1/maxGradientVectorLen, but the choice of gradient vectors makes this overly conservative
        // Scale factor of .97 is (1.0/the max values of a billion random samples); to be 100% sure about the range I also just Clamp it for now.
        return FMath::Clamp(0.97f *
            FMath::Lerp(
                FMath::Lerp(
                    FMath::Lerp(Grad(P[AA], pX, pY, pZ       ), Grad(P[BA], pX - 1.f, pY, pZ         ), u),
                    FMath::Lerp(Grad(P[AB], pX, pY - 1.f, pZ ), Grad(P[BB], pX - 1.f, pY -  1.f, pZ  ), u),
                    v),
                FMath::Lerp(
                    FMath::Lerp(Grad(P[AA + 1], pX, pY, pZ - 1.f        ), Grad(P[BA + 1], pX - 1.f, pY, pZ - 1.f       ), u),
                    FMath::Lerp(Grad(P[AB + 1], pX, pY - 1.f, pZ - 1.f  ), Grad(P[BB + 1], pX - 1.f, pY - 1.f, pZ - 1.f ), u),
                    v),
                w),
            -1.0f, 1.0f);
    }



    float Fractal(float pX, float pScale, int32 pOctaves, float pPersistance, float pLacunarity)
    {
        if (pScale <= 0)
            pScale = 0.0001f;

        float amplitude = 1;
        float frequency = 1;

        float output = 0;
        float denom = 0;

        for (int32 i = 0; i < pOctaves; ++i)
        {
            float sampleX = pX / pScale * frequency;

            output += amplitude * PerlinNoise(sampleX) * amplitude;
            denom += amplitude;

            amplitude *= pPersistance;
            frequency *= pLacunarity;
        }

        return output / denom;
    }

    float Fractal(float pX, float pY, float pScale, int32 pOctaves, float pPersistance, float pLacunarity)
    {
        if (pScale <= 0)
            pScale = 0.0001f;

        float amplitude = 1;
        float frequency = 1;

        float output = 0;
        float denom = 0;

        for (int32 i = 0; i < pOctaves; ++i)
        {
            float sampleX = pX / pScale * frequency;
            float sampleY = pY / pScale * frequency;

            output += (amplitude * PerlinNoise(sampleX, sampleY));
            denom += amplitude;

            amplitude *= pPersistance;
            frequency *= pLacunarity;
        }

        return output / denom;
    }
    
    float Fractal(float pX, float pY, float pZ, float pScale, int32 pOctaves, float pPersistance, float pLacunarity)
    {
        if (pScale <= 0)
            pScale = 0.0001f;

        float amplitude = 1;
        float frequency = 1;

        float output = 0;
        float denom = 0;

        for (int32 i = 0; i < pOctaves; ++i)
        {
            float sampleX = pX / pScale * frequency;
            float sampleY = pY / pScale * frequency;
            float sampleZ = pZ / pScale * frequency;

            output += (amplitude * PerlinNoise(sampleX, sampleY, sampleZ));
            denom += amplitude;

            amplitude *= pPersistance;
            frequency *= pLacunarity;
        }

        return output / denom;
    }



    TArray<float> Map(int32 pMapWidth, float pScale, const FVector& pOrigin, int32 pOctaves, float pPersistance, float pLacunarity)
    {
        TArray<float> noiseMap;

        for (float x = pOrigin.X; x < pMapWidth + pOrigin.X; ++x)
                noiseMap.Add(Fractal(x, pScale, pOctaves, pPersistance, pLacunarity));

        return noiseMap;
    }

    TArray<float> Map(int32 pMapWidth, int32 pMapHeight, float pScale, const FVector& pOrigin, int32 pOctaves, float pPersistance, float pLacunarity)
    {
        TArray<float> noiseMap;

        for (float y = pOrigin.Y; y < pMapHeight + pOrigin.Y; ++y)
            for (float x = pOrigin.X; x < pMapWidth + pOrigin.X; ++x)
                noiseMap.Add(Fractal(x, y, pScale, pOctaves, pPersistance, pLacunarity));

        return noiseMap;
    }

    TArray<float> Map(int32 pMapWidth, int32 pMapHeight, int32 pMapDepth, float pScale, const FVector& pOrigin, int32 pOctaves, float pPersistance, float pLacunarity)
    {
        TArray<float> noiseMap;

        for (float z = pOrigin.Z; z < pMapHeight + pOrigin.Z; ++z)
            for (float y = pOrigin.Y; y < pMapHeight + pOrigin.Y; ++y)
                for (float x = pOrigin.X; x < pMapWidth + pOrigin.X; ++x)
                    noiseMap.Add(Fractal(x, y, z, pScale, pOctaves, pPersistance, pLacunarity));

        return noiseMap;
    }
}