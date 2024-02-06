#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "WaveAlgorithm.h"
#include "GraphRoutesStruct.h"
#include "MapStruct.h"
#include "GUI.h"

int DrawEdge(void* map, int* posFrom, int* posTo)
{
	int pointX = CalcXCoord(map, posTo);
	int pointY = CalcYCoord(map, posTo);
	int count = 0;
	char flagSkip = 0;
	if (*(char*)ReturnCrossRoutes(map) == '1')
	{
		flagSkip = 1;
	}
	int step = *(int*)ReturnLevelCell(map, posTo);
	int distance = step;
	int stopPointPos = *posTo;
	int i[8] = { -1, 0, 0, 1, -1, -1, 1, 1 };
	int j[8] = { 0, -1, 1, 0, -1, 1, -1, 1 };
	for (step; step > 0; )
	{
		count = 0;
		for (char iter = 0; (iter < 8) && (count >= 0); iter++)
		{
			int nextCellPos = CalcPos(map, pointX + i[iter], pointY + j[iter]);
			int cellPos = CalcPos(map, pointX, pointY);
			if (count == 8) return 0;
			if (*(int*)ReturnLevelCell(map, &nextCellPos) != -1) count++;
			if (!((flagSkip == 0) && (*(char*)ReturnTypeCell(map, &nextCellPos) < 28)))
			{
				if ((*(int*)ReturnLevelCell(map, &nextCellPos) != -1) && (*(int*)ReturnLevelCell(map, &nextCellPos) < step) && (*(char*)ReturnTypeCell(map, &nextCellPos) != '1'))
				{

					//if (cellPos == 67)
					//{
					//	printf("DEBUG");
					//}
					//if (ReturnIterNextDrawIters(map) != NULL) printf("0 DrawIter %d\n", *(char*)ReturnIterNextDrawIters(map));
					//if (ReturnIterPrevDrawIters(map) != NULL) printf("1 DrawIter %d\n", *(char*)ReturnIterPrevDrawIters(map));
					//printf("iter %d\n", iter);
					char type = *(char*)ReturnTypeCell(map, &cellPos);
					if (iter > 3)
					{
						*(int*)ReturnCountDiag(map) = *(int*)ReturnCountDiag(map) + 1;
					}
					if (type < 28)
					{
						if (*(char*)ReturnCrossRoutes(map) == '0')
						{
							EraseEdge(map);
							ResetDrawIters(map);
							*(int*)ReturnCountDiag(map) = 0;
							//PrintMapTypeCells(map);
							return 0;
						}
						else
						{
							RemoveSecondDrawIters(map);
							InsertBeginDrawIters(map, &iter);
							char replace = CalcTypeDraw(map);/*например*/
							if (type != replace) *(char*)ReturnTypeCell(map, &cellPos) = '*';
							//printf("DEBUG");
						}
					}
					else
					{
						switch (type)
						{
						case('0'):
						{
							//if (*(char*)ReturnCrossRoutes(map) != '1')
							//{
							//	int nextCellPosLeft = CalcPos(map, pointX, pointY + j[iter]);
							//	int nextCellPosRight = CalcPos(map, pointX + i[iter], pointY);
							//	char typeLeft = *(char*)ReturnTypeCell(map, &nextCellPosLeft);
							//	char typeRight = *(char*)ReturnTypeCell(map, &nextCellPosRight);
							//	if (
							//		(iter > 3 && step > 1)
							//		&&
							//		(
							//			(
							//				(typeLeft < 28) && (typeRight < 28)
							//				)
							//			||
							//			(
							//				(typeLeft < 28)
							//				&&
							//				(typeRight != '0' && typeRight >= 28 && typeRight != '1')
							//				)
							//			||
							//			(
							//				(typeRight < 28)
							//				&&
							//				(typeLeft != '0' && typeLeft >= 28 && typeLeft != '1')
							//				)
							//			)
							//		)
							//	{
							//		EraseEdge(map);
							//		ResetDrawIters(map);
							//		*(int*)ReturnCountDiag(map) = 0;
							//		return 0;
							//	}		
							//}
							InsertBeginDrawEdgeCell(map, &cellPos);
							RemoveSecondDrawIters(map);
							InsertBeginDrawIters(map, &iter);

							*(char*)ReturnTypeCell(map, &cellPos) = CalcTypeDraw(map);/*например*/
							printf("From %c\n", *(char*)ReturnTypeCell(map, posFrom));
							printf("To %c\n", *(char*)ReturnTypeCell(map, posTo));
							//PrintMapLevelCells(map);
							//PrintNearestPoints(map);
							PrintMapTypeCellsSDL(map);
							//printf("DEBUG");
							break;
						}
						case('*'):
						{
							InsertBeginDrawEdgeCell(map, &cellPos);
							RemoveSecondDrawIters(map);
							InsertBeginDrawIters(map, &iter);
							break;
						}
						default:
						{
							if (step != distance)
							{
								int intNameFrom1 = CalcIntName(ReturnTypeCell(map, &stopPointPos));
								int intNameTo1 = CalcIntName(ReturnTypeCell(map, &cellPos));
								if (ReturnDistanceEdge(map, ReturnNumberPoint(map, &intNameFrom1), ReturnNumberPoint(map, &intNameTo1)) == NULL)
								{
									int distance1 = 100*(*(int*)ReturnLevelCell(map, &stopPointPos) - *(int*)ReturnLevelCell(map, &cellPos) - *(int*)ReturnCountDiag(map)) + *(int*)ReturnCountDiag(map) * 141;
									InsertEdge(map, ReturnNumberPoint(map, &intNameFrom1), ReturnNumberPoint(map, &intNameTo1), distance1, '1');
									InsertEdge(map, ReturnNumberPoint(map, &intNameTo1), ReturnNumberPoint(map, &intNameFrom1), distance1, '1');
									InsertBeginDrawEdgeCell(map, &cellPos);
									RemoveSecondDrawIters(map);
									InsertBeginDrawIters(map, &iter);
								}
								else
								{
									EraseEdge(map);
								}
								stopPointPos = cellPos;
								*(int*)ReturnCountDiag(map) = 0;
							}
							else
							{
								InsertBeginDrawIters(map, &iter);
							}
							break;
						}
						}

					}
					pointX = pointX + i[iter];
					pointY = pointY + j[iter];
					count = -1;
					step--;
					if (*(char*)ReturnCrossRoutes(map) == '0')
					{
						flagSkip = 0;
					}
					//PrintMapTypeCells(map);
				}
			}
			//printf("From %c\n", *(char*)ReturnTypeCell(map, posFrom));
			//printf("To %c\n", *(char*)ReturnTypeCell(map, posTo));
			//printf("nextCellPos %d\n", nextCellPos);
			//printf("cellPos %d\n", cellPos);
			//printf("Iter %d\n", iter);
			//PrintMapLevelCells(map);
			//PrintMapTypeCellsSDL(map);
			//PrintEdges(map);
			//printf("SizeNearestPoints %d\n", SizeNearestPoints(map));
			//printf("SizeWaveCells %d\n", SizeWaveCells(map));
			//printf("SizeDrawEdgeCells %d\n", SizeDrawEdgeCells(map));
			//if (ReturnIterNextDrawIters(map) != NULL) printf("0 DrawIter %d\n", *(char*)ReturnIterNextDrawIters(map));
			//if (ReturnIterPrevDrawIters(map) != NULL) printf("1 DrawIter %d\n", *(char*)ReturnIterPrevDrawIters(map));
			//printf("DEBUG");
		}
		flagSkip = 1;
	}
	int intNameFrom = CalcIntName(ReturnTypeCell(map, posFrom));
	int intNameTo = CalcIntName(ReturnTypeCell(map, &stopPointPos));
	if (ReturnDistanceEdge(map, ReturnNumberPoint(map, &intNameFrom), ReturnNumberPoint(map, &intNameTo)) == NULL)
	{
		int distance2 = 100*(*(int*)ReturnLevelCell(map, &stopPointPos) - *(int*)ReturnCountDiag(map)) + *(int*)ReturnCountDiag(map) * 141;
		InsertEdge(map, ReturnNumberPoint(map, &intNameFrom), ReturnNumberPoint(map, &intNameTo), distance2, '1');
		InsertEdge(map, ReturnNumberPoint(map, &intNameTo), ReturnNumberPoint(map, &intNameFrom), distance2, '1');
	}
	else
	{
		EraseEdge(map);
	}
	*(int*)ReturnCountDiag(map) = 0;
	ResetDrawEdgeCells(map);
	ResetDrawIters(map);
	return 1;
}

