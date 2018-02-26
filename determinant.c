#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

//包含的头文件不解释
typedef  int    bool;  //因为标准c里边没有bool类型才这么做

#define false 		0
#define true 		1
#define MAX			20

//定义几个全局变量，无奈之举
int *col,  			//将整个行列式的值存到c指向的空间里
    step = 0,		//记录当前的行列式计算进行了多少步
    rank, 			//方便传递行列式的阶数
    sum = 0;   		//记录每一步行列式计算所累加的结果

/*
 * Aq
 */    
int aq(int a)   //计算阶乘的函数，就不多解释了
{
    int s = 1;
    int i;
    
    for (i = 1; i <= a; i++)
        s *= i;
    return s;
}

/*
 * Swap the value
 */
void swap(int *a, int *b)  //利用地址传递，交换两个数的值
{
    int m = *a;
    
    *a = *b;
    *b = m;
}

/*
 * SA
 */
bool sa(int *flags)	 	//计算在行列式计算过程中每一项前边的符号是正还是负
{
    int n = 0;			//n为行列式展开式每一项的逆序数
    int i, j;
    
    for (i = 0; i < rank - 1; i ++)
        for (j = i + 1; j < rank; j++)
            if (flags[i] > flags[j])
				n++; 	//不断通过条件判断累加逆序数得出最终的逆序数
            
    if (n % 2 == 0)
		return false; 			//若为正，则返回false
	
    return true;				//否则返回true
}

/*
 * Permutation
 * perm(b, 0, rank - 1);	
 */
void perm(int *flags, int k, int m) //整个程序里边的核心函数，找出在不同行不同列的所有组合
{
    int i, s = 1, j;
    
    if (k > m) {    	    
        step++;								//每递归回来一次，将记录运行次数加一  
		printf("Raw %d:\t",step);   
  		for (j = 0; j < rank; j ++) {  			
            s *= col[flags[j] + rank * j];	//算出此次行列式展开式的这项的值
            printf("[%d|%d]\t", flags[j], j);
  		}			            
    	printf("\n");
        if (sa(flags))
			s *= -1; 						//确定这一项的符号	
			
								
        //输出当前sum内的值（即到当前为止所得到的结果是多少
        //输出运行的完成程度（即当前运行的次数除以总次数       
       printf("%5d\t完成度：%2.2f%%\n", sum += s, (float) step / aq(rank) * 100);
    }
    else  //不断的向内递归，就不多解释了，因为很多大公司招聘的时候，全排列问题在笔试环节是必出题，百度里有很多解释
    {
        for (i = k; i <= m; i++) {
            swap(flags + k, flags + i);
            perm(flags, k + 1, m);
            swap(flags + k, flags + i);
        }
    }
}


/*
 * Display the matrix
 */
void Display(double arr[][MAX], int n)
{
    int i, j;
    
    printf("");    
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++)
        {
            printf("%lf\t", arr[i][j]);
        }
        printf("\n");
    }
}


/*
 * Main function
 */
int main(void)	//主函数
{
    int *b, 	//一个辅助变量，在递归函数中将b指向的空间内的值进行全排列，也即行列式展开式不同组合的下标
        i, 		//循环中的辅助变量
        f, 		//在格式化输出行列式的辅助变量
        e;		//判断是否退出程序的标志位
        
    system("color 3e");	//设置程序运行的前景色和背景色
	system("cls");		//清空屏幕
	   
u:    
	printf("请输入行列式的阶数：\n");
    scanf("%d", &rank);							//获取行列式的阶数
    b = (int *) malloc (sizeof(int) * rank ); 	//为变量申请空间
    col = (int *) malloc (sizeof(int) * rank * rank);
    
    for ( i = 0; i < rank; i++)
        *( b + i ) = i;							//为辅助变量也即行列式下标逐个赋值
    for ( i = 0; i < rank * rank; i++) {
        if ( i % rank == 0)
            printf("\n请依次输入行列式中第%d行的值（以空格分隔）：\n", i / rank + 1 ); //提示输入行列式的值
    	*(col + i) = rand() % 100;
    	printf("%d\t", *(col + i)); 			  
 		//scanf("%d", c + i );
    }
    
   // Display(c, a);
    
    printf("\n\n");
    perm(b, 0, rank - 1);									//计算行列式的值
    printf("\n行列式展开式共有%d项\n", aq( rank ) );		//打印出来行列式的各种信息
    if (rank % 2 != 0)
		f = rank + 1;										//判断当前的行列式是偶数行还是奇数行
    else 
		f = rank;
    for (i = 0; i < rank * rank; i++)
    {
        if (i / rank + 1 == f / 2 && i % rank == 0) 		//判断是否达到行列式中间的一行行首
            printf("D = ");									//输出“D = ”
        else 
			if (i % rank == 0) 							//判断是否是每一行的行首，若是则输出四个空格，保证输出的格式优美
           		printf("    ");
        if (i % rank == 0) 								//判断是否是行首，若是输出制表符竖线，可与上一句写到一块儿
            printf("┃");
        if ((i + 1) % rank == 0) 							//判断是否是行列式某一行的最后一个数
            printf("%10d\t", * ( col + i ) );
        else
			printf("%10d  ", * ( col + i ) );				//若不是行列式某一行的最后一个数则在数字后边加一个空格
        if ((i + 1) % rank == 0) 							//判断是否到达一行的行末
            printf("┃");
        if ((i + 1) / rank == f / 2 && ( i + 1 ) % rank == 0) //判断是否达到行列式中间一行的行末，输出整个行列式的值
            printf(" = %d\n", sum);
        else if ((i + 1) % rank == 0 ) 				//判断是否到达行末输出换行
            printf("\n");
    }
    printf("\n\n");
    printf("是否继续？（ 1 / 0 ）\n");//提示是否退出
    scanf("%d", &e);
    step = 0;//每次都将都将上一次的运行记录消除
    if ( e != 0 )
	 goto u; //判断是否推出
    else 
		if ( e == 0 )
		 exit( 0 );
    return 0;
}
