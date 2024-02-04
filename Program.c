#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Program.h"
#include "GraphRoutesStruct.h"
#include "MapStruct.h"
#include "WaveAlgorithm.h"
#include "DijkstraAlgorithm.h"
#include "GUI.h"
#include "RWFile.h"

void startTest()
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	Map1* map = InitMap1();
	ReadMap1(map);
	//ReadMap(map);
	//printf("SizeCells %d SizePoints %d SizeEdges %d\n", SizeCells(map), SizePoints(map), SizeEdges(map));
	SetMaxNearestPoints(map);
	InsertCrossEdges(map);
	InsertEdgesMap(map);
	PrintMapTypeCells(map);
	PrintMapTypeCellsSDL(map);
	PrintPoints(map);
	PrintEdges(map);
	//DeletePointNoErase(map);
	//InsertCrossEdges(map);
	//ReDrawAllEdges(map);
	//PrintMapTypeCells(map);
	//PrintPoints(map);
	//PrintEdges(map);

	//PrintEdges(map);
	//PrintPoints(map);
	//printf("SizeNearestPoints %d\n", SizeNearestPoints(map));
	//printf("SizeWaveCells %d\n", SizeWaveCells(map));
	//printf("SizeDrawEdgeCells %d\n", SizeDrawEdgeCells(map));



	//SetMaxNearestPoints(map);
	//InsertEdgesMap(map);
	//PrintMapTypeCells(map);
	//PrintEdges(map);
	//printf("SizeNearestPoints %d\n", SizeNearestPoints(map));
	//printf("SizeWaveCells %d\n", SizeWaveCells(map));
	//printf("SizeDrawEdgeCells %d\n", SizeDrawEdgeCells(map));

	//SaveScene(map);
	//LoadScene(map);
	//PrintMapTypeCells(map);
	//PrintEdges(map);
	//PrintPoints(map);
	// 
	//DeletePointNoErase(map);
	//PrintMapTypeCells(map);
	//PrintEdges(map);
	//printf("SizeNearestPoints %d\n", SizeNearestPoints(map));
	//printf("SizeWaveCells %d\n", SizeWaveCells(map));
	//printf("SizeDrawEdgeCells %d\n", SizeDrawEdgeCells(map));

	//ReDrawAllEdges(map);
	//PrintMapTypeCells(map);
	//PrintEdges(map);
	//printf("SizeNearestPoints %d\n", SizeNearestPoints(map));
	//printf("SizeWaveCells %d\n", SizeWaveCells(map));
	//printf("SizeDrawEdgeCells %d\n", SizeDrawEdgeCells(map));

	//SetMaxNearestPoints(map);
	//InsertEdgesMap(map);
	//PrintMapTypeCells(map);
	//PrintEdges(map);
	//printf("SizeNearestPoints %d\n", SizeNearestPoints(map));
	//printf("SizeWaveCells %d\n", SizeWaveCells(map));
	//printf("SizeDrawEdgeCells %d\n", SizeDrawEdgeCells(map));

	//AddPoint(map);
	//AddMaxNearestPoints(map);
	//InsertEdgesMap(map);
	//PrintMapTypeCells(map);
	//PrintEdges(map);
	//printf("SizeNearestPoints %d\n", SizeNearestPoints(map));
	//printf("SizeWaveCells %d\n", SizeWaveCells(map));
	//printf("SizeDrawEdgeCells %d\n", SizeDrawEdgeCells(map));

	//DisableEdgeMap(map);
	//RunAlgDijkstra(map);
	FreeMap1(map);
	SDL_Quit();
	printf("END"); /*DEBUG*/
}

