// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericsEnum.generated.h"

#pragma region EnumToString
template<typename TEnum>
static FORCEINLINE FString GetEnumValueAsString(const FString& Name, TEnum Value)
{
    const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
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
    North           UMETA(DisplayName = "N"),
    NorthEast       UMETA(DisplayName = "NE"),
    East            UMETA(DisplayName = "E"),
    SouthEast       UMETA(DisplayName = "SE"),
    South           UMETA(DisplayName = "S"),
    SouthWest       UMETA(DisplayName = "SW"),
    West            UMETA(DisplayName = "W"),
    NorthWest       UMETA(DisplayName = "NW"),
};

#define TileDirToString(ValueOfEnum) \
EnumToString(ETileDirection, ValueOfEnum)
#pragma endregion