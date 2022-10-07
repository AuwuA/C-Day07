#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 栈帧的概念
void swap(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}

void swap2(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void test01()
{
    int m = 53;
    int n = 57;
    swap(m, n);
    printf("m = %d, n = %d\n", m, n);
    swap2(&m, &n);
    printf("m = %d, n = %d\n", m, n);
}

// 数组做函数参数 传递的是数组的首地址 不能用sizeof求数组的大小
void bubbleSort(void *arr, unsigned long long size, unsigned long long eleLen, int (*compare)(void *data1, void *data2))
{
    for (unsigned long long i = 0; i < size - 1; i++) {
        for (unsigned long long j = 0; j < size - 1 - i; j++) {
            if (compare((char *)arr + j * eleLen, (char *)arr + (j + 1) * eleLen)) {
                void *buff = malloc(eleLen);
                if (NULL == buff) {
                    return;
                }
                memcpy_s(buff, eleLen, (char *)arr + j * eleLen, eleLen);
                memcpy_s((char *)arr + j * eleLen, eleLen, (char *)arr + (j + 1) * eleLen, eleLen);
                memcpy_s((char *)arr + (j + 1) * eleLen, eleLen, buff, eleLen);
                free(buff);
                buff = NULL;
            }
        }
    }
}

int compare(void *data1, void *data2)
{
    return *(int *)data1 > *(int *)data2;
}

void test02()
{
    int arr[] = {5, 89, 3, 22, 40, 31, 9, 22, 67, 28};
    bubbleSort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), compare);
    for (unsigned long long i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        printf("%d\n", arr[i]);
    }
}

int m;// 全局变量 对应空间消失是要函数结束

int *test_func(int arr[])
{
    printf("test_func sizeof(arr) = %llu\n", sizeof(arr));
    m = 100;
    return &m;
//    int p = 1234;
//    return &p;
}

void test03()
{
    int arr[] = {4, 5, 6};
    test_func(arr);
    printf("test03 sizeof(arr) = %llu\n", sizeof(arr));
}

// 指针做函数返回值 不能返回局部变量的地址值
void test04()
{
    int arr[] = {4, 5, 6};
    int *p =test_func(arr);
    printf("p = %p\n", p);
}

// 字符串和指针
void test05()
{
    char str1[] = "hello";
    char m[] = "hello";
    str1[0] = 'R';
    char *str2 = "hello";// 字符串常量 不能修改
    char *n = "hello";
    printf("str1 = %s\n", str1);
    // str2[0] = 'R';
    printf("str2 = %s\n", str2);

    printf("str1 = %p\n", str1);
    printf("m = %p\n", m);
    printf("str1 = %p\n", str2);
    printf("n = %p\n", n);
}

// 字符串比较
int myStrcmp(char *srcStr, char *destStr)
{
    while(*srcStr == *destStr && *srcStr != '\0' && *destStr != '\0') {
        srcStr++;
        destStr++;
    };
    if (*srcStr == *destStr) {
        return 0;
    } else if (*srcStr > *destStr) {
        return 1;
    }else {
        return -1;
    }
}

void test06()
{
    char *str1 = "hellow";
    char *str2= "helloa";
    if (1 == myStrcmp(str1, str2)) {
        printf("str1 > str2\n");
    } else if (-1 == myStrcmp(str1, str2)) {
        printf("str1 < str2\n");
    } else {
        printf("str1 == str2\n");
    }
}

// 字符串拷贝
char *myStrcpy(char *srcStr, char *desStr)
{
    char *temp = desStr;
    while(1)
    {
        if (*srcStr == '\0') {
            *temp++ = *srcStr;
            return desStr;
        } else {
            *temp++ = *srcStr;
        }

        srcStr++;
    }
}

void test07()
{
    char *src = "helloworldfuoie11ll";

    char dst[100];

    myStrcpy(src, dst);

    printf("dst = %s\n", dst);
}

void removeSpace(char *str)
{
    while(*str) {
        while (*str == ' ') {
          char *temp1 = str;
          char *temp2 = str + 1;
          while (*temp2) {
              *temp1++ = *temp2++;
          }
          *temp1 = *temp2;
        }
        str++;
    }
}

// 字符串去空格
void test08()
{
    char str[] = "ni chou sha, chou ni z    a    di";
    removeSpace(str);
    puts(str);
}

// 字串在字符串中首次出现的位置
int isSubStr(char *str, char *subStr)
{
    while(*subStr) {
        if (*subStr != *str) {
            return 0;
        }
        subStr++;
        str++;
    }
    return 1;
}

char *myStrstr(char *str, char *subStr)
{
    while(*str) {
        if (isSubStr(str, subStr)) {
            return str;
        }
        str++;
    }
    return NULL;
}

void test09()
{
    char *str = "hellomollho";
    char *subStr = "lho";
    char * p = myStrstr(str, subStr);
    if (NULL == p) {
        printf("Not found\n");
    } else {
        printf("Found it: %s\n", p);
    }
}

// 统计子串在字符串中出现的次数
int statisticSubstrTimes(char *str, char *subStr)
{
    int num = 0;
    while(*str){
        if (0 != isSubStr(str, subStr)) {
            num++;
        }
        str++;
    }
    return num;
}

void test10()
{
    char str[] = "helloabclloxyzllo";
    char substr[] = "llo";

    int ret = statisticSubstrTimes(str, substr);

    printf("times = %d\n", ret);
}

// 带参main函数 argc参数个数 argv字符串数组
int main(int argc, char *argv[])
{
//    test01();
//    test02();
//    test03();
//    test04();
//    test05();
//    test06();
//    test07();

//    for (int i = 0; i < argc; i++) {
//        puts(argv[i]);
//    }
//    test08();
//    test09();
    test10();
    return 0;
}
