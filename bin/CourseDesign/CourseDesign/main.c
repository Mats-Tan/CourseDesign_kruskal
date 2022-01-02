#include "global.h"

#include "CSV_Util.h"

#define JSONPath "E:\\CourseDesign\\database\\level.json"
#define AOTudePath "E:\\CourseDesign\\database\\AOTude.csv"
#define ALLdetalDATAPath "E:\\CourseDesign\\database\\detailLevel.csv"
extern Province ProvincesTier[35];

/*
* GLOBAL DATA
*/
extern FILE* JSONData;	//the position of "level.json"
extern FILE* ALLdetalDATA;	//the position of "detailLevel.csv"
extern FILE* AOTudeData;	//the position of "AOTude.csv"



int initDataFile() {
	/*LOd* LOdhead =*/
	file_CSVLOd((String)AOTudePath);
	/*ALLdetalDATA = file_CSVDATA((String)ALLdetalDATAPath);
	JSONData = file_JSONDATA((String)JSONPath);*/
	/*fclose(AOTudeData);*/
	/*fclose(ALLdetalDATA);*/

	return 0;
}

/*initDataFile();*/
	/*train_conver();*/
	/*kruskaltest();*/

int main(int argc,char* agrv[]) {
	if (argc > 1) {
		FILE_CSV* csv = Fileloading_CSV(agrv[1]);
		String str = NULL;
		if (csv != NULL) {
			for (int i = 0; i < csv->data_csv->line_num; i++) {
				for (int j = 0; j < csv->data_csv->column_num; j++) {
					printf("%-23s\t", getData(csv->data_csv, i, j));
				}
				putchar('\n');
			}
		}
		return 0;
	}
	return 1;
}