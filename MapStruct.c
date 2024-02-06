#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "MapStruct.h"
//#include "GUI.h"

int CmpFuncInt1(void* inputKey1, void* inputKey2)
{
    int* a = (int*)inputKey1;
    int* b = (int*)inputKey2;
    if (*a == *b)
    {
        return 2;
    }
    else
    {
        if (*a < *b)
            return 1;
        if (*a > *b)
            return 3;
    }
}

void _CompareNumberPoint(void* extraData1, void* extraData2, void* extraData3, void* inputData, void* inputKey);
void _ResetLevelCell(void* extraData1, void* extraData2, void* extraData3, void* inputData, void* inputKey);
void _ResetEnabled(void* extraData1, void* extraData2, void* extraData3, void* inputData, void* inputKey);

void* InitMap1()
{
    Map1* map = NULL;
    while (1)
    {
        map = (Map1*)malloc(sizeof(Map1));
        if (map != NULL)break;
    }
    if (map != NULL)
    {
        map->cells = NULL;
        while (1)
        {
            map->cells = (Tree*)BstCreate(CmpFuncInt1, sizeof(Cell1));
            if (map->cells != NULL)break;
        }
        map->points = NULL;
        while (1)
        {
            map->points = (Tree*)BstCreate(CmpFuncInt1, sizeof(int));
            if (map->points != NULL)break;
        }
        map->edges = NULL;
        while (1)
        {
            map->edges = (List*)ListCreate(CmpFuncInt1, sizeof(FromEdge));
            if (map->edges != NULL)break;
        }
        map->nearestPoints = NULL;
        while (1)
        {
            map->nearestPoints = (List*)ListCreate(CmpFuncInt1, sizeof(void*));
            if (map->nearestPoints != NULL)break;
        }
        map->waveCells = NULL;
        while (1)
        {
            map->waveCells = (List*)ListCreate(CmpFuncInt1, sizeof(int));
            if (map->waveCells != NULL)break;
        }
        map->drawEdgeCells = NULL;
        while (1)
        {
            map->drawEdgeCells = (List*)ListCreate(CmpFuncInt1, sizeof(int));
            if (map->drawEdgeCells != NULL)break;
        }
        map->drawIters = NULL;
        while (1)
        {
            map->drawIters = (List*)ListCreate(CmpFuncInt1, sizeof(char));
            if (map->drawIters != NULL)break;
        }
        map->rows = 0;
        map->cols = 0;
        map->crossRoutes = '0';
        map->countDiag = 0;
        map->countCities = 0;
        //map->window = SDL_CreateWindow("Scene", 30, 30, 800, 800, SDL_WINDOW_SHOWN);
        //map->surface = SDL_GetWindowSurface(map->window);        
        map->window = NULL;
        map->render = NULL;
    }
    return map;
}

SDL_Window** ReturnWindow(Map1* map)
{
    return &map->window;
}
SDL_Renderer** ReturnRender(Map1* map)
{
    return &map->render;
}
void* ReturnTypeCell(Map1* map, int* pos)
{
    Cell1* cell = BstFind(map->cells, pos);
    if (cell != NULL)
    {
        return &cell->type;
    }
    else
    {
        return NULL;
    }
}
void* ReturnLevelCell(Map1* map, int* pos)
{
    Cell1* cell = BstFind(map->cells, pos);
    if (cell != NULL)
    {
        return &cell->level;
    }
    else
    {
        return NULL;
    }
}
void* ReturnNumberPoint(Map1* map, int* intNamePoint)
{
    return BstFind(map->points, intNamePoint);
}
void* ReturnIntNamePointEdge(Map1* map, int* numberPoint)
{
    FromEdge* fromEdge = Get(map->edges, *numberPoint);
    return &fromEdge->intNamePoint;
}
void* ReturnPosEdge(Map1* map, int* numberPoint)
{
    FromEdge* fromEdge = Get(map->edges, *numberPoint);
    return &fromEdge->pos;
}
void* ReturnMaxNearestEdge(Map1* map, int* numberPoint)
{
    FromEdge* fromEdge = Get(map->edges, *numberPoint);
    return &fromEdge->maxNearest;
}
void* ReturnDistanceEdge(Map1* map, int* numberPoint_From, int* numberPoint_To)
{
    FromEdge* fromEdge = Get(map->edges, *numberPoint_From);
    ToEdge* toEdge = BstFind(fromEdge->ToEdges, ReturnIntNamePointEdge(map, numberPoint_To));
    if (toEdge == NULL) return NULL;
    return &toEdge->distance;
}
void* ReturnEnabledEdge(Map1* map, int* numberPoint_From, int* numberPoint_To)
{
    FromEdge* fromEdge = Get(map->edges, *numberPoint_From);
    ToEdge* toEdge = BstFind(fromEdge->ToEdges, ReturnIntNamePointEdge(map, numberPoint_To));
    return &toEdge->enabled;
}
void* ReturnDistanceToEdge(ToEdge* toEdge)
{
    return &toEdge->distance;
}
void* ReturnEnabledToEdge(ToEdge* toEdge)
{
    return &toEdge->enabled;
}
void* ReturnNumberPointNearestPoint(Map1* map, int* number, int* numberPoint_From)
{
    return Get(*(void**)Get(map->nearestPoints, *numberPoint_From), *number);
}
void* ReturnPosFirstWaveCell(Map1* map)
{
    return Get(map->waveCells, 0);
}
void* ReturnPosFirstDrawEdgeCell(Map1* map)
{
    return Get(map->drawEdgeCells, 0);
}
void* ReturnIterNextDrawIters(Map1* map)
{
    return Get(map->drawIters, 0);
}
void* ReturnIterPrevDrawIters(Map1* map)
{
    return Get(map->drawIters, 1);
}
void* ReturnRows(Map1* map)
{
    return &map->rows;
}
void* ReturnCols(Map1* map)
{
    return &map->cols;
}
void* ReturnCrossRoutes(Map1* map)
{
    return &map->crossRoutes;
}
void* ReturnCountDiag(Map1* map)
{
    return &map->countDiag;
}
void* ReturnCountCities(Map1* map)
{
    return &map->countCities;
}