void start()
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	Map1* map = InitMap1();
	int run = 6;
	while (run != 0)
	{
		PrintText(" ");
		PrintText("Type 0 if you want to exit");
		PrintText("Type 1 if you want to read map");
		PrintText("The readmap file.txt should be presented in the form like this:");
		PrintText("1 1 1 1 1 1 1\\n");
		PrintText("1         p 1\\n");
		PrintText("1   a       1\\n");
		PrintText("1       1 1 1\\n");
		PrintText("1 1 1       1\\n");
		PrintText("1   1   k   1\\n");
		PrintText("1           1\\n");
		PrintText("1 1 1 1 1 1 1");
		PrintText("in the case of a size of 6 rows by 5 columns");
		PrintText("where '1' is a wall, ' ' is an empty space");
		PrintText("'char' is the name of the point (names should not be repeated)");
		PrintText("Type 2 if you want to load saved scene");
		PrintText("Type 3 if you want to edit enabled scene");
		PrintText("Type 4 if you want to save enabled scene");
		PrintText("Type 5 if you want to find all the shortest routes from the selected point");
		EnterInt(&run, "Enter the command:", NULL);
		switch (run)
		{
		case 0: /*exit*/
		{
			run = 0;
			break;
		}
		case 1: /*read map*/
		{
			PrintMapTypeCells(map);
			PrintMapTypeCellsSDL(map);
			ReadMap(map);
			SetMaxNearestPoints(map);
			InsertCrossEdges(map);
			InsertEdgesMap(map);
			PrintMapTypeCells(map);
			PrintMapTypeCellsSDL(map);
			PrintPoints(map);
			PrintEdges(map);
			break;
		}
		case 2: /*load*/
		{
			LoadScene(map);
			PrintMapTypeCells(map);
			PrintMapTypeCellsSDL(map);
			PrintPoints(map);
			PrintEdges(map);
			break;
		}
		case 3: /*edit*/
		{
			while (run != 0)
			{
				PrintText("Type 0 if you want to exit");
				PrintText("Type 1 if you want to add point");
				PrintText("Type 2 if you want to delete point");
				EnterInt(&run, "Enter the command:", NULL);
				switch (run)
				{
				case 0: /*exit*/
				{
					run = 0;
					break;
				}
				case 1: /*add point*/
				{
					AddPoint(map);
					while (run != 0)
					{
						PrintText("Type 0 if you want to exit");
						PrintText("Type 1 if you want to redraw all routes");
						PrintText("Type 2 if you want to add routes from added point");
						EnterInt(&run, "Enter the command:", NULL);
						switch (run)
						{
						case 0: /*exit*/
						{
							run = 0;
							break;
						}
						case 1: /*redraw all routes*/
						{
							while (run != 0)
							{
								PrintText("Type 0 if you want to exit");
								PrintText("Type 1 if you want to reenter all nearest points");
								PrintText("Type 2 if you want to redraw all routes");
								EnterInt(&run, "Enter the command:", NULL);
								switch (run)
								{
								case 0: /*exit*/
								{
									run = 0;
									break;
								}
								case 1: /*reenter all nearest points*/
								{
									SetMaxNearestPoints(map);
									break;
								}
								case 2: /*redraw all routes*/
								{
									InsertCrossEdges(map);
									ReDrawAllEdges(map);
									PrintMapTypeCells(map);
									PrintMapTypeCellsSDL(map);
									PrintPoints(map);
									PrintEdges(map);
									run = 0;
									break;
								}
								default:
								{
									run = 6;
									PrintText("Invalid command, please, try again");
									break;
								}
								}
							}
							run = 7;
							break;
						}
						case 2: /*add routes from added point*/
						{
							while (run != 0)
							{
								PrintText("Type 0 if you want to exit");
								PrintText("Type 1 if you want to add all nearest points");
								PrintText("Type 2 if you want to draw routes from added point");
								EnterInt(&run, "Enter the command:", NULL);
								switch (run)
								{
								case 0: /*exit*/
								{
									break;
								}
								case 1: /*add all nearest points*/
								{
									AddMaxNearestPoints(map);
									break;
								}
								case 2: /*draw routes from added point*/
								{
									InsertEdgesMap(map);
									PrintMapTypeCells(map);
									PrintMapTypeCellsSDL(map);
									PrintPoints(map);
									PrintEdges(map);
									run = 0;
									break;
								}
								default:
								{
									run = 6;
									PrintText("Invalid command, please, try again");
									break;
								}
								}
							}
							run = 7;
							break;
						}
						default:
						{
							run = 6;
							PrintText("Invalid command, please, try again");
							break;
						}
						}
					}
					run = 7;
					break;
				}
				case 2: /*delete point*/
				{
					while (run != 0)
					{
						PrintText("Type 0 if you want to exit");
						PrintText("Type 1 if you want to redraw all routes");
						PrintText("Type 2 if you want to erase routes from deleted point (only if CrossEdges = 0)");
						EnterInt(&run, "Enter the command:", NULL);
						switch (run)
						{
						case 0: /*exit*/
						{
							break;
						}
						case 1: /*redraw all routes*/
						{
							while (run != 0)
							{
								PrintText("Type 0 if you want to exit");
								PrintText("Type 1 if you want to reenter all nearest points");
								PrintText("Type 2 if you want to redraw all routes");
								EnterInt(&run, "Enter the command:", NULL);
								switch (run)
								{
								case 0: /*exit*/
								{
									break;
								}
								case 1: /*reenter all nearest points*/
								{
									SetMaxNearestPoints(map);
									break;
								}
								case 2: /*redraw all routes*/
								{
									DeletePointNoErase(map);
									InsertCrossEdges(map);
									ReDrawAllEdges(map);
									PrintMapTypeCells(map);
									PrintMapTypeCellsSDL(map);
									PrintPoints(map);
									PrintEdges(map);
									run = 0;
									break;
								}
								default:
								{
									run = 6;
									PrintText("Invalid command, please, try again");
									break;
								}
								}
							}
							run = 7;
							break;
						}
						case 2: /*erase routes from deleted point*/
						{
							DeletePointFrom(map);
							PrintMapTypeCells(map);
							PrintMapTypeCellsSDL(map);
							PrintPoints(map);
							PrintEdges(map);
							run = 0;
							break;
						}
						default:
						{
							run = 6;
							PrintText("Invalid command, please, try again");
							break;
						}
						}
					}
					run = 7;
					break;
				}
				default:
				{
					run = 6;
					PrintText("Invalid command, please, try again");
					break;
				}
				}
			}
			run = 7;
			break;
		}
		case 4: /*save*/
		{
			SaveScene(map);
			break;
		}
		case 5: /*dijkstra*/
		{
			while (run != 0)
			{
				PrintText("Type 0 if you want to exit");
				PrintText("Type 1 if you want to turn off route");
				PrintText("Type 2 if you want to find all the shortest routes from the selected point");
				EnterInt(&run, "Enter the command:", NULL);
				switch (run)
				{
				case 0: /*exit*/
				{
					ResetEnabledEdges(map);
					break;
				}
				case 1: /*turn off route*/
				{
					DisableEdgeMap(map);
					break;
				}
				case 2: /*find all the shortest routes*/
				{
					RunAlgDijkstra(map);
					ResetEnabledEdges(map);
					break;
				}
				default:
				{
					run = 6;
					PrintText("Invalid command, please, try again");
					break;
				}
				}
			}
			run = 7;
			ResetEnabledEdges(map);
			break;
		}
		default:
		{
			run = 6;
			PrintText("Invalid command, please, try again");
			break;
		}
		}
	}
	FreeMap1(map);
	SDL_Quit();
	printf("END"); /*DEBUG*/
}

