#include "RBT.h"
#include "List.h"
#include <SDL2/SDL.h>
#ifndef _MapStruct_H_
#define _MapStruct_H_

typedef struct Cell1
{
	int level;
	char type;
}Cell1;

typedef struct FromEdge
{
	int intNamePoint;
	int pos;
	int maxNearest;
	Tree* ToEdges;
}FromEdge;

typedef struct ToEdge
{
	int distance;
	char enabled;
}ToEdge;

typedef struct Map1
{
	SDL_Window* window;
	SDL_Renderer* render;
	Tree* cells; /*key: int pos, data: char type, int level*/
	Tree* points; /*key: int intNamePoint, data: int numberPoint*/
	List* edges; /*data: int intNamePoint, int pos, int maxNearest, Tree: key: int intNamePoint, data: int distance, char enabled*/
	List* nearestPoints; /*data: List: data: int numberPoint*/
	List* waveCells; /*data: int pos*/
	List* drawEdgeCells; /*data: int pos*/
	List* drawIters; /*data: char iter*/
	int rows;
	int cols;
	int countDiag;
	int countCities;
	char crossRoutes; 
}Map1;

void* InitMap1();

SDL_Window** ReturnWindow(Map1* map);
SDL_Renderer** ReturnRender(Map1* map);
void* ReturnTypeCell(Map1* map, int* pos);
void* ReturnLevelCell(Map1* map, int* pos);
void* ReturnNumberPoint(Map1* map, int* intNamePoint);
void* ReturnIntNamePointEdge(Map1* map, int* numberPoint);
void* ReturnPosEdge(Map1* map, int* numberPoint);
void* ReturnMaxNearestEdge(Map1* map, int* numberPoint);
void* ReturnDistanceEdge(Map1* map, int* numberPoint_From, int* numberPoint_To);
void* ReturnEnabledEdge(Map1* map, int* numberPoint_From, int* numberPoint_To);
void* ReturnDistanceToEdge(ToEdge* toEdge);
void* ReturnEnabledToEdge(ToEdge* toEdge);
void* ReturnNumberPointNearestPoint(Map1* map, int* number, int* numberPoint_From);
void* ReturnPosFirstWaveCell(Map1* map);
void* ReturnPosFirstDrawEdgeCell(Map1* map);
void* ReturnIterNextDrawIters(Map1* map);
void* ReturnIterPrevDrawIters(Map1* map);
void* ReturnRows(Map1* map);
void* ReturnCols(Map1* map);
void* ReturnCrossRoutes(Map1* map);
void* ReturnCountDiag(Map1* map);
void* ReturnCountCities(Map1* map);

int CalcIntName(char* charNamePoint);
char CalcCharName(int* intNamePoint);
int CalcPos(Map1* map, int x, int y);
int CalcXCoord(Map1* map, int* pos);
int CalcYCoord(Map1* map, int* pos);

int SizeCells(Map1* map);
int SizePoints(Map1* map);
int SizeEdges(Map1* map);
int SizeEdgesFrom(Map1* map, int* numberPoint_From);
int SizeNearestPoints(Map1* map, int* numberPoint_From);
int SizeWaveCells(Map1* map);
int SizeDrawEdgeCells(Map1* map);
int SizeDrawIters(Map1* map);

void* InsertCell(Map1* map, int pos, char type, int level);
void* InsertPoint(Map1* map, int intNamePoint, int pos);
void* InsertEdge(Map1* map, int* numberPoint_From, int* numberPoint_To, int distance, char enabled);
void* InsertEndNearestPoint(Map1* map, int* numberPoint, int* numberPoint_From);
void* InsertEndWaveCell(Map1* map, int* pos);
void* InsertBeginDrawEdgeCell(Map1* map, int* pos);
void* InsertBeginDrawIters(Map1* map, char* iter);

void RemovePoint(Map1* map, int* numberPoint_Ptr);
void* RemoveEdge(Map1* map, int* numberPoint_From, int* numberPoint_To);
void RemoveFirstWaveCell(Map1* map);
void RemoveFirstDrawEdgeCell(Map1* map);
void RemoveSecondDrawIters(Map1* map);
void RemoveFirstDrawIters(Map1* map);

void ResetLevelCells(Map1* map);
void ResetEnabledEdges(Map1* map);
void ResetToEdges(Map1* map);
void ResetNearestPoints(Map1* map, int* numberPoint_From);
void ResetAllNearestPoints(Map1* map);
void ResetWaveCells(Map1* map);
void ResetDrawEdgeCells(Map1* map);
void ResetDrawIters(Map1* map);

void FreeMap1(Map1* map);

void IterEdges(Map1* map, void* graphRoutes, int* nearest, void(*IterFunc)(void* extraData1, void* extraData2, void* extraData3, void* inputData, void* inputKey));

#endif
