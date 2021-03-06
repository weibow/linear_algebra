#include <stdio.h>
#include <math.h>
 
#define MAX 100
 
double D(double arr[][MAX], int n);
void Display(double arr[][MAX], int n);
 
 
/*
 * Main function
 */
int main(void)
{
    double arr[MAX][MAX];
    double bak[MAX][MAX];
    double value;
    int n;
    int i, j, k, c;
 
     system("color 3e");//设置程序运行的前景色和背景色
u: system("cls");//清空屏幕
 
    printf("Please enter matrix size n(1<=n<20):");
    scanf("%d", &n); 
    printf("Please input matrix line by line:\n");
    
    k = 1;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
           // scanf("%lf", &arr[i][j]);
           arr[i][j] = rand()%100;
        }
    }
 
    printf("matrix a:\n");
    Display(arr, n);
 
    /* 保存D(0,i)的值到bak中 */
//    for(i=0; i<n; i++)             /* 处理第1行的每一列元素 */
//    {
//        for(j=1; j<n; j++)         /* 逐行处理 */
//        {
//            for(c=0,k=0; k<n; k++) /* 逐列处理 */
//            {
//                if(k == i)
//                {
//                    continue;
//                }
//                bak[j-1][c++] = arr[j][k];
//            }
//        }
//        value = D(bak, n-1);
// 
//        printf("Submatrix:\n");
//        Display(bak, n-1);
// 
//        printf("DValue of the Submatrix is   %f\n", D(bak, n-1));
//    }
 
    value = D(arr, n);
    printf("result = %f\n", value);
    return 0;
}
 
 /*
  * Calculate the matrix
  */
double D(double arr[][MAX], int n)
{
    double bak[MAX][MAX];
    int i, j, k, c, d;
    double sum = 0;
 
    if(n == 1)
    {
        return arr[0][0];
    }
 
    for(i=0; i<n; i++)             /* 处理第1行的每一列元素 */
    {
        for(j=1; j<n; j++)         /* 逐行处理 */
        {
            for(c=0,k=0; k<n; k++) /* 逐列处理 */
            {
                if(k == i)
                {
                    continue;
                }
                bak[j-1][c++] = arr[j][k];
            }
        }
        printf("Submatrix:\n");
        Display(bak, n-1);
 
        //printf("DValue of the Submatrix is   %f\n", D(bak, n-1));
        /* 计算arr(row, col) * D(row, col)的值 */
        sum += (i % 2 == 0 ? 1 : -1) * arr[0][i] * D(bak, n-1);
    }
    return sum;
}

/*
 * Display the matrix
 */
void Display(double arr[][MAX], int n)
{
    int i, j;
    printf("");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            printf("%lf\t", arr[i][j]);
        }
        printf("\n");
    }
}