void EraseEdge(void* map)
{
	char* type = NULL;
	while ((SizeDrawEdgeCells(map) > 0)&&(*(char*)ReturnTypeCell(map, ReturnPosFirstDrawEdgeCell(map)) < 28))
	{
		*(char*)ReturnTypeCell(map, ReturnPosFirstDrawEdgeCell(map)) = '0';
		RemoveFirstDrawEdgeCell(map);
	} 
	ResetDrawEdgeCells(map);
}

char CalcTypeDraw(void* map)
{
	char invert[8] = {3, 2, 1, 0, 7, 6, 5, 4};
	*(char*)ReturnIterPrevDrawIters(map) = invert[*(char*)ReturnIterPrevDrawIters(map)];
	char less = 0;
	char more = 0;
	if (*(char*)ReturnIterNextDrawIters(map) > *(char*)ReturnIterPrevDrawIters(map))
	{
		more = *(char*)ReturnIterNextDrawIters(map);
		less = *(char*)ReturnIterPrevDrawIters(map);
	}
	else
	{
		less = *(char*)ReturnIterNextDrawIters(map);
		more = *(char*)ReturnIterPrevDrawIters(map);
	}
	more--;
	char type = 0;
	for (char i = 0; i < less; i++)
	{
		type = type + ((char)7 - i);
		more--;
	}
	type = type + more;
	return type;
}