void InsertCrossEdges(void* map)
{
	char input = ' ';
	while (1)
	{
		EnterChar(&input, "Enter bool crossEdges:", NULL);
		if ((input == '0') || (input == '1')) break;
		else PrintText("Incorrect input, enter 0 to prohibit route intersections or enter 1 to allow ");
	}
	char* ptr = ReturnCrossRoutes(map);
	*ptr = input;
}

void InsertEdgesMap(void* map)
{
	ResetLevelCells(map);
	ResetNearestPoints(map);
	ResetWaveCells(map);
	ResetDrawEdgeCells(map);
	for (int numberPoint_from = 0; numberPoint_from < SizePoints(map); numberPoint_from++)
	{
		CalcWave(map, ReturnPosEdge(map, &numberPoint_from));
		int countEdges = SizeEdgesFrom(map, &numberPoint_from);
		if (countEdges < *(int*)ReturnMaxNearestEdge(map, &numberPoint_from))
		{
			int numberNearPoint = 0;
			for (countEdges; ((countEdges < *(int*)ReturnMaxNearestEdge(map, &numberPoint_from)) && (numberNearPoint < SizeNearestPoints(map))); )
			{
				void* numberPoint_to = ReturnNumberPointNearestPoint(map, numberNearPoint);
				if ((ReturnDistanceEdge(map, &numberPoint_from, numberPoint_to) == NULL) && (SizeEdgesFrom(map, numberPoint_to) < *(int*)ReturnMaxNearestEdge(map, numberPoint_to)))
				{
					if (*(char*)ReturnCrossRoutes(map) == '0')
					{
						//PrintNearestPoints(map);
						//CalcWave(map, ReturnPosEdge(map, &numberPoint_from));
						CalcWaveCross(map, ReturnPosEdge(map, &numberPoint_from), ReturnPosEdge(map, numberPoint_to));
					}
					//printf("From %c\n", CalcCharName(ReturnIntNamePointEdge(map, &numberPoint_from)));
					//printf("To %c\n", CalcCharName(ReturnIntNamePointEdge(map, numberPoint_to)));
					//PrintMapLevelCells(map);
					//PrintNearestPoints(map);
					DrawEdge(map, ReturnPosEdge(map, &numberPoint_from), ReturnPosEdge(map, numberPoint_to));
					//PrintMapTypeCellsSDL(map);
				}
				numberNearPoint++;
				countEdges = SizeEdgesFrom(map, &numberPoint_from);
			}
		}
		ResetLevelCells(map);
		ResetWaveCells(map);
		ResetDrawEdgeCells(map);
		ResetNearestPoints(map);
	}
}

