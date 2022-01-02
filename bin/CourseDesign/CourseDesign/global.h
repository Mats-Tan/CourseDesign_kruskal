#pragma once
#pragma warning(default:4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#define Provinces_NUMBER 34
#define MaxSize 128
typedef char* String;


/*
* Stack
*/
char stack[MaxSize];


/*
* Structure definition
*/
typedef struct Provinces Province;
typedef struct Citys City;
typedef struct Blocks Block;

struct Provinces {
	String code;
	String name;
	String province;
	City* childrens;	//citys
	int cityNum;
};

struct Citys {
	float x, y;			// longitude and latitude 
	String code;
	String name;
	Province* province;	// link with its own province
	Block* childrens;	//blocks
	int blockNum;
};

struct Blocks {
	String code;
	String name;
	Province* province;	// link with its own province
	City* chileres;		// link with its own city
};


/*
* global variable
*/
Province ProvincesTier[35];// one sentry with thirty_five "Province"
int PT35;

FILE* JSONData;	//the position of "level.json"
FILE* ALLdetalDATA;	//the position of "detailLevel.csv"
FILE* AOTudeData;	//the position of "AOTude.csv"
/*-----------Data_Util.c------*/
int addProvince(String str);

FILE* file_CSVDATA(String path);// file
FILE* file_JSONDATA(String path);// file

/// <summary>
/// table of longitude and latitude
/// </summary>
typedef struct LOdata {
	String id;
	String name;
	String x;
	String y;
	struct LOdata* next;
}LOd;

typedef struct LOdatas {
	LOd* head;
	LOd* tail;
	int length;
}LOlink;
static LOlink LOK;

/*
* test algorithm
*/
int kruskaltest();