#ifndef _Program_H_
#define _Program_H_

void startTest(); /*DEBUG*/
void start();

void ReadMap(void* map);
void ReadMap1(void* map);
void LoadScene(void* map);
void SaveScene(void* map);
void AddPoint(void* map);
void DeletePointNoErase(void* map);
void DeletePointFrom(void* map);
void ReDrawAllEdges(void* map);
void InsertCrossEdges(void* map);
void InsertEdgesMap(void* map);
void InsertEdgesMapCross(void* map);
void RunAlgDijkstra(void* map);
void DisableEdgeMap(void* map);
void AddMaxNearestPoints(void* map);
void SetMaxNearestPoints(void* map);

#endif