void RunAlgDijkstra(void* map)
{
	char fromChar = '0';
	while (1)
	{
		char* text = "Enter from point or 0 to exit:";
		EnterChar(&fromChar, text, NULL);
		if (fromChar == '0') break;
		int intNamePoint = CalcIntName(&fromChar);
		if (ReturnNumberPoint(map, &intNamePoint) != NULL)
		{
			int intNameFrom = CalcIntName(&fromChar);
			GraphRoutes* graphRoutes = InitGraphRoutes(ReturnNumberPoint(map, &intNameFrom), SizePoints(map));
			CalcDistRoutes(map, graphRoutes);
			PrintGraphRoutes(map, graphRoutes);
			FreeGraphRoutes(graphRoutes);
		}
		else
		{
			PrintText("Non-existent point");
		}
	}
}

void DisableEdgeMap(void* map)
{
	PrintText(" ");
	char fromChar = '0';
	char toChar = '0';
	while (1)
	{
		PrintText(" ");
		char* text = "Enter from point to disable edge or 0 to exit:";
		EnterChar(&fromChar, text, NULL);
		if (fromChar == '0') return;
		text = "Enter to point to disable edge or 0 to exit:";
		EnterChar(&toChar, text, NULL);
		if (toChar == '0') return;
		int intNameFrom = CalcIntName(&fromChar);
		int intNameTo = CalcIntName(&toChar);
		if (
			(ReturnNumberPoint(map, &intNameFrom) != NULL) 
			&& 
			(ReturnNumberPoint(map, &intNameTo) != NULL)
			)
		{
			if (ReturnDistanceEdge(map, ReturnNumberPoint(map, &intNameFrom), ReturnNumberPoint(map, &intNameTo)) == NULL) printf("No edge\n");
			else *(char*)ReturnEnabledEdge(map, ReturnNumberPoint(map, &intNameFrom), ReturnNumberPoint(map, &intNameTo)) = '0';
			PrintEdges(map);
		}
		else
		{
			PrintText("Incorrect input Point");
		}
	}
}

void SetMaxNearestPoints(void* map)
{
	for (int n = 0; n < SizePoints(map); n++)
	{
		char name = CalcCharName(ReturnIntNamePointEdge(map, &n));
		int set = 0;
		while (1)
		{
			EnterInt(&set, "Enter int maxEdges from point (value must be at least zero):", &name);
			if (set >= 0)
			{
				*(int*)ReturnMaxNearestEdge(map, &n) = set;
				break;
			}
			else
			{
				PrintText("Incorrect input");
			}
		}
	}
}