int CalcIntName(char* charNamePoint)
{
    int name = (int)(*charNamePoint) - 97;
    return name;
}
char CalcCharName(int* intNamePoint)
{
    char name = (char)((*intNamePoint) + 97);
    return name;
}
int CalcPos(Map1* map, int x, int y)
{
    int key = y * map->cols + x;
    return key;
}
int CalcXCoord(Map1* map, int* pos)
{
    int x = *pos % map->cols;
    return x;
}
int CalcYCoord(Map1* map, int* pos)
{
    int y = *pos / map->cols;
    return y;
}

int SizeCells(Map1* map)
{
    int size = BstSize(map->cells);
    return size;
}
int SizePoints(Map1* map)
{
    int size = BstSize(map->points);
    return size;
}
int SizeEdges(Map1* map)
{
    int size = Length(map->edges);
    return size;
}
int SizeEdgesFrom(Map1* map, int* numberPoint_From)
{
    FromEdge* fromEdge = Get(map->edges, *numberPoint_From);
    int size = BstSize(fromEdge->ToEdges);
    return size;
}
int SizeNearestPoints(Map1* map, int* numberPoint_From)
{
    int size = Length(*(void**)Get(map->nearestPoints, *numberPoint_From));
    return size;
}
int SizeWaveCells(Map1* map)
{
    int size = Length(map->waveCells);
    return size;
}
int SizeDrawEdgeCells(Map1* map)
{
    int size = Length(map->drawEdgeCells);
    return size;
}
int SizeDrawIters(Map1* map)
{
    int size = Length(map->drawIters);
    return size;
}

void* InsertCell(Map1* map, int pos, char type, int level)
{
    Cell1 cell = { 0, ' '};
    cell.type = type;
    cell.level = level;
    BstInsert(map->cells, &cell, &pos);
}
void* InsertPoint(Map1* map, int intNamePoint, int pos)
{
    Map1* map1 = map;
    int numberPoint = SizePoints(map);
    void * data = BstInsert(map->points, &numberPoint, &intNamePoint);
    FromEdge fromEdge = { 0, 0, 0, NULL };
    fromEdge.intNamePoint = intNamePoint;
    fromEdge.pos = pos;
    fromEdge.ToEdges = BstCreate(CmpFuncInt1, sizeof(ToEdge));
    Append(map->edges, &fromEdge);
    List* nearestList = ListCreate(CmpFuncInt1, sizeof(int));
    Append(map->nearestPoints, &nearestList);
    return data;
}
void* InsertEdge(Map1* map, int* numberPoint_From, int* numberPoint_To, int distance, char enabled)
{
    ToEdge toEdge = {0, '1'};
    toEdge.distance = distance;
    toEdge.enabled = enabled;
    FromEdge* fromEdge = Get(map->edges, *numberPoint_From);
    return BstInsert(fromEdge->ToEdges, &toEdge, ReturnIntNamePointEdge(map, numberPoint_To));
}
void* InsertEndNearestPoint(Map1* map, int* numberPoint, int* numberPoint_From)
{
    Append(*(void**)Get(map->nearestPoints, *numberPoint_From), numberPoint);
}
void* InsertEndWaveCell(Map1* map, int* pos)
{
    Append(map->waveCells, pos);
}
void* InsertBeginDrawEdgeCell(Map1* map, int* pos)
{
    Prepend(map->drawEdgeCells, pos);
}
void* InsertBeginDrawIters(Map1* map, char* iter)
{
    Prepend(map->drawIters, iter);
}

