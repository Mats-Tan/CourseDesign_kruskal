#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(default:4996)

typedef char* String;

typedef struct CSVDATAS_COLUMNS {
	String data;
	struct CSVDATAS_COLUMNS* next;
}CSV_COLUMN;

typedef struct CSVDATAS_LINE {
	CSV_COLUMN* columns;
	struct CSVDATAS_LINE* next;
}CSV_LINE;


typedef struct CSVDATAS {
	CSV_LINE* lines;
	int line_num;
	int column_num;
}DATA_CSV;

typedef struct CSVFILEs {
	String path;
	FILE* fp;
	DATA_CSV* data_csv;
}FILE_CSV;
/*founction area*/
//FILE_CSV* Fileloading_CSV(String path, int column_num); //不能自动检查列数
FILE_CSV* Fileloading_CSV(String path);

DATA_CSV* Data_loading_CSV(FILE* fp, int column_num);
//FILE_CSV* Fileloading_CSV(String path);
CSV_LINE* addLine(CSV_LINE* tail, String line[], int num);
CSV_COLUMN* addcolumn(String e, CSV_COLUMN* pcolumn);
CSV_LINE* getLineIndex(DATA_CSV* csv, int row_index);
CSV_COLUMN* getColumnIndex(CSV_LINE* line, int col_index);
String getData(DATA_CSV* csv, int row, int col);