void AddMaxNearestPoints(void* map)
{
	for (int n = 0; n < SizePoints(map); n++)
	{
		char name = CalcCharName(ReturnIntNamePointEdge(map, &n));
		int add = 0;
		while (1)
		{
			EnterInt(&add, "Add int maxEdges from point:", &name);
			if (add >= 0)
			{
				*(int*)ReturnMaxNearestEdge(map, &n) = *(int*)ReturnMaxNearestEdge(map, &n) + add;
				break;
			}
			else
			{
				PrintText("Int maxEdges to add must be at least zero");
			}
		}
	}
}

void ReadMap(void* map)
{
	FreeMap1(map);
	map = InitMap1();
	PrintText("Enabled scene will be deleted");
	char fileName[64];
	FILE* inputFile = NULL;
	while (1)
	{
		EnterString(&fileName, "Enter fileName:");
		fopen_s(&inputFile, fileName, "r");
		if (inputFile != NULL) break;
		else PrintText("The file cannot be opened");
	}
	char flag = 0;
	int i = 0;
	if (inputFile != NULL)
	{
	    while (!feof(inputFile))
	    {
	        char type = ' ';
	        fscanf_s(inputFile, "%c", &type, 1);
	        if (flag == 0)
	        {
	            flag = 1;
	            switch (type)
	            {
	            case '1':
	            {
					InsertCell(map, CalcPos(map, i, *(int*)ReturnRows(map)), '1', -1);
	                break;
	            }
	            case ' ':
	            {
					InsertCell(map, CalcPos(map, i, *(int*)ReturnRows(map)), '0', -1);
	                break;
	            }
	            default:
	            {
					int intNamePoint = CalcIntName(&type);
					if (ReturnNumberPoint(map, &intNamePoint) == NULL)
					{
						InsertCell(map, CalcPos(map, i, *(int*)ReturnRows(map)), type, -1);
						InsertPoint(map, intNamePoint, CalcPos(map, i, *(int*)ReturnRows(map)));
					}
					else
					{
						PrintText("Incorrect input map");
						FreeMap1(map);
						map = InitMap1();
						return;
					}
	                break;
	            }
	            }
	            i++;
	        }
	        else
	        {
	            flag = 0;
	            if (type == '\n')
	            {
	                if (*(int*)ReturnCols(map) == 0) *(int*)ReturnCols(map) = i;
	                i = 0;
					*(int*)ReturnRows(map) = *(int*)ReturnRows(map) + 1;
	            }
	            if(feof(inputFile)) *(int*)ReturnRows(map) = *(int*)ReturnRows(map) + 1;
	        }
	    }
	}
}