void RemovePoint(Map1* map, int* numberPoint_Ptr)
{
    int numberPoint = *numberPoint_Ptr;
    int intNamePoint = *(int*)ReturnIntNamePointEdge(map, &numberPoint);
    FreeList(*(void**)Get(map->nearestPoints, *numberPoint_Ptr));
    free(*(void**)Get(map->nearestPoints, *numberPoint_Ptr));
    Remove(map->nearestPoints, *numberPoint_Ptr);
    *(char*)ReturnTypeCell(map, ReturnPosEdge(map, numberPoint_Ptr)) = '0';
    FromEdge* fromEdge = NULL;
    for (int i = 0; i < SizeEdges(map); i++)
    {
        fromEdge = Get(map->edges, i);
        BstDelete(fromEdge->ToEdges, ReturnIntNamePointEdge(map, &numberPoint));
    }
    fromEdge = Get(map->edges, numberPoint);
    BstDestroy(fromEdge->ToEdges, NULL);
    fromEdge->ToEdges = NULL;
    BstForeach(map->points, _CompareNumberPoint, &numberPoint, NULL, NULL);
    BstDelete(map->points, &intNamePoint);
    Remove(map->edges, numberPoint);
}
void* RemoveEdge(Map1* map, int* numberPoint_From, int* numberPoint_To)
{
    FromEdge* fromEdge = Get(map->edges, *numberPoint_From);
    return BstDelete(fromEdge->ToEdges, ReturnIntNamePointEdge(map, numberPoint_To));
}
void RemoveFirstWaveCell(Map1* map)
{
    Remove(map->waveCells, 0);
}
void RemoveFirstDrawEdgeCell(Map1* map)
{
    Remove(map->drawEdgeCells, 0);
}
void RemoveSecondDrawIters(Map1* map)
{
    if (Length(map->drawIters) > 1) Remove(map->drawIters, 1);
}
void RemoveFirstDrawIters(Map1* map)
{
    Remove(map->drawIters, 0);
}
void _CompareNumberPoint(void* extraData1, void* extraData2, void* extraData3, void* inputData, void* inputKey)
{
    if (*(int*)inputData > *(int*)extraData1) *(int*)inputData = *(int*)inputData - 1;
}

void ResetLevelCells(Map1* map)
{
    BstForeach(map->cells, _ResetLevelCell, NULL, NULL, NULL);
}
void ResetEnabledEdges(Map1* map)
{
    for (int i = 0; i < SizeEdges(map); i++)
    {
        FromEdge* fromEdge = Get(map->edges, i);
        BstForeach(fromEdge->ToEdges, _ResetEnabled, NULL, NULL, NULL);
    }
}
void ResetToEdges(Map1* map)
{
    for (int i = 0; i < SizeEdges(map); i++)
    {
        FromEdge* fromEdge = Get(map->edges, i);
        BstDestroy(fromEdge->ToEdges, NULL);
        fromEdge->ToEdges = BstCreate(CmpFuncInt1, sizeof(ToEdge));
    }
}
void ResetNearestPoints(Map1* map, int* numberPoint_From)
{
    FreeList(*(void**)Get(map->nearestPoints, *numberPoint_From));
}
void ResetAllNearestPoints(Map1* map)
{
    for (int i = 0; i < SizePoints(map); i++)
    {
        ResetNearestPoints(map, &i);
    }
}
void ResetWaveCells(Map1* map)
{
    FreeList(map->waveCells);
}
void ResetDrawEdgeCells(Map1* map)
{
    FreeList(map->drawEdgeCells);
}
void ResetDrawIters(Map1* map)
{
    FreeList(map->drawIters);
}
void _ResetLevelCell(void* extraData1, void* extraData2, void* extraData3, void* inputData, void* inputKey)
{
    Cell1* cell = (Cell1*)inputData;
    cell->level = -1;
}
void _ResetEnabled(void* extraData1, void* extraData2, void* extraData3, void* inputData, void* inputKey)
{
    ToEdge* toEdge = (ToEdge*)inputData;
    toEdge->enabled = '1';
}

void FreeMap1(Map1* map)
{
    for (int i = 0; i < SizeEdges(map); i++)
    {
        FromEdge* fromEdge = Get(map->edges, i);
        BstDestroy(fromEdge->ToEdges, NULL);
        fromEdge->ToEdges = NULL;
    }
    FreeList(map->edges);
    FreeList(map->drawEdgeCells);
    FreeList(map->waveCells);
    FreeList(map->nearestPoints);
    FreeList(map->drawIters);
    BstDestroy(map->points, NULL);
    BstDestroy(map->cells, NULL);
    //SDL_DestroyWindow(map->window);
    free(map);
}

void IterEdges(Map1* map, void* graphRoutes, int* nearest, void(*IterFunc)(void* extraData1, void* extraData2, void* extraData3, void* inputData, void* inputKey))
{
    FromEdge* fromEdge = Get(map->edges, *nearest);
    BstForeach(fromEdge->ToEdges, IterFunc, graphRoutes, nearest, map);
}