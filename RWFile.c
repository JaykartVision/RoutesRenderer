#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "GraphRoutesStruct.h"
#include "MapStruct.h"
#include "RWFile.h"
#include "GUI.h"

void WriteScene(void* map)
{
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;
	char fileName[64];
	EnterString(&fileName, "Enter fileName scene:");
	FILE* file = fopen(fileName, "w");
	int password = 25268;
	fwrite(&password, sizeof(int), 1, file); /*пароль*/
	fwrite(ReturnCountCities(map), sizeof(int), 1, file); /*количество пунктов*/
	fwrite(ReturnCols(map), sizeof(int), 1, file); /*столбцы*/
	fwrite(ReturnRows(map), sizeof(int), 1, file); /*строки*/
	fwrite(ReturnCrossRoutes(map), sizeof(char), 1, file); /*натройка пересечений*/
	for (int j = 1; j < (*(int*)ReturnRows(map) - 1); j++)
	{
		int count = 0;
		char bufer = ' ';
		for (int i = 1; i < (*(int*)ReturnCols(map) - 1); i++)
		{
			int pos = CalcPos(map, i, j);
			if (bufer != *(char*)ReturnTypeCell(map, &pos))
			{
				if (count != 0)
				{
					fwrite(&bufer, sizeof(char), 1, file); /*символ*/
					fwrite(&count, sizeof(int), 1, file); /*количество*/
					count1++;
					count = 0;
				}
				bufer = *(char*)ReturnTypeCell(map, &pos);
				count++;
			}
			else
			{
				count++;
			}
		}
		fwrite(&bufer, sizeof(char), 1, file); /*символ*/
		fwrite(&count, sizeof(int), 1, file); /*количество*/
	}

	//char a = '\n';
	//fwrite(&a, sizeof(char), 1, file);
	fclose(file);
	FILE* file1 = fopen(fileName, "a");
	for (int i = 0; i < SizePoints(map); i++)
	{
		//char iName = ReturnCharName(i);
		//fwrite(&iName, sizeof(char), 1, file);
		int count = SizeEdgesFrom(map, &i);
		//printf("SizeEdgesFrom %d count %d\n", i, count);
		fwrite(&count, sizeof(int), 1, file1);
		for (int j = 0; j < SizePoints(map); j++)
		{
			int* item = (float*)ReturnDistanceEdge(map, &i, &j);
			if (item != NULL)
			{
				//printf("from %c to %c distance %f\n", ReturnCharName(i), ReturnCharName(j), *item);
				char jName = CalcCharName(ReturnIntNamePointEdge(map, &j));
				fwrite(&jName, sizeof(char), 1, file1);
				//fwrite(item, 4, 1, file1);
				fprintf(file1, "%d", *item);
				count2++;
			}
		}
	}
	//fwrite(&a, sizeof(char), 1, file);
	fclose(file1);
	FILE* file2 = fopen(fileName, "a");
	for (int i = 0; i < SizePoints(map); i++)
	{
		int nearestCount = *(int*)ReturnMaxNearestEdge(map, &i);
		fwrite(&nearestCount, sizeof(int), 1, file2);
		count3++;
	}
	//for (int i = 0; i < SizePoints(map); i++)
	//{
	//	printf("i %d nearest %d\n", i, *(int*)ReturnMaxNearestEdge(map, &i));
	//}
	fclose(file2);
	//printf("END");
	//PrintEdges(map);
	//PrintPoints(map);
}

