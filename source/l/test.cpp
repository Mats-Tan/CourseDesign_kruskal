#include"test1.h" 
#include "CSV_Util.h"
typedef struct List {
	char* city1;
	double longitude1;
	double latitude1;
	char* city2;
	double longitude2;
	double latitude2;
	struct List* next;
}sqlist;
void Showgraph(sqlist& L,sqlist& L1,int x,int y) {
	sqlist* p = &L;
	sqlist* p1 = &L1;
	initgraph(x, y);
	int R = 5;
	int  r = 45;
	double l = 0.6;
	r = (int)r * l;
	setbkcolor(WHITE);
	cleardevice();
	setcolor(BLACK);
	int size = r / 2;
	setfillcolor(RED);
	settextstyle(size, 0, "楷体"); setbkmode(TRANSPARENT);
	settextcolor(RED);
	setlinecolor(GREEN);
	for (int i = 0; p != NULL; i++) {
		line((int)p->longitude1, (int)p->latitude1, (int)p->longitude2, (int)p->latitude2);
		outtextxy((int)(p->longitude1 - size / 2), (int)(p->latitude1+5 ), p->city1);
		outtextxy((int)(p->longitude2 - size / 2 ), (int)(p->latitude2+5 ), p->city2);
		fillcircle((int)p->longitude1, (int)p->latitude1 , R);
		fillcircle((int)p->longitude2, (int)p->latitude2, R);
		p = p->next;
	}for (int i = 0; p1 != NULL;i++) {
		line((int)p1->longitude1, (int)p1->latitude1, (int)p1->longitude2, (int)p1->latitude2);
		outtextxy((int)(p1->longitude1 - size / 2 ), (int)(p1->latitude1+5 ), p1->city1);
		outtextxy((int)(p1->longitude2 - size / 2), (int)(p1->latitude2+5 ), p1->city2);
		fillcircle((int)p1->longitude1 , (int)p1->latitude1 , R);
		fillcircle((int)p1->longitude2 , (int)p1->latitude2 , R);
		p1 = p1->next;
	}
	_getch();
	closegraph();
}
String stradd(CSV_LINE* line) {
	String str = (String)calloc(64 , sizeof(char));
	for (int i = 0; i < 6;) {
		strcat(str, getColumnIndex(line, i)->data);
		i++;
		if(i<6)strcat(str, ",");
	}
	return str;
}
sqlist* loadingDataGraph(sqlist* L, char* str2, int xi, int yi, char* x0, char* y0) {
	sqlist* p = NULL;
	int rx=35, ry=40;
	p = (sqlist*)malloc(sizeof(sqlist));
	p->city1 = (char*)malloc(23 * sizeof(char));
	p->city2 = (char*)malloc(23 * sizeof(char));
	p->next = NULL;
	char* record = strtok(str2, ",");
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 0:
			strcpy(p->city1, record);
			break;
		case 1:
			p->longitude1 = (double)xi+(atof(record) - atof(x0))*rx;
			break;
		case 2:
			p->latitude1 = (double)yi + (atof(record) - atof(y0)) * ry ;
			break;
		case 3:
			strcpy(p->city2, record);
			break;
		case 4:
			p->longitude2 = (double)xi + (atof(record) - atof(x0)) * rx;
			break;
		case 5:
			p->latitude2 = (double)yi + (atof(record) - atof(y0)) * ry ;
			break;
		default:
			printf("\n");
		}
		record = strtok(NULL, ",");
	}
	if (L == NULL) {
		L = p;
		return L;
	}
	else {
		sqlist* pp = L;
		while (pp->next != NULL)pp = pp->next;
		pp->next = p;
	}
	return L;
}
int main(int argc,char* argv[]) {
	while (argc-- > 1)
	{
		if (argv>0)
			printf("%s\n", *++argv);
		else
			printf("ERROR\n");
	}
	char* record,*s,*mm,*nn;
	record= strtok(*argv, ",");
	s = strtok(NULL, ",");
	mm = strtok(NULL, ",");
	nn = strtok(NULL, ",");
	int m = atoi(mm);
	int n = atoi(nn);
	int xi = m / 4, yi = (n -300) / 2;
	sqlist* L = NULL;
	sqlist* L1 = NULL;
	String str1 = (String)record;
	FILE_CSV* csv = NULL;
	if ((csv = Fileloading_CSV(str1)) == NULL) {
		printf("empty\n");
	}
	for (int i = 0; i < csv->data_csv->line_num; i++) {
		stradd(getLineIndex(csv->data_csv, i));
		L = loadingDataGraph(L, stradd(getLineIndex(csv->data_csv, i)),xi,yi, getData(csv->data_csv, 0, 1), getData(csv->data_csv, 0, 2));
	}
	
	String str3 = (String)s;
	FILE_CSV* csv1 = NULL;
	if ((csv1 = Fileloading_CSV(str3)) == NULL) {
		printf("empty\n");
	}
	for (int i = 0; i < csv1->data_csv->line_num; i++) {
		 stradd(getLineIndex(csv1->data_csv, i));
		L1 = loadingDataGraph(L1, stradd(getLineIndex(csv1->data_csv, i)), 3*xi, yi, getData(csv1->data_csv, 1, 1), getData(csv1->data_csv, 1, 2));
	}
	Showgraph(*L,*L1,m,n);
}
//int main(int argc, char* argv[])
//{
//	while (argc-- > 1)
//	{
//		if (argv > 0)
//			printf("%s\n", *++argv);
//		else
//			printf("ERROR\n");
//	}
//	char* record, * s;
//	record = strtok(*argv, ",");//读取一行中的第一个字符串
//	s = strtok(NULL, ",");//读取后续字符串
//	printf("%s\n", record);
//	printf("%s\n", s);
//	int m = atoi(record);//将字符串转为整型得到窗口宽度
//	int n = atoi(s);//窗口高度
//}
//#include <graphics.h>		// 引用图形库头文件
//#include <conio.h>
//int main()
//{
//	initgraph(640, 480);	// 创建绘图窗口，大小为 640x480 像素
//	setbkcolor(WHITE);
//	cleardevice();
//	setcolor(BLACK);
//	line(200, 100, 100, 10);//(左上角x,左上角y, 右下角x，右下角y)
//	_getch();				// 按任意键继续
//	closegraph();			// 关闭绘图窗口
//	return 0;
//}