int CheckIter(char* end, char symbolFrom, char symbol, char iter, char* iter1, char* iter2)
{
	char invert[8] = { 3, 2, 1, 0, 7, 6, 5, 4 };
	if (((symbol > 96) && (symbol < 123) && (symbol != symbolFrom)))
	{
		*end = 1;
		if ((*iter1 == 0) && (*iter2 == 0))
		{
			return 1;
		}
		else
		{
			if ((iter == *iter1) || (iter == *iter2)) return 1;
		}
	}
	if (symbol < 28)
	{
		iter = invert[iter];
		char type = 0;
		char iter1a = 0;
		char iter2a = 0;
		for (iter1a; symbol - type > 6 - iter1a; iter1a++)
		{
			type = type + ((char)7 - iter1a);
		}
		iter2a = iter1a + 1 + (symbol - type);
		if ((iter == iter1a) || (iter == iter2a))
		{
			*iter1 = iter1a;
			*iter2 = iter2a;
			return 1;
		}
		else return 0;
	}
	else return 0;
}

void EraseEdgeFrom(void* map, int* posFrom)
{
	char symbolFrom = *(char*)ReturnTypeCell(map, posFrom);
	int pointX = CalcXCoord(map, posFrom);
	int pointY = CalcYCoord(map, posFrom);
	char count = 0;
	char end = 0;
	char* type = NULL;
	char iter1 = ' ';
	char iter2 = ' ';
	int i[8] = { -1, 0, 0, 1, -1, -1, 1, 1 };
	int j[8] = { 0, -1, 1, 0, -1, 1, -1, 1 };
	while (end == 0)
	{
		count = 0;
		for (char iter = 0; (iter < 8) && (count == 0); iter++)
		{
			int nextCellPos = CalcPos(map, pointX + i[iter], pointY + j[iter]);
			int cellPos = CalcPos(map, pointX, pointY);
			char typeNext = *(char*)ReturnTypeCell(map, &nextCellPos);
			if ((CheckIter(&end, symbolFrom, typeNext, iter, &iter1, &iter2)) && (*(char*)ReturnTypeCell(map, &nextCellPos) != '1') && (*(int*)ReturnLevelCell(map, &nextCellPos) == -1))
			{
				type = (char*)ReturnTypeCell(map, &cellPos);
				if (*type < 28)
				{
					*type = '0';
				}
				*(int*)ReturnLevelCell(map, &cellPos) = 0;
				pointX = pointX + i[iter];
				pointY = pointY + j[iter];
				count = 1;
				//printf("From %c\n", *(char*)ReturnTypeCell(map, posFrom));
				//printf("nextCellPos %d\n", nextCellPos);
				//printf("cellPos %d\n", cellPos);
				//printf("Iter %d\n", iter);
				//PrintMapTypeCells(map);
				//printf("DEBUG");
			}
		}
	}
}

