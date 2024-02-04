#ifndef _WaveAlgorithm_H_
#define _WaveAlgorithm_H_

int DrawEdge(void* map, int* posFrom, int* posTo);
void EraseEdge(void* map);
int CheckIter(char* end, char symbolFrom, char symbol, char iter, char* iter1, char* iter2);
void EraseEdgeFrom(void* map, int* posFrom);
void EraseAllEdge(void* map);
void CalcCell(void* map, int* pos);
void CalcWave(void* map, int* posFrom);
void CalcCellCross(void* map, int* pos, char charNameTo);
void CalcWaveCross(void* map, int* posFrom, int* posTo);
char CalcTypeDraw(void* map);

#endif