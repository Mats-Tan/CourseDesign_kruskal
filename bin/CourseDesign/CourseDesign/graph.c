#include "global.h"

//typedef struct Citys {
//	String name;
//	String id;
//	double longitude;
//	double latitude;
//}City;
//
//typedef struct Edges{
//	City* vi;
//	City* ui;
//	double weight;
//}Edge;
//
//typedef struct Lists {
//	void* data;
//	struct Lists* next;
//}LinkList;
//
//typedef struct Graphs {
//	int v;
//	int n;
//	LinkList*nodeSet;// 城市集合
//	LinkList*edgesSet;// 边集合
//	LinkList*minTree;
//}Graph;
//
//int isCityEqual(City* city1, City* city2) {
//	if (!strcmp(city1->id, city2->id))return 0;
//	if (!strcmp(city1->name, city2->name))return 0;
//	if (!city1->longitude == city2->longitude)return 0;
//	if (!city1->latitude == city2->latitude)return 0;
//}
//
//int LinkContain(LinkList* nodeSet,const City* city) {
//	if (nodeSet == NULL) {
//		printf("error list null!\n");
//		return 1;
//	}
//	LinkList* p = nodeSet;
//	for (int i = 0; p != NULL; p = p->next) {
//		if (isCityEqual((City*)p->data, city))
//			return 1;
//	}
//	return 0;
//}
//
//int find(LinkList* nodeSet, const Edge* edge) {
//	if (nodeSet == NULL || edge == NULL) {
//		printf("error find()!\n");
//		return 0;
//	}
//	return LinkContain(nodeSet, edge->ui) && LinkContain(nodeSet, edge->vi);
//}
//
//Edge* getEdges(LinkList* edgesSet,int index) {
//	if (edgesSet == NULL) {
//		printf("error edgesSet is NULL!\n");
//		return NULL;
//	}
//	LinkList* p = edgesSet;
//	int i = 0;
//	for (i = 0; i < index && p != NULL; i++)
//		p = p->next;
//
//	if (p == NULL) {
//		printf("error index!\n");
//		return NULL;
//	}
//	else {
//		return p;
//	}
//}
//
//LinkList* getminTree(Graph* g) {
//	LinkList* nodeSet;// 城市集合
//	int i = 0;
//	int isSameSet = 0;
//	while (getEdges(g->edgesSet, i)) {
//		isSameSet = find(nodeSet, getEdges(g->edgesSet, i));
//		if (!isSameSet) {
//			addNode(nodeSet, getEdges(g->edgesSet, i)->ui);
//			addNode(nodeSet, getEdges(g->edgesSet, i)->vi);
//			addNode(g->minTree, getEdges(g->edgesSet, i));
//		}
//		i++;
//	}
//	return g->minTree;
//}