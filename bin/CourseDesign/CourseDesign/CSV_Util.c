#include "CSV_Util.h"

CSV_COLUMN* addcolumn(String e, CSV_COLUMN* pcolumn) {
	String data = (String)malloc(25 * sizeof(char));
	strcpy(data, e);
	pcolumn->data = data;
	return pcolumn;
}

/// <summary>
/// 对已经产生的空间操作,在这里不使用会导致指针tail变化的方法
/// </summary>
/// <param name="tail"></param>
/// <param name="line"></param>
/// <param name="num"></param>
/// <returns></returns>
CSV_LINE*addLine(CSV_LINE* tail,String line[],int num) {
	if (tail == NULL)return NULL;
	String str = NULL;
	CSV_COLUMN* columns = (CSV_COLUMN*)calloc(1, sizeof(CSV_COLUMN));
	CSV_COLUMN* p = columns;
	int i = 0;
	for (; i < num; i++) {
		str = line[i];
		addcolumn(str, p);
		p->next = (CSV_COLUMN*)calloc(1, sizeof(CSV_COLUMN));
		p = p->next;
	}

	tail->columns = columns;
	return tail;
}

DATA_CSV* Data_loading_CSV(FILE* fp,int column_num) {
	if (fp == NULL)return fp;

	DATA_CSV* data_csv = (DATA_CSV*)calloc(1, sizeof(DATA_CSV));
	data_csv->lines = (CSV_LINE*)calloc(1, sizeof(CSV_LINE));
	CSV_LINE* pline = data_csv->lines;
	CSV_LINE* pp = NULL;


	String line = NULL; String record = NULL;
	String* str = NULL;
	str = (String*)calloc(column_num, sizeof(String));
	int i = 0;
	char buffer[1024];

	char delims[] = ",";
	char* result = NULL;
	int line_num = 0;

	while ((line = fgets(buffer, sizeof(buffer), fp)) != NULL)
	{
		record = strtok(line, ",");
		while (record != NULL)
		{	
			if (strcmp(record, "Ps:") == 0)
				return 0;
			str[i] = record;
			/*printf("%-23s\t", str[i]);*/
			i++;
			if (i == column_num) {
				addLine(pline,str,column_num);
				line_num++;
				pline->next = (CSV_LINE*)calloc(1, sizeof(CSV_LINE));
				/*pp = pline;*/
				pline = pline->next;
				i = 0;
			}
			record = strtok(NULL, ",");
		}
	}
	/*free(pp->next);
	pp->next = NULL;*/


	if (data_csv != NULL) {
		data_csv->column_num = column_num;
		data_csv->line_num = line_num;
	}
		
	return data_csv;
}

FILE_CSV* Fileloading_CSV(String path) {
	int column_num = 0;
	FILE_CSV* csv = (FILE_CSV*)calloc(1, sizeof(FILE_CSV));
	csv->path = path;
	if (!(csv->fp = fopen(path, "a+"))) {
		printf("ERROR: FILE OPENING FAILURE!\n");
		return NULL;
	}

	char str[128] = { NULL };
	String record = NULL;
	if (fgets(str, 128, csv->fp) == NULL)return NULL;
	int i = 0;
	if (record = strtok(str, ",") != NULL)i = 1;
	for (; (record = strtok(NULL, ",")) != NULL; i++);
	column_num = i;
	rewind(csv->fp);
	

	csv->data_csv = Data_loading_CSV(csv->fp,column_num);
	fclose(csv->fp);
	return csv;
}

/// <summary>
/// 根据行号 i 获取行
/// </summary>
/// <param name="csv"></param>
/// <param name="i"></param>
CSV_LINE* getLineIndex(DATA_CSV*csv,int row_index) {
	CSV_LINE* p = csv->lines;
	int i = 0;
	for (; i < row_index&&p!=NULL; i++) {
		p = p->next;
	}
	if (p == NULL) {
		printf("ERROR: The %d row does not exist \n(\t--getLineIndex(DATA_CSV*csv,int row_index))\n", row_index);
		return NULL;
	}
	else {
		return p;
	}
}

/// <summary>
/// 根据列号 i 获取列结构
/// </summary>
/// <param name="line"></param>
/// <param name="i"></param>
CSV_COLUMN*getColumnIndex(CSV_LINE* line, int col_index) {
	if (line == NULL) {
		return NULL;
	}
	CSV_COLUMN* p = line->columns;
	int i = 0;
	for (; i < col_index&&p!=NULL; i++) {
		p = p->next;
	}
	if (p == NULL) {
		printf("ERROR: The %d row %d col does not exist \n(\t--getColumnIndex(CSV_LINE* line, int col_index))\n",i, col_index);
		return NULL;
	}
	else {
		return p;
	}
}

/// <summary>
/// 获取第 row 行,第 col 列的 data
/// </summary>
/// <param name="csv"></param>
/// <param name="row"></param>
/// <param name="col"></param>
/// <returns></returns>
String getData(DATA_CSV* csv,int row, int col) {
	 return getColumnIndex(getLineIndex(csv,row),col)->data;
}