void ReadMap1(void* map)
{
	FreeMap1(map);
	map = InitMap1();
	PrintText("Enabled scene will be deleted");
	char fileName[64];
	FILE* inputFile = NULL;
	while (1)
	{
		EnterString(&fileName, "Enter fileName:");
		fopen_s(&inputFile, fileName, "r");
		if (inputFile != NULL) break;
		else PrintText("The file cannot be opened");
	}

	Map1* map1 = map;
	char type = ' ';
	int i = 0;
	int j = 0;
	char flag = 0;
	int phase = 1;
	while (phase == 1) /*считывание ширины по верхней границе*/
	{
		fread(&type, sizeof(char), 1, inputFile);
		if (feof(inputFile))
		{
			phase = 0;
			break;
		}
		if (type == '\n')
		{
			*(int*)ReturnCols(map) = i;
			*(int*)ReturnRows(map) = 1;
			i = 0;
			phase = 2;
			if (feof(inputFile))
			{
				phase = 0;
				break;
			}
		}
		else
		{
			if (flag == 0)
			{
				if (type != '1')
				{
					phase = 0;
					break;
				}
				else
				{
					InsertCell(map, CalcPos(map, i, 0), '1', -1);
				}
				flag = 1;
				i++;
			}
			else
			{
				if (type != ' ')
				{
					phase = 0;
					break;
				}
				flag = 0;
			}
		}
	}	
	//printf("SizeCells %d SizePoints %d SizeEdges %d\n", SizeCells(map), SizePoints(map), SizeEdges(map));
	while (phase == 2) /*считывание высоты по правой границе*/
	{
		fread(&type, sizeof(char), 1, inputFile);
		if (feof(inputFile))
		{
			phase = 0;
			break;
		}
		else
		{
			fseek(inputFile, -1, SEEK_CUR);
		}
		for (int j = 0; j < (2*(*(int*)ReturnCols(map)) - 1); j++)
		{
			if (j == (2*(*(int*)ReturnCols(map)) - 2))
			{
				InsertCell(map, CalcPos(map, (*(int*)ReturnCols(map) - 1), *(int*)ReturnRows(map)), '1', -1);
			}
			fseek(inputFile, 1, SEEK_CUR);
			if (feof(inputFile))
			{
				phase = 0;
				break;
			}
		}
		fread(&type, sizeof(char), 1, inputFile);
		if (type == '\n')
		{
			*(int*)ReturnRows(map) = *(int*)ReturnRows(map) + 1;
		}
		else
		{
			*(int*)ReturnRows(map) = *(int*)ReturnRows(map) + 1;
			phase = 3;
			fseek(inputFile, 0, SEEK_SET);
			break;
		}
	}
	while (phase == 3) /*проверка левой границы*/
	{
		fread(&type, sizeof(char), 1, inputFile);
		if (i == *(int*)ReturnRows(map))
		{
			phase = 4;
			flag = 0;
			i = 0;
			//printf("SizeCells %d SizePoints %d SizeEdges %d\n", SizeCells(map), SizePoints(map), SizeEdges(map));
			fseek(inputFile, -(2 * (*(int*)ReturnCols(map)) - 1), SEEK_END);
			break;
		}
		else
		{
			if (type == '1')
			{
				InsertCell(map, CalcPos(map, 0, i), '1', -1);
				i++;
			}
			else
			{
				phase = 0;
				break;
			}
			fseek(inputFile, (2 * (*(int*)ReturnCols(map))), SEEK_CUR);
		}
	}
	while (phase == 4) /*проверка нижней границы*/
	{
		fread(&type, sizeof(char), 1, inputFile);
		if (feof(inputFile))
		{
			phase = 5;
			j = 1;
			i = 1;
			flag = 1;
			fseek(inputFile, (2 * (*(int*)ReturnCols(map)) + 2), SEEK_SET);
			break;
		}
		else
		{
			if (flag == 0)
			{
				if (type != '1')
				{
					phase = 0;
					break;
				}
				else
				{
					InsertCell(map, CalcPos(map, i, *(int*)ReturnRows(map) - 1), '1', -1);
				}
				flag = 1;
				i++;
			}
			else
			{
				if (type != ' ')
				{
					phase = 0;
					break;
				}
				flag = 0;
			}
		}
	}

	while (phase == 5) /*считывание и проверка карты*/
	{
		fread(&type, sizeof(char), 1, inputFile);
		if ((j == *(int*)ReturnRows(map) - 2)&&(i == *(int*)ReturnCols(map) - 1))
		{
			phase = -1;
			break;
		}
		else
		{
			if (i == *(int*)ReturnCols(map))
			{
				i = 1;
				j++;
				fseek(inputFile, 1, SEEK_CUR);
				flag = 1;
			}
			else
			{
				if (flag == 0)
				{
					if ((type > 96) && (type < 123))
					{
						int intNamePoint = CalcIntName(&type);
						if (ReturnNumberPoint(map, &intNamePoint) == NULL)
						{
							InsertCell(map, CalcPos(map, i, j), type, -1);
							InsertPoint(map, intNamePoint, CalcPos(map, i, j));
						}
						else
						{
							phase = 0;
							break;
						}
					}
					else
					{
						switch (type)
						{
						case '1':
						{
							InsertCell(map, CalcPos(map, i, j), '1', -1);
							break;
						}
						case ' ':
						{
							InsertCell(map, CalcPos(map, i, j), '0', -1);
							break;
						}
						default:
						{
							phase = 0;
							break;
						}
						}
					}
					flag = 1;
					i++;
				}
				else
				{
					if (type != ' ')
					{
						phase = 0;
						break;
					}
					flag = 0;
				}
			}
		}
	}
	if (
		(phase != 0)
		&&
		(
		(*(int*)ReturnCols(map) < 3)
		||
		(*(int*)ReturnRows(map) < 3)
			)
		)
	{
		FreeMap1(map);
		map = InitMap1();
		PrintText("Incorrect input map");
	}
	if (phase == 0)
	{
		FreeMap1(map);
		map = InitMap1();
		PrintText("Incorrect input map");
	}
	fclose(inputFile);
}

