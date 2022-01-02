#include<stdio.h>
#include"Mydll.h"
void test_print(char const* str)
{
        printf("测试输出的内容是：%s\n", str);
}

int test_sum(int a, int b)
{
        return a + b;
}