//int addLOdMes(String str[]) {
//	if (str == NULL) return -1;
//
//	//注意: 每个字符都要空间
//	dt->City1 = (String)calloc(32, sizeof(char));
//	dt->Longitude1 = (String)calloc(32, sizeof(char));
//	dt->Latitude1 = (String)calloc(32, sizeof(char));
//	dt->City2 = (String)calloc(32, sizeof(char));
//	dt->Longitude2(String)calloc(32, sizeof(char));
//	dt->Latitude2 = (String)calloc(32, sizeof(char));
//	strcpy(dt->City1, str[0]);
//	strcpy(dt.Longitude1, str[1]);
//	strcpy(dt->Latitude1, str[2]);
//	strcpy(dt->City2, str[3]);
//	strcpy(dt->Longitude2, str[4]);
//	strcpy(dt->Latitude2, str[5]);
//	dt->next = NULL;
//
//	if (flag == 1) {
//		LOK.head = data;
//		LOK.head->next == NULL;
//		LOK.length = 1;
//		LOK.tail = LOK.head;
//		flag = 0;
//		printf("start here:\n");
//	}
//	else {
//		LOK.tail->next = data;
//		LOK.tail = LOK.tail->next;
//		/*showLOd(LOK.head);*/
//
//
//
//	}
//	dt = NULL;
//	return 0;
//}
//void get_from_csv(void)
//{
	//char buff[MAX];
	//char* str[6],*record;
	//DT* dt = (DT*)calloc(1, sizeof(DT));
	//DT* head = dt;
	//FILE* fp = fopen("D:/CourseDesign/database/res.csv", "r");
	//if (NULL == fp)
	//{
	//	printf("read file fail\n");
	//	return;
	//}
