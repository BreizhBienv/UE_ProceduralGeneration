// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericsEnum.generated.h"

#pragma region EnumToString
template<typename TEnum>
static FORCEINLINE FString GetEnumValueAsString(const FString& Name, TEnum Value)
{
    FString fullName = "/Script/GridSystem." + Name;
    const UEnum* enumPtr = FindObject<UEnum>(nullptr, *fullName, true);
    if (!enumPtr) return FString("Invalid");
    return enumPtr->GetNameByValue((int64)Value).ToString();
}

#define EnumToString(EnumClassName, ValueOfEnum)    \
GetEnumValueAsString<EnumClassName>                 \
(FString(TEXT(#EnumClassName)), (ValueOfEnum))

#pragma endregion

#pragma region TileDirection
UENUM(BlueprintType)
enum class ETileDirection : uint8
{
    N   UMETA(DisplayName = "North"),
    NE  UMETA(DisplayName = "NorthEast"),
    E   UMETA(DisplayName = "East"),
    SE  UMETA(DisplayName = "SouthEast"),
    S   UMETA(DisplayName = "South"),
    SW  UMETA(DisplayName = "SouthWest"),
    W   UMETA(DisplayName = "West"),
    NW  UMETA(DisplayName = "NorthWest"),
};

#define TileDirToString(ValueOfEnum) \
EnumToString(ETileDirection, ValueOfEnum)
#pragma endregion

#pragma region GenerationType
UENUM(BlueprintType)
enum class EProceduralGeneration : uint8
{
    PerlinNoise     UMETA(DisplayName = "PerlinNoise"),
    SimplexNoise    UMETA(DisplayName = "SimplexNoise"),
    Voronoi         UMETA(DisplayName = "Voronoi"),
    MPD             UMETA(DisplayName = "Mid-Point Displacement"),
    Diamond         UMETA(DisplayName = "Diamond-Square"),
    WaveCollapse    UMETA(DisplayName = "WaveFunctionCollapse"),
};

#define ProceduralGenToString(ValueOfEnum) \
EnumToString(EProceduralGeneration, ValueOfEnum)
#pragma endregion