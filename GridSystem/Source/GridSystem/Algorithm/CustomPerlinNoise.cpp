// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPerlinNoise.h"

#pragma region SampleGeneration

const int32 CustomPerlinNoise::permutationTable[512] = {
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

float CustomPerlinNoise::Fade(float p)
{
    return p * p * p * (p * (p * 6.f - 15.f) + 10.f);
}

float CustomPerlinNoise::Grad2D(int32 pHash, float pX, float pY)
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

float CustomPerlinNoise::Noise2D(float pX, float pY, bool pChangeRange)
{
    float xf = FMath::FloorToFloat(pX);
    float yf = FMath::FloorToFloat(pY);

    //Find unit cube that contains location
    int32 xi = (int32)(xf) & 255;
    int32 yi = (int32)(yf) & 255;

    //Find Relative x, y of location in unit cube
    float X = pX - xf;
    float Y = pY - yf;

    float Xm1 = X - 1.f;
    float Ym1 = Y - 1.f;

    //Comput fade curve for X and Y
    float U = Fade(X);
    float V = Fade(Y);

    //Hash coord of the square's corners
    //A = 0, B = 1
    const int32 *P = permutationTable;
    int32 AA = P[xi] + yi;      //BottomLeft
    int32 AB = AA + 1;          //TopLeft
    int32 BA = P[xi + 1] + yi;  //BottomRight
    int32 BB = BA + 1;          //TopRight

    //Blend result of coords hashing
    float result = FMath::Lerp(
        FMath::Lerp(Grad2D(P[AA], X, Y), Grad2D(P[BA], Xm1, Y), U),
        FMath::Lerp(Grad2D(P[AB], X, Ym1), Grad2D(P[BB], Xm1, Ym1), U),
        V);

    return pChangeRange ? (result + 1.0f) / 2.0f : result;
}
#pragma region SampleGeneration

#pragma region NoiseGeneration

int32 xRandRange = 10000;
int32 yRandRange = 10000;

TArray<TArray<float>> CustomPerlinNoise::GenerateNoiseMap(
    const int32 pMapWidth, const int32 pMapHeight,
    const int32 pSeed, float pScale, const int32 pOctaves,
    const float pPersistance, const float pLacunarity, FVector2f pOffset)
{
    if (pScale <= 0)
        pScale = 0.0001f;

    TArray<float> row;
    row.Init(0, pMapWidth);

    TArray<TArray<float>> noiseMap;
    noiseMap.Init(TArray<float>(row), pMapHeight);

    for (int y = 0; y < pMapHeight; ++y)
    {
        for (int x = 0; x < pMapWidth; ++x)
        {
            float sampleX = x / pScale;
            float sampleY = y / pScale;

            float perlinValue = Noise2D(sampleX, sampleY, true);
            noiseMap[x][y] = perlinValue;
        }
    }

    return noiseMap;
}

#pragma endregion NoiseGeneration