//	int i = 0;
//	while (fgets(buff, sizeof(buff), fp) != NULL)
//	{
//
//		i = 0;
//		record = strtok(buff, ",");
//		while (record != NULL)
//		{
//			if (strcmp(record, "Ps:") == 0)
//				return 0;
//			str[i] = record;
//			i++;
//			if (i == 6) {
//				addLOdMes(str);
//				i = 0;
//			}
//			record = strtok(NULL, ",");
//
//		}
//		for (i = 0; i < 6; i++) {
//			str[i] = strtok(NULL, ",");
//			if (strlen(str[i]) < strlen("ps"))break;
//			printf("%s", str[i]);
//		}
//
//		for (int j = 0; j < i; j++) {
			/*switch (j) {
			case 0:
				dt->City1 = (char*)calloc(40, sizeof(char));
				strcpy(dt->City1, str[j]);
				break;
			case 1:
				dt->Longitude1 = atof(str[j]);
				break;
			case 2:
				dt->Latitude1 = atof(str[j]);
				break;
			case 3:
				dt->City2 = (char*)calloc(40, sizeof(char));
				strcpy(dt->City1, str[j]);
				break;
			case 4:
				dt->Longitude2 = atof(str[j]);
				break;
			case 5:
				dt->Latitude2 = atof(str[j]);
				break;
			default:
				printf("加载完成\n");
			}*/
//		}
//
//		dt->next = (DT*)calloc(1, sizeof(DT));
//		dt = dt->next;
//		memset(buff, 0, sizeof(buff));
//	}
//	fclose(fp);
//}
//int main() {
//	char buff[1024];
//	FILE* fp = fopen("D:/CourseDesign/database/res.csv", "r");
//	if (NULL == fp)
//	{
//		printf("read file fail\n");
//	}
//
//	while (fgets(buff, sizeof(buff), fp) != NULL)
//	{
//		printf("%s", buff);
//	}
//}
//int main() {
//	FILE* fp = NULL;
//	char* line, * record;
//	char buffer[1024];
//	if ((fp = fopen("D:/CourseDesign/database/res.csv", "at+")) != NULL)
//	{
//		fseek(fp, 0L, SEEK_SET);  //定位到第二行，每个英文字符大小为1
//		char delims[] = ",";
//		char* result = NULL;
//		int j = 0;
//		while ((line = fgets(buffer, sizeof(buffer), fp)) != NULL)//当没有读取到文件末尾时循环继续
//		{
//			record = strtok(line, ",");
//			while (record != NULL)//读取每一行的数据
//			{
//				if (strcmp(record, "Ps:") == 0)//当读取到Ps那一行时，不再继续读取
//					return 0;
//				printf("%s ", record);//将读取到的每一个数据打印出来
//				if (j == 10)  //只需读取前9列
//					break;
//				record = strtok(NULL, ",");
//				j++;
//			}
//			
//			j = 0;
//
//		}
//		fclose(fp);
//		fp = NULL;
//	}
//}
//int main(int argc, char* agrv[]) {
//	if (argc > 1) {
//		FILE_CSV* csv = Fileloading_CSV(agrv[1]);
//		String str = NULL;
//		if (csv != NULL) {
//			for (int i = 0; i < csv->data_csv->line_num; i++) {
//				for (int j = 0; j < csv->data_csv->column_num; j++) {
//					printf("%-23s\t", getData(csv->data_csv, i, j));
//				}
//				putchar('\n');
//			}
//		}
//		return 0;
//	}
//	return 1;
//}