void ReadScene(void* map)
{
	Map1* map1 = map;
	char fileName[64];
	FILE* file = NULL;
	while (1)
	{
		EnterString(&fileName, "Enter fileName scene:");
		fopen_s(&file, fileName, "r");
		if (file != NULL) break;
		else PrintText("The file cannot be opened");
	}
	int password = 0;
	fread(&password, sizeof(int), 1, file);
	if ((!feof(file))&&(password == 25268))
	{
		fread(ReturnCountCities(map), sizeof(int), 1, file);
		fread(ReturnCols(map), sizeof(int), 1, file);
		fread(ReturnRows(map), sizeof(int), 1, file);
		fread(ReturnCrossRoutes(map), sizeof(char), 1, file);
		for (int i = 0; i < *(int*)ReturnCols(map); i++)
		{
			InsertCell(map, CalcPos(map, i, 0), '1', -1);
		}
		for (int j = 1; j < (*(int*)ReturnRows(map) - 1); j++)
		{
			int i = 0;
			while (i < *(int*)ReturnCols(map))
			{
				if ((i == 0) || (i == (*(int*)ReturnCols(map) - 1)))
				{
					InsertCell(map, CalcPos(map, i, j), '1', -1);
					i++;
				}
				else
				{
					char bufer = ' ';
					int count = 0;
					fread(&bufer, sizeof(char), 1, file); /*символ*/
					fread(&count, sizeof(int), 1, file); /*количество*/
					for (int iter = 0; iter < count; iter++)
					{
						if (bufer < 28)
						{
							InsertCell(map, CalcPos(map, i, j), bufer, -1);
						}
						else
						{
							switch (bufer)
							{
							case '1':
							{
								InsertCell(map, CalcPos(map, i, j), '1', -1);
								break;
							}
							case '0':
							{
								InsertCell(map, CalcPos(map, i, j), '0', -1);
								break;
							}
							case '*':
							{
								InsertCell(map, CalcPos(map, i, j), '*', -1);
								break;
							}
							default:
							{
								InsertCell(map, CalcPos(map, i, j), bufer, -1);
								int intNamePoint = CalcIntName(&bufer);
								//PrintMapTypeCells(map);
								InsertPoint(map, intNamePoint, CalcPos(map, i, j));
								//printf("SizeCells %d SizePoints %d SizeEdges %d\n", SizeCells(map), SizePoints(map), SizeEdges(map));
								//PrintEdges(map);
								//PrintPoints(map);
								//printf("DEBUG");
								break;
							}
							}
						}
						i++;
					}
				}
			}
		}
		for (int i = 0; i < *(int*)ReturnCols(map); i++)
		{
			InsertCell(map, CalcPos(map, i, *(int*)ReturnRows(map) - 1), '1', -1);
		}
		//PrintMapTypeCells(map);
		//PrintEdges(map);
		//PrintPoints(map);
		//printf("SizeCells %d SizePoints %d SizeEdges %d\n", SizeCells(map), SizePoints(map), SizeEdges(map));
		for (int i = 0; i < SizePoints(map); i++)
		{
			int count = 0;
			fread(&count, sizeof(int), 1, file);
			for (count; count > 0; count--)
			{
				char jName = ' ';
				fread(&jName, sizeof(char), 1, file);
				int intJName = CalcIntName(&jName);
				int distance = 0;
				//fread(&distance, 4, 1, file);
				fscanf(file, "%d", &distance);
				InsertEdge(map, &i, ReturnNumberPoint(map, &intJName), distance, '1');
				//PrintEdges(map);
				//printf("  \n");
			}
		}
		//PrintMapTypeCells(map);
		//PrintEdges(map);
		//PrintPoints(map);
		//printf("SizeCells %d SizePoints %d SizeEdges %d\n", SizeCells(map), SizePoints(map), SizeEdges(map));
		for (int i = 0; i < SizePoints(map); i++)
		{
			int nearestCount = 0;
			fread(&nearestCount, sizeof(int), 1, file);
			*(int*)ReturnMaxNearestEdge(map, &i) = nearestCount;
		}
		//for (int i = 0; i < SizePoints(map); i++)
		//{
		//	printf("i %d nearest %d\n", i, *(int*)ReturnMaxNearestEdge(map, &i));
		//}
	}
	else
	{
		PrintText("Error read file");
	}
	fclose(file);
	//printf("END");
}