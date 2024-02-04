#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "GraphRoutesStruct.h"

int CmpFuncInt2(void* inputKey1, void* inputKey2)
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

void* InitGraphRoutes(int* city, int SizePoints)
{
    GraphRoutes* graphRoutes = NULL;
    while (1)
    {
        graphRoutes = (GraphRoutes*)malloc(sizeof(GraphRoutes));
        if (graphRoutes != NULL)break;
    }
    if (graphRoutes != NULL)
    {
        graphRoutes->routes = (Tree*)BstCreate(CmpFuncInt2, sizeof(DataGraphOutput));
        for (int i = 0; i < SizePoints; i++)
        {
            DataGraphOutput* dataGraphOutput = NULL;
            while (1)
            {
                dataGraphOutput = (DataGraphOutput*)malloc(sizeof(DataGraphOutput));
                if (dataGraphOutput != NULL)break;
            }
            if (dataGraphOutput != NULL)
            {
                dataGraphOutput->stopovers = NULL;
                dataGraphOutput->from = -1;
                dataGraphOutput->visited = '0';
                if (i == *city)
                {
                    dataGraphOutput->distance = 0;
                }
                else
                {
                    dataGraphOutput->distance = 1e9;
                }
                BstInsert(graphRoutes->routes, dataGraphOutput, &i);
            }
        }
        *(int*)ReturnNumberCityPoint(graphRoutes) = *city;
    }
    return graphRoutes;
}

void* ReturnNumberCityPoint(GraphRoutes* graphRoutes)
{
    return &graphRoutes->city;
}
void* ReturnDistanceRoute(GraphRoutes* graphRoutes, int* numberPoint_To)
{
    DataGraphOutput* dataGraphOutput = BstFind(graphRoutes->routes, numberPoint_To);
    if (dataGraphOutput != NULL)
    {
        return &dataGraphOutput->distance;
    }
    else
    {
        return NULL;
    }
}
void* ReturnFromRoute(GraphRoutes* graphRoutes, int* numberPoint_To)
{
    DataGraphOutput* dataGraphOutput = BstFind(graphRoutes->routes, numberPoint_To);
    if (dataGraphOutput != NULL)
    {
        return &dataGraphOutput->from;
    }
    else
    {
        return NULL;
    }
}
void* ReturnVisitedRoute(GraphRoutes* graphRoutes, int* numberPoint_To)
{
    DataGraphOutput* dataGraphOutput = BstFind(graphRoutes->routes, numberPoint_To);
    if (dataGraphOutput != NULL)
    {
        return &dataGraphOutput->visited;
    }
    else
    {
        return NULL;
    }
}

void* ReturnStopoverRouteNumber(GraphRoutes* graphRoutes, int* numberPoint_To, int* number) /*return stopovers*/
{
    DataGraphOutput* dataGraphOutput = BstFind(graphRoutes->routes, numberPoint_To);
    if (dataGraphOutput != NULL)
    {
        int* stopover = Get(dataGraphOutput->stopovers, *number);
        return stopover;
    }
    else
    {
        return NULL;
    }
}

int SizeRoutes(GraphRoutes* graphRoutes)
{
    int size = BstSize(graphRoutes->routes);
    return size;
}

int SizeStopovers(GraphRoutes* graphRoutes, int* numberPoint_To)
{
    DataGraphOutput* dataGraphOutput = BstFind(graphRoutes->routes, numberPoint_To);
    int size = Length(dataGraphOutput->stopovers);
    return size;
}

void InsertStopover(GraphRoutes* graphRoutes, int* numberPoint_To, int* stopover)
{
    DataGraphOutput* dataGraphOutput = NULL;
    dataGraphOutput = BstFind(graphRoutes->routes, numberPoint_To);
    if (dataGraphOutput->stopovers == NULL) dataGraphOutput->stopovers = ListCreate(CmpFuncInt2, sizeof(int));
    Prepend(dataGraphOutput->stopovers, stopover);
}

void FreeGraphRoutes(GraphRoutes* graphRoutes)
{
    for (int i = 0; i < SizeRoutes(graphRoutes); i++)
    {
        DataGraphOutput* dataGraphOutput = BstFind(graphRoutes->routes, &i);
        FreeList(dataGraphOutput->stopovers);
        free(dataGraphOutput->stopovers);
        dataGraphOutput->stopovers = NULL;
    }
    BstDestroy(graphRoutes->routes, NULL);
    free(graphRoutes);
}