void EraseAllEdge(void* map)
{
	for (int i = 0; i < SizeCells(map); i++)
	{
		char* type = (char*)ReturnTypeCell(map, &i);
		if (
			(*type == '*')
			||
			(*type < 28)
			) *type = '0';
	}
}

void CalcCell(void* map, int* pos, int* numberPoint_From)
{
	int pointX = CalcXCoord(map, pos);
	int pointY = CalcYCoord(map, pos);
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			int cellPosNext = CalcPos(map, pointX + i, pointY + j);
			char* typeNext = ReturnTypeCell(map, &cellPosNext);
			int* levelNext = ReturnLevelCell(map, &cellPosNext);
			if ((*typeNext != '1') && (*levelNext == -1))
			{
				if ((*typeNext >= 28) && (*typeNext != '0') && (*typeNext != '*'))
				{
					int intNameNext = CalcIntName(typeNext);
					InsertEndNearestPoint(map, ReturnNumberPoint(map, &intNameNext), numberPoint_From);
				}
				*levelNext = *(int*)ReturnLevelCell(map, pos) + 1;
				InsertEndWaveCell(map, &cellPosNext);
				//PrintWaveCells(map);
			}
		}
	}
	RemoveFirstWaveCell(map);
}

void CalcWave(void* map, int* numberPoint_From)
{
	ResetLevelCells(map);
	ResetWaveCells(map);
	ResetDrawEdgeCells(map);
	*(int*)ReturnLevelCell(map, ReturnPosEdge(map, numberPoint_From)) = 0;
	InsertEndWaveCell(map, ReturnPosEdge(map, numberPoint_From));
	while (SizeWaveCells(map) != 0)
	{
		CalcCell(map, ReturnPosFirstWaveCell(map), numberPoint_From);
	}
}

