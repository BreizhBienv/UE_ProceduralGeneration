

#pragma once

#ifndef CELLULARAUTOMATAT
#define CELLULARAUTOMATAT

/*
*	Sources:
*	https://www.youtube.com/watch?v=slTEz6555Ts&t=796s
* 
*/
namespace CellularAutomata
{
	TArray<float> Map(int32 pWidth, int32 pHeight, float pNoiseDensity, int32 pIterations, int32 pMorphFactor, bool pFillBorder);
}

#endif