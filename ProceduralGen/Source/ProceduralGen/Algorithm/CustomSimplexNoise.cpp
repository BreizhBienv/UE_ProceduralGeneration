// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomSimplexNoise.h"

namespace CustomSimplexNoise
{
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
    222, 114,  67,  29,  24,  72, 243, 141, 128, 195,  78,  66, 215,  61, 156, 180,
    };

    int32 FastFloor(float p)
    {
        return p > 0 ? (int32)p : ((int32)p) - 1;
    }

    float Grad(int32 pHash, float pX)
    {
        const int32 h = pHash & 15;
        float grad = 1.0f + (h & 7); // Gradient value 1.0, 2.0, ..., 8.0
        if (h & 8) 
            grad = -grad;	        // Set a random sign for the gradient
        return (grad * pX);			// Multiply the gradient with the distance
    }

    float Grad(int32 pHash, float pX, float pY) {
        const int32 h = pHash & 7;                                      // Convert low 3 bits of hash code
        const float u = h < 4 ? pX : pY;                                // into 8 simple gradient directions,
        const float v = h < 4 ? pY : pX;
        return ((h & 1) ? -u : u) + ((h & 2) ? -2.0f * v : 2.0f * v);   // and compute the dot product with (x,y).
    }

    float Grad(int32 pHash, float pX, float pY, float pZ) {
        int32 h = pHash & 15;									    // Convert low 4 bits of hash code into 12 simple
        float u = h < 8 ? pX : pY;							    // gradient directions, and compute dot product.
        float v = h < 4 ? pY : h == 12 || h == 14 ? pX : pZ;	// Fix repeats at h = 12 to 15
        return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
    }



    float SimplexNoise(float pX)
    {
        float n0, n1;

        int32 i0 = FastFloor(pX);
        int32 i1 = i0 + 1;
        float x0 = pX - i0;
        float x1 = x0 - 1.0f;

        // Calculate the contribution from the first corner
        float t0 = 1.0f - x0 * x0;
        t0 *= t0;
        n0 = t0 * t0 * Grad(perm[i0 & 0xff], x0);

        // Calculate the contribution from the second corner
        float t1 = 1.0f - x1 * x1;
        t1 *= t1;
        n1 = t1 * t1 * Grad(perm[i1 & 0xff], x1);
        // The maximum value of this noise is 8*(3/4)^4 = 2.53125
        // A factor of 0.395 would scale to fit exactly within [-1,1], but
        // we want to match PRMan's 1D noise, so we scale it down some more.
        return 0.25f * (n0 + n1);
    }

    float SimplexNoise(float pX, float pY)
    {
        // Skewing/Unskewing factors for 2D
#define F2 0.366025403f;   //F2 = (sqrt(3) - 1) / 2
#define G2 0.211324865f;   //G2 = (3 - sqrt(3)) / 6   = F2 / (1 + 2 * K)

        //Noise contribution from the three corners.
        float n0, n1, n2;

        //Skew the intput space to determine which simplex we are in.
        float s = (pX + pY) * F2; // Hairy factor for 2D
        int32 i = FastFloor(pX + s);
        int32 j = FastFloor(pY + s);

        // Unskew the cell origin back to (x,y) space
        float t = (float)(i + j) * G2;
        const float X0 = i - t;
        const float Y0 = j - t;

        // The x,y distances from the cell origin
        const float x0 = pX - X0;
        const float y0 = pY - Y0;

        // For the 2D case, the simplex shape is an equilateral triangle.    
        // Determine which simplex we are in
        int32 i1, j1; // Offsets for second (middle) corner of simplex in (i,j) coords
        if (x0 > y0) // lower triangle, XY order: (0,0)->(1,0)->(1,1)
        {
            i1 = 1;
            j1 = 0;
        }
        else // upper triangle, YX order: (0,0)->(0,1)->(1,1)
        {
            i1 = 0;
            j1 = 1;
        }

        /*
            A step of(1, 0) in(i, j) means a step of(1 - c, -c) in(x, y), and
            a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
            c = (3-sqrt(3))/6
         */

        const float x1 = x0 - i1 + G2;            // Offsets for middle corner in (x,y) unskewed coords
        const float y1 = y0 - j1 + G2;
        const float x2 = x0 - 1.0f + 2.0f * G2;   // Offsets for last corner in (x,y) unskewed coords
        const float y2 = y0 - 1.0f + 2.0f * G2;

        // Wrap the integer indices at 256, to avoid indexing perm[] out of bounds
        const int32 ii = i & 0xff;
        const int32 jj = j & 0xff;

        // Calculate the contribution from the first corner
        float t0 = 0.5f - x0 * x0 - y0 * y0;
        if (t0 < 0.0f)
            n0 = 0.0f;
        else
        {
            t0 *= t0;
            n0 = t0 * t0 * Grad(perm[ii + perm[jj]], x0, y0);
        }

        // Calculate the contribution from the second corner
        float t1 = 0.5f - x1 * x1 - y1 * y1;
        if (t1 < 0.0f)
            n1 = 0.0f;
        else
        {
            t1 *= t1;
            n1 = t1 * t1 * Grad(perm[ii + i1 + perm[jj + j1]], x1, y1);
        }

        // Calculate the contribution from the third corner
        float t2 = 0.5f - x2 * x2 - y2 * y2;
        if (t2 < 0.0f)
            n2 = 0.0f;
        else
        {
            t2 *= t2;
            n2 = t2 * t2 * Grad(perm[ii + 1 + perm[jj + 1]], x2, y2);
        }

        // Add contributions from each corner to get the final noise value.
        // The result is scaled to return values in the interval [-1,1].
        return (40.0f / 0.884343445f) * (n0 + n1 + n2);
    }

    float SimplexNoise(float pX, float pY, float pZ)
    {
        // Simple skewing factors for the 3D case
#define F3 0.333333333f
#define G3 0.166666667f

        float n0, n1, n2, n3; // Noise contributions from the four corners

        // Skew the input space to determine which simplex cell we're in
        float s = (pX + pY + pZ) * F3; // Very nice and simple skew factor for 3D
        float xs = pX + s;
        float ys = pY + s;
        float zs = pZ + s;
        int32 i = FastFloor(xs);
        int32 j = FastFloor(ys);
        int32 k = FastFloor(zs);

        float t = (float)(i + j + k) * G3;
        float X0 = i - t; // Unskew the cell origin back to (x,y,z) space
        float Y0 = j - t;
        float Z0 = k - t;
        float x0 = pX - X0; // The x,y,z distances from the cell origin
        float y0 = pY - Y0;
        float z0 = pZ - Z0;

        // For the 3D case, the simplex shape is a slightly irregular tetrahedron.
        // Determine which simplex we are in.
        int32 i1, j1, k1; // Offsets for second corner of simplex in (i,j,k) coords
        int32 i2, j2, k2; // Offsets for third corner of simplex in (i,j,k) coords

        /* This code would benefit from a backport from the GLSL version! */
        if (x0 >= y0) {
            if (y0 >= z0)
            {
                i1 = 1; j1 = 0; k1 = 0; i2 = 1; j2 = 1; k2 = 0;
            } // X Y Z order
            else if (x0 >= z0)
            {
                i1 = 1;
                j1 = 0;
                k1 = 0;
                i2 = 1;
                j2 = 0;
                k2 = 1;
            } // X Z Y order
            else 
            { i1 = 0;
            j1 = 0;
            k1 = 1;
            i2 = 1;
            j2 = 0;
            k2 = 1;
            } // Z X Y order
        }
        else { // x0<y0
            if (y0 < z0) 
            {
                i1 = 0;
                j1 = 0;
                k1 = 1;
                i2 = 0;
                j2 = 1;
                k2 = 1;
            } // Z Y X order
            else if (x0 < z0)
            { 
                i1 = 0;
                j1 = 1;
                k1 = 0;
                i2 = 0;
                j2 = 1;
                k2 = 1;
            } // Y Z X order
            else 
            {
                i1 = 0;
                j1 = 1;
                k1 = 0;
                i2 = 1;
                j2 = 1;
                k2 = 0;
            } // Y X Z order
        }

        // A step of (1,0,0) in (i,j,k) means a step of (1-c,-c,-c) in (x,y,z),
        // a step of (0,1,0) in (i,j,k) means a step of (-c,1-c,-c) in (x,y,z), and
        // a step of (0,0,1) in (i,j,k) means a step of (-c,-c,1-c) in (x,y,z), where
        // c = 1/6.

        float x1 = x0 - i1 + G3; // Offsets for second corner in (x,y,z) coords
        float y1 = y0 - j1 + G3;
        float z1 = z0 - k1 + G3;
        float x2 = x0 - i2 + 2.0f * G3; // Offsets for third corner in (x,y,z) coords
        float y2 = y0 - j2 + 2.0f * G3;
        float z2 = z0 - k2 + 2.0f * G3;
        float x3 = x0 - 1.0f + 3.0f * G3; // Offsets for last corner in (x,y,z) coords
        float y3 = y0 - 1.0f + 3.0f * G3;
        float z3 = z0 - 1.0f + 3.0f * G3;

        // Wrap the integer indices at 256, to avoid indexing perm[] out of bounds
        int32 ii = i & 0xff;
        int32 jj = j & 0xff;
        int32 kk = k & 0xff;

        // Calculate the contribution from the four corners
        float t0 = 0.6f - x0 * x0 - y0 * y0 - z0 * z0;
        if (t0 < 0.0) 
            n0 = 0.0;
        else 
        {
            t0 *= t0;
            n0 = t0 * t0 * Grad(perm[ii + perm[jj + perm[kk]]], x0, y0, z0);
        }

        float t1 = 0.6f - x1 * x1 - y1 * y1 - z1 * z1;
        if (t1 < 0.0) 
            n1 = 0.0;
        else 
        {
            t1 *= t1;
            n1 = t1 * t1 * Grad(perm[ii + i1 + perm[jj + j1 + perm[kk + k1]]], x1, y1, z1);
        }

        float t2 = 0.6f - x2 * x2 - y2 * y2 - z2 * z2;
        if (t2 < 0.0) 
            n2 = 0.0;
        else
        {
            t2 *= t2;
            n2 = t2 * t2 * Grad(perm[ii + i2 + perm[jj + j2 + perm[kk + k2]]], x2, y2, z2);
        }

        float t3 = 0.6f - x3 * x3 - y3 * y3 - z3 * z3;
        if (t3 < 0.0) 
            n3 = 0.0;
        else 
        {
            t3 *= t3;
            n3 = t3 * t3 * Grad(perm[ii + 1 + perm[jj + 1 + perm[kk + 1]]], x3, y3, z3);
        }

        // Add contributions from each corner to get the final noise value.
        // The result is scaled to stay just inside [-1,1]
        return 32.0f * (n0 + n1 + n2 + n3);

    }



    float Fractal(float pX, float pScale, int32 pOctaves, float pPersistance, float pLacunarity)
    {
        if (pScale <= 0)
            pScale = 0.0001f;

        float amplitude = 1.f;
        float frequency = 1.f;

        float output = 0;
        float denom = 0;

        for (int32 i = 0; i < pOctaves; ++i)
        {
            float sampleX = pX / pScale * frequency;

            output += (amplitude * SimplexNoise(sampleX));
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

        float amplitude = 1.f;
        float frequency = 1.f;

        float output = 0;
        float denom = 0;

        for (int32 i = 0; i < pOctaves; ++i)
        {
            float sampleX = pX / pScale * frequency;
            float sampleY = pY / pScale * frequency;

            output += (amplitude * SimplexNoise(sampleX, sampleY));
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

        float amplitude = 1.f;
        float frequency = 1.f;

        float output = 0;
        float denom = 0;

        for (int32 i = 0; i < pOctaves; ++i)
        {
            float sampleX = pX / pScale * frequency;
            float sampleY = pY / pScale * frequency;
            float sampleZ = pZ / pScale * frequency;

            output += (amplitude * SimplexNoise(sampleX, sampleY, sampleZ));
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

        for (float x = pOrigin.X; x < pMapWidth + pOrigin.X; ++x)
            for (float y = pOrigin.Y; y < pMapHeight + pOrigin.Y; ++y)
                noiseMap.Add(Fractal(x, y, pScale, pOctaves, pPersistance, pLacunarity));

        return noiseMap;
    }

    TArray<float> Map(int32 pMapWidth, int32 pMapHeight, int32 pMapDepth, float pScale, const FVector& pOrigin, int32 pOctaves, float pPersistance, float pLacunarity)
    {
        TArray<float> noiseMap;

        for (float z = pOrigin.Z; z < pMapDepth + pOrigin.Z; ++z)
            for (float y = pOrigin.Y; y < pMapHeight + pOrigin.Y; ++y)
                for (float x = pOrigin.X; x < pMapWidth + pOrigin.X; ++x)
                    noiseMap.Add(Fractal(x, y, z, pScale, pOctaves, pPersistance, pLacunarity));

        return noiseMap;
    }
}
