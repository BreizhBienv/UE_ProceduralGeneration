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

    float Grad1(int32 pHash, float pX)
    {
        // Slicing Perlin's 3D improved noise would give us only scales of -1, 0 and 1; this looks pretty bad so let's use a different sampling
        static const float Grad1Scales[16] = { -8 / 8, -7 / 8., -6 / 8., -5 / 8., -4 / 8., -3 / 8., -2 / 8., -1 / 8., 1 / 8., 2 / 8., 3 / 8., 4 / 8., 5 / 8., 6 / 8., 7 / 8., 8 / 8 };
        return Grad1Scales[pHash & 15] * pX;
    }

    float Grad2D(int32 pHash, float pX, float pY)
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

    float Grad3(int32 pHash, float pX, float pY, float pZ)
    {
        switch (pHash & 15)
        {
            // 12 cube midpoints
        case 0: return pX + pZ;
        case 1: return pX + pY;
        case 2: return pY + pZ;
        case 3: return -pX + pY;
        case 4: return -pX + pZ;
        case 5: return -pX - pY;
        case 6: return -pY + pZ;
        case 7: return pX - pY;
        case 8: return pX - pZ;
        case 9: return pY - pZ;
        case 10: return -pX - pZ;
        case 11: return -pY - pZ;
            // 4 vertices of regular tetrahedron
        case 12: return pX + pY;
        case 13: return -pX + pY;
        case 14: return -pY + pZ;
        case 15: return -pY - pZ;
            // can't happen
        default: return 0;
        }
    }



    float PerlinNoise(float pX)
    {
        int32 fx = FastFloor(pX);

        int32 xi = fx & 255;

        float X = pX - fx;
        float Xm1 = X - 1.f;

        int32 A = perm[xi];
        int32 B = perm[xi + 1];

        float U = Fade(X);

        // 2.0 factor to ensure (-1, 1) range
        return 2.0f * FMath::Lerp(Grad1(A, X), Grad1(B, Xm1), U);
    }

    float PerlinNoise(float pX, float pY)
    {
        int32 fx = FastFloor(pX);
        int32 fy = FastFloor(pY);

        //Find unit cube that contains location
        int32 xi = fx & 255;
        int32 yi = fy & 255;

        //Find Relative x, y of location in unit cube
        float X = pX - fx;
        float Y = pY - fy;

        float Xm1 = X - 1.f;
        float Ym1 = Y - 1.f;

        //Comput fade curve for X and Y
        float U = Fade(X);
        float V = Fade(Y);

        //Hash coord of the square's corners
        //A = 0, B = 1
        const int32* P = perm;
        int32 AA = P[xi] + yi;      //BottomLeft
        int32 AB = AA + 1;          //TopLeft
        int32 BA = P[xi + 1] + yi;  //BottomRight
        int32 BB = BA + 1;          //TopRight

        //Blend result of coords hashing
        float result = FMath::Lerp(
            FMath::Lerp(Grad2D(P[AA], X, Y), Grad2D(P[BA], Xm1, Y), U),
            FMath::Lerp(Grad2D(P[AB], X, Ym1), Grad2D(P[BB], Xm1, Ym1), U),
            V);

        return result;
    }

    float PerlinNoise(float pX, float pY, float pZ)
    {
        int32 fx = FastFloor(pX);
        int32 fy = FastFloor(pY);
        int32 fz = FastFloor(pZ);

        int32 Xi = fx & 255;
        int32 Yi = fy & 255;
        int32 Zi = fz & 255;

        float X = pX - fx;
        float Y = pY - fy;
        float Z = pZ - fz;

        float Xm1 = X - 1.0f;
        float Ym1 = Y - 1.0f;
        float Zm1 = Z - 1.0f;

        const int32* P = perm;
        int32 A = P[Xi] + Yi;
        int32 AA = P[A] + Zi;	int32 AB = P[A + 1] + Zi;

        int32 B = P[Xi + 1] + Yi;
        int32 BA = P[B] + Zi;	int32 BB = P[B + 1] + Zi;

        float U = Fade(X);
        float V = Fade(Y);
        float W = Fade(Z);

        // Note: range is already approximately -1,1 because of the specific choice of direction vectors for the Grad3 function
        // This analysis (http://digitalfreepen.com/2017/06/20/range-perlin-noise.html) suggests scaling by 1/sqrt(3/4) * 1/maxGradientVectorLen, but the choice of gradient vectors makes this overly conservative
        // Scale factor of .97 is (1.0/the max values of a billion random samples); to be 100% sure about the range I also just Clamp it for now.
        return FMath::Clamp(0.97f *
            FMath::Lerp(FMath::Lerp(FMath::Lerp(Grad3(P[AA], X, Y, Z), Grad3(P[BA], Xm1, Y, Z), U),
                FMath::Lerp(Grad3(P[AB], X, Ym1, Z), Grad3(P[BB], Xm1, Ym1, Z), U),
                V),
                FMath::Lerp(FMath::Lerp(Grad3(P[AA + 1], X, Y, Zm1), Grad3(P[BA + 1], Xm1, Y, Zm1), U),
                    FMath::Lerp(Grad3(P[AB + 1], X, Ym1, Zm1), Grad3(P[BB + 1], Xm1, Ym1, Zm1), U),
                    V),
                W
            ),
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