//void CalcCellCross(void* map, int* pos, char charNameTo)
//{
//	int cellPos = *pos;
//	int pointX = CalcXCoord(map, &cellPos);
//	int pointY = CalcYCoord(map, &cellPos);
//	int i[8] = { -1, 0, 0, 1, -1, -1, 1, 1 };
//	int j[8] = { 0, -1, 1, 0, -1, 1, -1, 1 };
//	for (char iter = 0; iter < 8; iter++)
//	{
//		int cellPosNext = CalcPos(map, pointX + i[iter], pointY + j[iter]);
//		char* typeNext = ReturnTypeCell(map, &cellPosNext);
//		int* levelNext = ReturnLevelCell(map, &cellPosNext);
//		if (
//			(*typeNext == '0')
//			&& 
//			(*levelNext == -1)
//			)
//		{
//			if (iter > 3)
//			{
//				int nextCellPosLeft = CalcPos(map, pointX, pointY + j[iter]);
//				int nextCellPosRight = CalcPos(map, pointX + i[iter], pointY);
//				char typeLeft = *(char*)ReturnTypeCell(map, &nextCellPosLeft);
//				char typeRight = *(char*)ReturnTypeCell(map, &nextCellPosRight);
//				if (
//					!(
//						(
//							(typeLeft < 28) && (typeRight < 28)
//						)
//						||
//						(
//							(typeLeft < 28)
//							&&
//							(typeRight != '0' && typeRight >= 28 && typeRight != '1')
//						)
//						||
//						(
//							(typeRight < 28)
//							&&
//							(typeLeft != '0' && typeLeft >= 28 && typeLeft != '1')
//						)
//					)
//				)
//				{
//					*levelNext = *(int*)ReturnLevelCell(map, &cellPos) + 1;
//					InsertEndWaveCell(map, &cellPosNext);
//				}
//			}
//			else
//			{
//				*levelNext = *(int*)ReturnLevelCell(map, &cellPos) + 1;
//				InsertEndWaveCell(map, &cellPosNext); 
//			}
//		}
//		if (*typeNext == charNameTo)
//		{
//			*levelNext = *(int*)ReturnLevelCell(map, &cellPos) + 1;
//			ResetWaveCells(map);
//			printf("SizeWaveCells %d\n",SizeWaveCells(map));
//			printf("DEBUG\n");
//			return;
//		}
//		//PrintMapLevelCells(map);
//	}
//	RemoveFirstWaveCell(map);
//}
void CalcCellCross(void* map, int* pos, char charNameTo)
{
	int cellPos = *pos;
	int pointX = CalcXCoord(map, &cellPos);
	int pointY = CalcYCoord(map, &cellPos);
	int i[8] = { -1, 0, 0, 1, -1, -1, 1, 1 };
	int j[8] = { 0, -1, 1, 0, -1, 1, -1, 1 };
	for (char iter = 0; iter < 8; iter++)
	{
		int cellPosNext = CalcPos(map, pointX + i[iter], pointY + j[iter]);
		char* typeNext = ReturnTypeCell(map, &cellPosNext);
		int* levelNext = ReturnLevelCell(map, &cellPosNext);
		if (
			(
				(*typeNext == charNameTo)
				||
				(*typeNext == '0')
				)
			&& 
			(*levelNext == -1)
			)
		{
			if (iter > 3)
			{
				int nextCellPosLeft = CalcPos(map, pointX, pointY + j[iter]);
				int nextCellPosRight = CalcPos(map, pointX + i[iter], pointY);
				char typeLeft = *(char*)ReturnTypeCell(map, &nextCellPosLeft);
				char typeRight = *(char*)ReturnTypeCell(map, &nextCellPosRight);
				if (
					!(
						(
							(typeLeft < 28) && (typeRight < 28)
							)
						||
						(
							(typeLeft < 28)
							&&
							(typeRight != '0' && typeRight >= 28 && typeRight != '1')
							)
						||
						(
							(typeRight < 28)
							&&
							(typeLeft != '0' && typeLeft >= 28 && typeLeft != '1')
							)
						)
					)
				{
					*levelNext = *(int*)ReturnLevelCell(map, &cellPos) + 1;
					InsertEndWaveCell(map, &cellPosNext);
					if (*typeNext == charNameTo)
					{
						ResetWaveCells(map);
						printf("SizeWaveCells %d\n",SizeWaveCells(map));
						printf("DEBUG\n");
						return;
					}
				}
			}
			else
			{
				*levelNext = *(int*)ReturnLevelCell(map, &cellPos) + 1;
				InsertEndWaveCell(map, &cellPosNext);
				if (*typeNext == charNameTo)
				{
					ResetWaveCells(map);
					printf("SizeWaveCells %d\n", SizeWaveCells(map));
					printf("DEBUG\n");
					return;
				}
			}
		}
	}
	RemoveFirstWaveCell(map);
}
void CalcWaveCross(void* map, int* posFrom, int* posTo)
{
	ResetLevelCells(map);
	ResetWaveCells(map);
	ResetDrawEdgeCells(map);
	char charNameTo = *(char*)ReturnTypeCell(map, posTo);
	*(int*)ReturnLevelCell(map, posFrom) = 0;
	InsertEndWaveCell(map, posFrom);
	while (SizeWaveCells(map) != 0)
	{
		//PrintWaveCells(map);
		CalcCellCross(map, ReturnPosFirstWaveCell(map), charNameTo);
		PrintMapLevelCells(map);
	}
}