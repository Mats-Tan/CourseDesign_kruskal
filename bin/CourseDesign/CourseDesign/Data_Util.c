#include "global.h"
/*
* global variable
*/
extern Province ProvincesTier[35];// one sentry with thirty_five "Province"
extern int PT35;

String find_code(String str) {

	return NULL;
}

String find_name(String str) {

	return NULL;
}


String find_province(String str) {

	return NULL;
}

int addProvince(String str) {
	if (str == NULL)return 0;
	ProvincesTier->code = find_code(str);
	ProvincesTier->name = find_name(str);
	ProvincesTier->province = find_province(str);

	int cityNum;
	return 0;
}


/*
* file
*/
FILE* file_CSVDATA(String path) {
	FILE* fp = NULL;
	char* line, * record;
	char buffer[1024];
	if ((fp = fopen(path, "at+")) != NULL)
	{
		/*fseek(fp, 170L, SEEK_SET);*/
		char delims[] = ",";
		char* result = NULL;

		while ((line = fgets(buffer, sizeof(buffer), fp)) != NULL)
		{
			record = strtok(line, ",");
			while (record != NULL)
			{
				if (strcmp(record, "Ps:") == 0)
					return 0;
				printf("%-23s\t", record);
				record = strtok(NULL, ",");

			}
			printf("\n");

		}
		AOTudeData = fp;
	}
}

FILE* file_JSONDATA(String path) {
	printf("wait...\n");

	return NULL;
}

/*
* The following method is used to simplify the data set
*/

// Write it to convert "train.txt" to "simply_train.csv"
typedef struct station {
	String name;
	float x, y;
	City* itsCity;

};

typedef struct trainData {
	String code;
	String nameA;
	String nameB;
}train;


void store_train_code_name(train* collection,char*record,FILE*save){
	if (record == NULL) {
		return;
	}
	char* delim01 = "e";
	char* delim02 = "\"";
	char* delim03 = "(";
	char* delim04 = "-";
	char* code;
	char* nameA,*nameB;
	code = strtok(record, delim01);
	code = strtok(NULL, delim01); 
	code = strtok(code, delim02); 
	code = strtok(NULL, delim02);
	code = strtok(code, delim03);
	nameA = strtok(NULL, delim03);
	nameA = strtok(nameA, delim04);
	nameB = strtok(NULL, delim04);

	if (code != NULL && nameA != NULL && nameB != NULL) {
		fprintf(save,"%s,%s,%s\n", code, nameA, nameB);
	}

	return;
}

void test() {
	FILE* fp;
	int c;

	fp = fopen("train.txt", "r");
	while (1)
	{
		c = fgetc(fp);
		if (feof(fp))
		{
			break;
		}
		printf("%c", c);
	}
	fclose(fp);
}

void train_conver() {
	FILE* file = fopen("train.txt","w+");
	String path = "E:\\CourseDesign\\database\\train.txt";
	char* line, * record;
	char* recordA[32] = { NULL,NULL };
	char buffer[1024];
	FILE* fp = NULL;
	int flag;	//
	if ((fp = fopen(path, "a+")) == NULL)return;
	train* collection = (train*)calloc(1, sizeof(collection));
	int i = 0; int j = 0;

	while ((line = fgets(buffer, sizeof(buffer), fp)) != NULL && i<20)
	{
		record = strtok(line, ")");
		while (record != NULL)
		{
			recordA[j] = record;
			record = strtok(NULL, ")");
			j++;
		}
		/*recordA[j - 1] = NULL;*/
		int length = j; j = 0;
		while (j<length) {
			store_train_code_name(collection, recordA[j],file);
			recordA[j] = NULL;
			j++;
		}
		j = 0;
		i++;
	}
	fclose(file);
	fclose(fp);
	printf("%d,",rename("train.txt", "train.csv"));
}


/*
* LOd
* loading table of longitude and latitude
*/
extern LOlink LOK; 
static int flag = 1;
int showLOd(const LOd*head) {
	if (head == NULL)return -1;
	LOd* p = head;
	if (p == NULL)return -1;
	/*printf("%-23s\t%-23s\t%-23s\t%-23s\n", "ID", "name", "longitude", "latitude");*/
	int i = 0;
	while (p != NULL) {
		printf("%-23s\t%-23s\t%-23s\t%-23s\n", p->id, p->name, p->x, p->y);
		p = p->next;
		i++;
	}
	printf("data len:%d\n", i);
	return 0;
}


int addLOdMes(String str[]) {
	if (str == NULL) return -1;

	//注意: 每个字符都要空间
	LOd* data = (LOd*)calloc(1, sizeof(LOd));
	data->id = (String)calloc(32, sizeof(char));
	data->name = (String)calloc(32, sizeof(char));
	data->x = (String)calloc(32, sizeof(char));
	data->y = (String)calloc(32, sizeof(char));
	strcpy(data->id , str[0]);
	strcpy(data->name, str[1]);
	strcpy(data->x, str[2]);
	strcpy(data->y, str[3]);
	data->next = NULL;

	if (flag == 1) {
		LOK.head = data;
		LOK.head->next == NULL;
		LOK.length = 1;
		LOK.tail = LOK.head;
		flag = 0;
		printf("start here:\n");
		/*printf("%-23s\t%-23s\t%-23s\t%-23s\n", LOK.head->id, LOK.head->name, LOK.head->x, LOK.head->y);*/
	}
	else {
		LOK.tail->next = data;
		LOK.tail = LOK.tail->next;
		/*showLOd(LOK.head);*/
		
		
	}
	data = NULL;
	return 0;
}

LOd* file_CSVLOd(String path) {
	FILE* fp = NULL;
	char* line, * record;
	char buffer[1024];
	static String str[4] = { NULL }; int i = 0;
	if ((fp = fopen(path, "at+")) != NULL)
	{
		/*fseek(fp, 170L, SEEK_SET);*/
		char delims[] = ",";
		char* result = NULL;

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
				if (i == 4) {
					addLOdMes(str);
					i = 0;
				}
				record = strtok(NULL, ",");

			}
			

		}
		showLOd(LOK.head);
		return fp;
	}
}