// 读取以，分割的一行数据
// 输入： 1,2,3,4,5
// 输出 1 2 3 4 5 
//#include <iostream>
//#include <sstream>
//#include <vector>
//
//using namespace std;
//int main() {
//    string str;
//    getline(cin, str);
//    stringstream ss(str);
//
//    vector<int> nums;
//    char del = ',';// 分割符号为，
//    string tmp;
//    while (getline(ss, tmp, del)) {
//        nums.push_back(stoi(tmp));
//    }
//    // 输出 1 2 3 4 5 
//    for (auto v : nums) {
//        cout << v << " ";
//    }
//}
// str 为输入字符串，del为分隔符，返回分割之后的字符串数组
//vector<string> split(string str, char del) {
//    stringstream ss(str);
//    string tmp;
//    vector<string> res;
//    while (getline(ss, tmp, del)) {
//        res.push_back(tmp);
//    }
//    return res;
//}

//int main()
//{
//	FILE* p = NULL;
//	int i;
//	char buff[MAX];
//	p = fopen("D:/text/text.txt", "w");
//	fprintf(p, "liwencai\n");
//	fputs("liwencai\n",p);
//	/*fgets(buff, MAX, p);
//	for (i=1;i<MAX;i++)
//	{
//		fputc(buff,p);
//	}*/
//
//}
//void display()
//{
//	int x = 50, y = 200, r = 50;
//	float l = 0.6; int number = 4;
//	r = (int)r * l;
//	initgraph(1000, 800);	// ������ͼ���ڣ���СΪ 640x480 ����
//	setbkcolor(WHITE);				// ���ñ���ɫΪ��ɫ
//	cleardevice();					// �ñ���ɫ�����Ļ
//	setcolor(BLACK);
//
//	for (int i = 0; i < number; i++) {
//		x = x + 100;
//		line(x - 50, 100, x, y);
//		fillcircle(x, y, r);
//		
//	}
//	int size = r / 2;
//	settextstyle(size, 0, "΢���ź�");
//	outtextxy(x - size / 2, y, "����");
//	int z = 0;
//	for (int i = 0; i < number; i++)
//	{
//		z = z + 100;
//		fillcircle(z, y-100, r);
//	}
//	
//	_getch();				// �����������
//	closegraph();			// �رջ�ͼ����
//	return 0;
//}
//int main()
//{
//	initgraph(950, 680);
	//setbkcolor(WHITE);				// ���ñ���ɫΪ��ɫ
	//cleardevice();					// �ñ���ɫ�����Ļ
	//setcolor(RED);					// ���û�ͼɫΪ��ɫ
//	int a, b, c, d, o = 0, q = 0, r = 0, p = 0;
//	int x, y, m, n, cir[6][2], l[6][4], e = 0, f = 0;
//	printf("input the number of circles:\n");
//	scanf("%d", &x);
//	printf("%d\n", x);
//	for (m = 0; m < x; m++)
//	{
//		for (n = 0; n < x; n++)
//		{
//			scanf("%d", &cir[m][n]);
//		}
//	}
//	for (m = 0; m < 3; m++)
//	{
//		e = cir[m][1];
//		f = cir[m][2];
//		circle(e, f, 30);
//	}
//	_getch();						// �����������
//	closegraph();					// �ر�ͼ�ν���
//	return 0;
//}

//{
//	int i;
//	short win_width, win_height;//���崰�ڵĿ�Ⱥ͸߶�
//	win_width = 480; win_height = 360;

