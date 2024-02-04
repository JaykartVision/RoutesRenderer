#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "DijkstraAlgorithm.h"
#include "GraphRoutesStruct.h"
#include "MapStruct.h"

void SearchMinDist(void* extraData1, void* extraData2, void* extraData3, void* inputData, void* inputKey)
{
	if (*(char*)ReturnEnabledToEdge(inputData) == '1')
	{
		if (*(int*)ReturnDistanceRoute(extraData1, ReturnNumberPoint(extraData3, inputKey)) > (*(int*)ReturnDistanceRoute(extraData1, extraData2) + *(int*)ReturnDistanceToEdge(inputData)))
		{
			*(int*)ReturnDistanceRoute(extraData1, ReturnNumberPoint(extraData3, inputKey)) = (*(int*)ReturnDistanceRoute(extraData1, extraData2) + *(int*)ReturnDistanceToEdge(inputData));
			*(int*)ReturnFromRoute(extraData1, ReturnNumberPoint(extraData3, inputKey)) = *(int*)extraData2;
		}
	}
}

void CalcDistRoutes(void* map, void* graphRoutes)
{
	for (int i = 0; i < SizePoints(map); i++)
	{
		int nearest = -1;
		for (int v = 0; v < SizePoints(map); v++)
		{
			if (
				(*(char*)ReturnVisitedRoute(graphRoutes, &v) == '0')
				&&
				(
					(nearest == -1)
					||
					(*(int*)ReturnDistanceRoute(graphRoutes, &nearest) > *(int*)ReturnDistanceRoute(graphRoutes, &v))
					)
				)
			{
				nearest = v;
			}
		}
		if (
			*(int*)ReturnDistanceRoute(graphRoutes, &nearest) == 1e9
			)
		{
			break;
		}
		*(char*)ReturnVisitedRoute(graphRoutes, &nearest) = '1';
		IterEdges(map, graphRoutes, &nearest, SearchMinDist);
	}
	for (int j = 0; j < SizePoints(map); j++)
	{
		if (j != *(int*)ReturnNumberCityPoint(graphRoutes))
		{
			for (int v = *(int*)ReturnFromRoute(graphRoutes, &j); (v != *(int*)ReturnNumberCityPoint(graphRoutes))&&(v != -1); v = *(int*)ReturnFromRoute(graphRoutes, &v))
			{
				InsertStopover(graphRoutes, &j, &v);
			}
		}
	}
}