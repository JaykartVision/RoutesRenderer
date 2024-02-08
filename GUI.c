#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "GraphRoutesStruct.h"
#include "MapStruct.h"
#include "GUI.h"

void PrintMapCells(void* map)
{
    printf("\n");
    for (int i = 0; i < SizeCells(map); i++)
    {
        if (*(char*)ReturnTypeCell(map, &i) == '0') printf(" %d ", *(int*)ReturnLevelCell(map, &i));
        else printf("%c%d ", *(char*)ReturnTypeCell(map, &i), *(int*)ReturnLevelCell(map, &i));
        if ((i + 1) % *(int*)ReturnCols(map) == 0) printf("\n");
    }
}

void PrintMapLevelCells(void* map)
{
    printf("\n");
    for (int i = 0; i < SizeCells(map); i++)
    {
        if (*(int*)ReturnLevelCell(map, &i) == -1) printf("  ");
        else printf("%d ", *(int*)ReturnLevelCell(map, &i));
        if ((i + 1) % *(int*)ReturnCols(map) == 0) printf("\n");
    }
}

void PrintMapTypeCells(void* map)
{
    printf("\n");
    for (int i = 0; i < SizeCells(map); i++)
    {
        if (*(char*)ReturnTypeCell(map, &i) == '0') printf("  ");
        else
        {
            if (*(char*)ReturnTypeCell(map, &i) < 28)
            {
                printf("%c ", *(char*)ReturnTypeCell(map, &i) + 224);
            }
            else
            {
                printf("%c ", *(char*)ReturnTypeCell(map, &i));
            }
        }
        if ((i + 1) % *(int*)ReturnCols(map) == 0) printf("\n");
    }
}

void DrawCell(void* map, char road, int pos)
{
    char charRoad[5] = "     ";
    char* typeFile = ".png";
    char* nameFile = "elements/";
    char path[17] = "                 ";
    snprintf(charRoad, sizeof(charRoad), "%d", (int)road);
    snprintf(path, sizeof(path), "%s%s%s", nameFile, &charRoad, typeFile);
    int x = CalcXCoord(map, &pos);
    int y = CalcYCoord(map, &pos);
    SDL_Texture* texture = IMG_LoadTexture(*ReturnRender(map), path);
    SDL_Rect dst = {18*x, 18*y, 18, 18};
    SDL_RenderCopy(*ReturnRender(map), texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}

void PrintMapTypeCellsSDL(void* map)
{
    *ReturnWindow(map) = SDL_CreateWindow("Scene", 50, 50, (*(int*)ReturnCols(map))*18, (*(int*)ReturnRows(map))*18 ,SDL_WINDOW_SHOWN);
    *ReturnRender(map) = SDL_CreateRenderer(*ReturnWindow(map), -1, SDL_RENDERER_ACCELERATED);
    for (int i = 0; i < SizeCells(map); i++)
    {
        char type = *(char*)ReturnTypeCell(map, &i);
        DrawCell(map, type, i);
    }
    SDL_RenderPresent(*ReturnRender(map));
    SDL_Event event;
    char quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }
    SDL_DestroyRenderer(*ReturnRender(map));
    SDL_DestroyWindow(*ReturnWindow(map));
}
void PrintMaxNearestEdge(void* map)
{
    for (int i = 0; i < SizePoints(map); i++)
    {
        printf("Max nearest point %c: %d \n", CalcCharName(ReturnIntNamePointEdge(map, &i)),*(int*)ReturnMaxNearestEdge(map, &i));
    }
}
void PrintPoints(void* map)
{
    for (int i = 0; i < SizeEdges(map); i++)
    {
        printf("Point charName %c numberPoint %d x %d y %d\n", CalcCharName(ReturnIntNamePointEdge(map, &i)), i, CalcXCoord(map, ReturnPosEdge(map, &i)), CalcYCoord(map, ReturnPosEdge(map, &i)));
    }
}

void PrintEdges(void* map)
{
    for (int i = 0; i < SizePoints(map); i++)
    { 
        for (int j = 0; j < SizePoints(map); j++)
        { 
            int* item = ReturnDistanceEdge(map, &i, &j);
            if (item != NULL) 
            { 
                int integ = *item / 100;
                int fract = *item % 100;
                printf("from %c to %c distance %d.%d enabled %c\n", CalcCharName(ReturnIntNamePointEdge(map, &i)), CalcCharName(ReturnIntNamePointEdge(map, &j)), integ, fract, *(char*)ReturnEnabledEdge(map, &i, &j));
            } 
        } 
    } 
}

void PrintGraphRoutes(void* map, void* graphRoutes)
{
    for (int i = 0; i < SizeRoutes(graphRoutes); i++)
    {  
        int integ = *(int*)ReturnDistanceRoute(graphRoutes, &i) / 100;
        int fract = *(int*)ReturnDistanceRoute(graphRoutes, &i) % 100;
        printf("from %c to %c distance %d.%d ", CalcCharName(ReturnIntNamePointEdge(map, ReturnNumberCityPoint(graphRoutes))), CalcCharName(ReturnIntNamePointEdge(map, &i)), integ, fract);
        for (int j = 0; j < SizeStopovers(graphRoutes, &i); j++)
        {
            printf("stopover %c ", CalcCharName(ReturnIntNamePointEdge(map, ReturnStopoverRouteNumber(graphRoutes, &i, &j))));
        }
        printf("\n");
    } 
}

void PrintWaveCells(void* map)
{
    for (int i = 0; i < SizeWaveCells(map); i++)
    {
        printf("%d ", *(int*)Get(((Map1*)map)->waveCells, i));
    }
    printf("\n");
}

void PrintNearestPoints(void* map, int* numberPoint)
{
    printf("From point %c To Points: ", CalcCharName(ReturnIntNamePointEdge(map, numberPoint)));
    for (int i = 0; i < SizeNearestPoints(map, numberPoint); i++)
    {
        printf("%c ", CalcCharName(ReturnIntNamePointEdge(map, ReturnNumberPointNearestPoint(map, &i, numberPoint))));
    }
    printf("\n");
}
void PrintAllNearestPoints(void* map)
{
    for (int i = 0; i < SizePoints(map); i++)
    {
        PrintNearestPoints(map, &i);
    }
}

void PrintText(char* text)
{
    printf("%s\n", text);
}

void EnterChar(char* letter, char* text, char* extraData)
{
    if (extraData != NULL) printf("%s %c\n", text, *extraData);
    else printf("%s\n", text);
    char bufer = '0';
    if (scanf("%c", &bufer) != 1)
    {
        bufer = '0';
    }
    while (getchar() != '\n');
    *letter = bufer;
    printf("\n");
}

void EnterInt(int* digit, char* text, char* extraData)
{
    if (extraData != NULL) printf("%s %c\n", text, *extraData);
    else printf("%s\n", text);
    if (scanf_s("%d", digit) != 1)
    {
        *digit = -2147483647;
    }
    while (getchar() != '\n');
    printf("\n");
}

void EnterString(char* string, char* text)
{
    printf("%s\n", text);
    //while (getchar() != '\n');
    scanf("%s", string);
    printf("\n");
}