void LoadScene(void* map)
{
	FreeMap1(map);
	map = InitMap1();
	PrintText("Enabled scene will be deleted");
	ReadScene(map);
}

void SaveScene(void* map)
{
	WriteScene(map);
}

void AddPoint(void* map)
{
	char inputPoint = ' ';
	int pointX = 0;
	int pointY = 0;
	while (1)
	{
		EnterChar(&inputPoint, "Enter charName of new point:", NULL);
		int intNamePoint = CalcIntName(&inputPoint);
		if (ReturnNumberPoint(map, &intNamePoint) == NULL)
		{
			EnterInt(&pointX, "Enter int x coord of new point:", NULL);
			EnterInt(&pointY, "Enter int y coord of new point:", NULL);
			int pos = CalcPos(map, pointX, pointY);
			if (
				(ReturnTypeCell(map, &pos) != NULL)
				&&
				(*(char*)ReturnTypeCell(map, &pos) == '0')
				)
			{
				*(char*)ReturnTypeCell(map, &pos) = inputPoint;
				InsertPoint(map, intNamePoint, pos);
				EnterInt(ReturnMaxNearestEdge(map, ReturnNumberPoint(map, &intNamePoint)), "Enter int maxNearestPoints of new point:", NULL);
				break;
			}
			else
			{
				PrintText("Error input, please enter correct coords");
			}
		}
		else
		{
			PrintText("Such a point already exists");
		}
	}
}

void DeletePointNoErase(void* map)
{
	char inputPoint = ' ';
	while (1)
	{
		EnterChar(&inputPoint, "Enter charName point to delete:", NULL);
		int intNamePoint_from = CalcIntName(&inputPoint);
		if (ReturnNumberPoint(map, &intNamePoint_from) != NULL)
		{
			RemovePoint(map, ReturnNumberPoint(map, &intNamePoint_from));
			break;
		}
		else
		{
			PrintText("Error input, please enter existing point charName");
		}
	}
}

void DeletePointFrom(void* map)
{
	if (*(char*)ReturnCrossRoutes(map) == '0')
	{
		ResetLevelCells(map);
		ResetNearestPoints(map);
		ResetWaveCells(map);
		ResetDrawEdgeCells(map);
		char inputPoint = ' ';
		while (1)
		{
			EnterChar(&inputPoint, "Enter charName point to delete:", NULL);
			int intNamePoint_from = CalcIntName(&inputPoint);
			int* numberPoint_from = ReturnNumberPoint(map, &intNamePoint_from);
			if (numberPoint_from != NULL)
			{
				//int size = *(int*)SizeEdgesFrom(map, numberPoint_from);
				for (int i = 0; i < SizeEdgesFrom(map, numberPoint_from); i++)
				{
					EraseEdgeFrom(map, ReturnPosEdge(map, numberPoint_from));
					ResetLevelCells(map);
				}
				RemovePoint(map, ReturnNumberPoint(map, &intNamePoint_from));
				ResetLevelCells(map);
				ResetNearestPoints(map);
				ResetWaveCells(map);
				ResetDrawEdgeCells(map);
				break;
			}
			else
			{
				PrintText("Error input, please enter existing point charName");
			}
		}
	}
	else
	{
		PrintText("CrossEdges = 1, cant erase from->to edges");
	}
}

void ReDrawAllEdges(void* map)
{
	EraseAllEdge(map);
	ResetToEdges(map);
	InsertEdgesMap(map);
}