//int main()
//	initgraph(win_width, win_height);//��ʼ�����ڣ�������
//	for (i = 0; i < 256; i += 5)
//	{
//		setbkcolor(RGB(i, i, i));//���ñ���ɫ��ԭ��Ĭ�Ϻ�ɫ
//		cleardevice();//������ȡ���ڱ���ɫ��
//		Sleep(15);//��ʱ15ms
//	}
//	closegraph();//�رջ�ͼ����
//}
//int r1[] = { 30,20,130,60 };//���밴ť�ľ��β���
//int r2[] = { 170,20,220,60 };//���а�ť�ľ��β���
//int r3[] = { 260,20,310,60 };//�˳���ť�ľ��β���
//int main()
//{
//	int i;
//	short win_width, win_height;//���崰�ڵĿ�Ⱥ͸߶�
//	win_width = 480; win_height = 360;
//	initgraph(win_width, win_height);//��ʼ�����ڣ�������
//	for (i = 0; i < 256; i += 5)
//	{
//		setbkcolor(RGB(i, i, i));//���ñ���ɫ��ԭ��Ĭ�Ϻ�ɫ
//		cleardevice();//������ȡ���ڱ���ɫ��
//		Sleep(15);//��ʱ15ms
//	}
//	RECT R1 = { r1[0],r1[1],r1[2],r1[3] };//����ָ��R1
//	RECT R2 = { r2[0],r2[1],r2[2],r2[3] };//����ָ��R2
//	RECT R3 = { r3[0],r3[1],r3[2],r3[3] };//����ָ��R3
//	LOGFONT f;//������ʽָ��
//	gettextstyle(&f);					//��ȡ������ʽ
//	_tcscpy(f.lfFaceName, _T("����"));	//��������Ϊ����
//	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
//	settextstyle(&f);                     // ����������ʽ
//	settextcolor(BLACK);				//BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����
//	drawtext("�������", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R1���������֣�ˮƽ���У���ֱ���У�������ʾ
//	drawtext("����", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R2���������֣�ˮƽ���У���ֱ���У�������ʾ
//	drawtext("�˳�", &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R3���������֣�ˮƽ���У���ֱ���У�������ʾ
//	setlinecolor(BLACK);
//	rectangle(r1[0], r1[1], r1[2], r1[3]);
//	rectangle(r2[0], r2[1], r2[2], r2[3]);
//	rectangle(r3[0], r3[1], r3[2], r3[3]);
//	system("pause");//��ͣ��Ϊ����ʾ
//	closegraph();
//	return 0;
//}
//#define PI 3.1416
//int r[3][4] = { {30,20,130,60},{170,20,220,60},{260,20,310,60} };//������ť�Ķ�ά����
//float alpha, R, h0, sim_t;//��ײʱ��������ʧ�ʣ���İ뾶����ʼ�߶ȡ�����ʱ��
////��ť�жϺ���
//int button_judge(int x, int y)
//{
//	if (x > r[0][0] && x<r[0][2] && y>r[0][1] && y < r[0][3])return 1;
//	if (x > r[1][0] && x<r[1][2] && y>r[1][1] && y < r[1][3])return 2;
//	if (x > r[2][0] && x<r[2][2] && y>r[2][1] && y < r[2][3])return 3;
//	return 0;
//}
////��ʼ��ͼ��
//void init_figure()
//{
//	int i;
//	setrop2(R2_COPYPEN);//��ǰ��ɫ
//	setlinecolor(BLACK);
//	setlinestyle(PS_SOLID);//ʵ��
//	rectangle(30, 100, 420, 330);//�����
//	setlinestyle(PS_DOT);//����
//	for (i = 30 + 39; i < 420; i += 39)
//	{
//		line(i, 100, i, 330);//��ֱ������
//	}
//	for (i = 100 + 23; i < 330; i += 23)
//	{
//		line(30, i, 420, i);//ˮƽ������
//	}
//}
////��������
//int simulation()
//{
//	char t[3];//�ٷ�ֵ���ַ�
//	char* out_text;
//	float dt = 0.01;//������10ms
//	float dy = 230 / h0;//��λ������
//	long int N = (long int)(sim_t / dt);//��������
//	float* h = (float*)calloc(N, sizeof(float));//�߶�
//	float* v = (float*)calloc(N, sizeof(float));//�ٶȣ���ֱ����
//	long int i;//��������
//	float process_duty;//����
//	RECT r = { 370,35,400,65 };//�ٷ�ֵ��ʾ����ľ���ָ��
//	init_figure();//��ʼ��ͼ������
//	setrop2(R2_COPYPEN);//��ǰ��ɫ
//	setfillcolor(WHITE);
//	setlinecolor(WHITE);
//	fillrectangle(354, 19, 411, 81);//����ԭ����������
//	setlinestyle(PS_NULL);//������
//	setbkmode(TRANSPARENT);//����������䱳��Ϊ͸��
//	//���㲽��
//	h[0] = h0; v[0] = 0;
//	BeginBatchDraw();//��ʼ������
//	for (i = 1; i < N; i++)
//	{
//		if (h[i - 1] > R)//δ������ײ
//		{
//			v[i] = v[i - 1] - 9.8 * dt;//�ٶȼ���
//		}
//		else//������ײ��������ʧalpha���ٶ���ʧalpha�Ŀ���
//		{
//			v[i] = -sqrt(alpha) * v[i - 1];
//		}
//		setfillcolor(WHITE);
//		setlinecolor(WHITE);
//		fillrectangle(354, 19, 416, 81);//����ԭ����������
//		h[i] = h[i - 1] + v[i] * dt;//�߶ȼ���
//		process_duty = (i + 1) / (float)(N);
//		setlinestyle(PS_SOLID);
//		putpixel(30 + (int)(process_duty * 390), 330 - (int)(h[i] * dy), RED);
//		setfillcolor(BLUE);
//		setlinestyle(PS_NULL);
//		fillpie(355, 20, 415, 80, 0, process_duty * 2 * PI);
//		setfillcolor(WHITE);
//		fillcircle(385, 50, 20);
//		sprintf(t, "%d", (int)(process_duty * 100.0));//����ת��Ϊ�ַ���
//		out_text = strcat(t, "%");//���һ���ٷֺ�
//		drawtext(out_text, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
//		Sleep(dt * 1000);
//		FlushBatchDraw();//ˢ�»�����
//	}
//	EndBatchDraw();//����������
//	free(h);
//	free(v);
//	return 0;
//}
//
//int main()
//{
//	int i, event = 0;
//	char s[30];//�����ַ�������
//	short win_width, win_height;//���崰�ڵĿ�Ⱥ͸߶�
//	win_width = 480; win_height = 360;
//	initgraph(win_width, win_height);//��ʼ�����ڣ�������
//	for (i = 0; i < 256; i += 5)
//	{
//		setbkcolor(RGB(i, i, i));//���ñ���ɫ��ԭ��Ĭ�Ϻ�ɫ
//		cleardevice();//������ȡ���ڱ���ɫ��
//		Sleep(30);//��ʱ30ms
//	}
//	RECT R1 = { r[0][0],r[0][1],r[0][2],r[0][3] };
//	RECT R2 = { r[1][0],r[1][1],r[1][2],r[1][3] };
//	RECT R3 = { r[2][0],r[2][1],r[2][2],r[2][3] };
//	LOGFONT f;//������ʽָ��
//	gettextstyle(&f);					//��ȡ������ʽ
//	_tcscpy(f.lfFaceName, _T("����"));	//��������Ϊ����
//	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
//	settextstyle(&f);                     // ����������ʽ
//	settextcolor(BLACK);				//BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����
//	drawtext("�������", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R1���������֣�ˮƽ���У���ֱ���У�������ʾ
//	drawtext("����", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R2���������֣�ˮƽ���У���ֱ���У�������ʾ
//	drawtext("�˳�", &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R3���������֣�ˮƽ���У���ֱ���У�������ʾ
//	setlinecolor(BLACK);
//	rectangle(r[0][0], r[0][1], r[0][2], r[0][3]);
//	rectangle(r[1][0], r[1][1], r[1][2], r[1][3]);
//	rectangle(r[2][0], r[2][1], r[2][2], r[2][3]);
//	MOUSEMSG m;//���ָ��
//
//	while (true)
//	{
//		m = GetMouseMsg();//��ȡһ�������Ϣ
//
//		switch (m.uMsg)
//		{
//		case WM_MOUSEMOVE:
//			setrop2(R2_XORPEN);
//			setlinecolor(LIGHTCYAN);//������ɫΪ����ɫ
//			setlinestyle(PS_SOLID, 3);//���û�����ʽΪʵ�֣�10��
//			setfillcolor(WHITE);//�����ɫΪ��ɫ
//			if (button_judge(m.x, m.y) != 0)
//			{
//				if (event != button_judge(m.x, m.y))
//				{
//					event = button_judge(m.x, m.y);//��¼��һ�δ����İ�ť
//					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//�п������Σ�X1,Y1,X2,Y2��
//				}
//			}
//			else
//			{
//				if (event != 0)//�ϴδ����İ�ťδ������Ϊԭ������ɫ
//				{
//					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//����ͬ��Ϊԭ����ɫ
//					event = 0;
//				}
//			}
//			break;
//		case WM_LBUTTONDOWN:
//			setrop2(R2_NOTXORPEN);//��Ԫ��դ����NOT(��Ļ��ɫ XOR ��ǰ��ɫ)
//			for (i = 0; i <= 10; i++)
//			{
//				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//����Բ��ɫ
//				circle(m.x, m.y, 2 * i);
//				Sleep(20);//ͣ��30ms
//				circle(m.x, m.y, 2 * i);//Ĩȥ�ոջ���Բ
//			}
//			//���հ�ť�ж����������Ĳ���
//			switch (button_judge(m.x, m.y))
//			{
//				//��ԭ��ťԭ��
//			case 1:
//				InputBox(s, 30, "��������ײʱ��������ʧ�ʡ���İ뾶����ʼ�߶ȡ�����ʱ��");
//				sscanf(s, "%f%f%f%f", &alpha, &R, &h0, &sim_t);//�������ַ�������ɨ�赽ȫ�ֱ�������
//				FlushMouseMsgBuffer();//�����¼�����������Ϣ
//				break;
//			case 2:
//				simulation();//��������
//				FlushMouseMsgBuffer();//�����¼�����������Ϣ
//				break;
//			case 3:
//				closegraph();//�رջ�ͼ����
//				exit(0);//�����˳�
//			default:
//				FlushMouseMsgBuffer();//�����¼�����������Ϣ
//				//printf("\r\n(%d,%d)",m.x,m.y);//��ӡ������꣬�������ʱȷ������
//				break;
//			}
//			break;
//		}
//	}
//	return 0;
//}

