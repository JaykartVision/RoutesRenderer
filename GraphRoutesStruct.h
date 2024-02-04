#include "RBT.h"
#include "List.h"
#ifndef _GraphRoutesStruct_H_
#define _GraphRoutesStruct_H_

typedef struct DataGraphOutput
{
	List* stopovers;
	int distance;
	int from;
	char visited;
}DataGraphOutput;

typedef struct GraphRoutes
{
	int city;
	Tree* routes;
}GraphRoutes;

void* InitGraphRoutes(int* city, int SizePoints);

void* ReturnNumberCityPoint(GraphRoutes* graphRoutes);
void* ReturnDistanceRoute(GraphRoutes* graphRoutes, int* numberPoint_To); /*return unsigned int distance*/
void* ReturnFromRoute(GraphRoutes* graphRoutes, int* numberPoint_To); /*return int from*/
void* ReturnVisitedRoute(GraphRoutes* graphRoutes, int* numberPoint_To); /*return char visited*/
void* ReturnStopoverRouteNumber(GraphRoutes* graphRoutes, int* numberPoint_To, int* number); /*return stopovers*/

int SizeRoutes(GraphRoutes* graphRoutes);
int SizeStopovers(GraphRoutes* graphRoutes, int* numberPoint_To);

void InsertStopover(GraphRoutes* graphRoutes, int* numberPoint_To, int* stopover);

void FreeGraphRoutes(GraphRoutes* graphRoutes);

#endif
