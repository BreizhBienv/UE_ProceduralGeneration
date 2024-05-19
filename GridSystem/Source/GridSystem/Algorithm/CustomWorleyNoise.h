// Fill out your copyright notice in the Description page of Project Settings.

#ifndef WORLEYNOISE
#define WORLEYNOISE

/*
* Sources used:
* https://thebookofshaders.com/12/
* https://www.youtube.com/watch?v=4066MndcyCk
* 
*/

namespace CustomWorleyNoise
{
	TArray<float> Map(int32 pWidth, int32 pHeight, int32 pPointsNum);
	TArray<float> Map(int32 pWidth, int32 pHeight, int32 pDepth, int32 pPointsNum);
}

#endif