//int main(void)
//{
//	initgraph(640, 480);//��ʼ��ͼ�ν���,������СΪ640*480
//	setbkcolor(RGB(64, 128, 128));//���ñ���ɫ
//	cleardevice(); //�ñ���ɫ���������Ļ(��������)
//		//��һ��Բ
//		setlinecolor(RGB(255, 0, 0));//���û���(����)����ɫ
//	setlinestyle(PS_SOLID, 10);//��������Ϊʵ��,�����߿�Ϊ10����
//	circle(320, 240, 200);//��ͼ,Բ��(320,240),�뾶Ϊ200
//	settextcolor(RGB(255, 255, 0));//����������ɫ
//	//����������ʽ:����߶�Ϊ100����,��Ȳ�ָ��,��������Ϊ΢���ź�
//	settextstyle(100, 0, "΢���ź�");
//	outtextxy(170, 190, ("Ԭʯͷ"));//��ָ��λ������ı�
//	//��һ��б��
//	line(180, 380, 460, 100);//��(180,380)��(460,100)��һ��ֱ��
//	system("pause");
//	closegraph();
//	//�ر�ͼ�ν���
//}

//#include<MMSystem.h>//����������Ҫ��ͷ�ļ�
//#pragma comment(lib,"winmm.lib")//���߱�����,����winmm.lib���ļ�
//
//int main(void) {
//	initgraph(800, 513);
//	loadimage(0, _T("jile.jpg"));
//	//�ظ�����"���־���.MP3"
//	mciSendString(_T("piay ���־���.MP3 repeat"), 0, 0, 0);
//
//	system("pause");
//	closegraph();
//	return 0;
//}
