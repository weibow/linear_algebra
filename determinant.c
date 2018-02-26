#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

//������ͷ�ļ�������
typedef  int    bool;  //��Ϊ��׼c���û��bool���Ͳ���ô��

#define false 		0
#define true 		1
#define MAX			20

//���弸��ȫ�ֱ���������֮��
int *col,  			//����������ʽ��ֵ�浽cָ��Ŀռ���
    step = 0,		//��¼��ǰ������ʽ��������˶��ٲ�
    rank, 			//���㴫������ʽ�Ľ���
    sum = 0;   		//��¼ÿһ������ʽ�������ۼӵĽ��

/*
 * Aq
 */    
int aq(int a)   //����׳˵ĺ������Ͳ��������
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
void swap(int *a, int *b)  //���õ�ַ���ݣ�������������ֵ
{
    int m = *a;
    
    *a = *b;
    *b = m;
}

/*
 * SA
 */
bool sa(int *flags)	 	//����������ʽ���������ÿһ��ǰ�ߵķ����������Ǹ�
{
    int n = 0;			//nΪ����ʽչ��ʽÿһ���������
    int i, j;
    
    for (i = 0; i < rank - 1; i ++)
        for (j = i + 1; j < rank; j++)
            if (flags[i] > flags[j])
				n++; 	//����ͨ�������ж��ۼ��������ó����յ�������
            
    if (n % 2 == 0)
		return false; 			//��Ϊ�����򷵻�false
	
    return true;				//���򷵻�true
}

/*
 * Permutation
 * perm(b, 0, rank - 1);	
 */
void perm(int *flags, int k, int m) //����������ߵĺ��ĺ������ҳ��ڲ�ͬ�в�ͬ�е��������
{
    int i, s = 1, j;
    
    if (k > m) {    	    
        step++;								//ÿ�ݹ����һ�Σ�����¼���д�����һ  
		printf("Raw %d:\t",step);   
  		for (j = 0; j < rank; j ++) {  			
            s *= col[flags[j] + rank * j];	//����˴�����ʽչ��ʽ�������ֵ
            printf("[%d|%d]\t", flags[j], j);
  		}			            
    	printf("\n");
        if (sa(flags))
			s *= -1; 						//ȷ����һ��ķ���	
			
								
        //�����ǰsum�ڵ�ֵ��������ǰΪֹ���õ��Ľ���Ƕ���
        //������е���ɳ̶ȣ�����ǰ���еĴ��������ܴ���       
       printf("%5d\t��ɶȣ�%2.2f%%\n", sum += s, (float) step / aq(rank) * 100);
    }
    else  //���ϵ����ڵݹ飬�Ͳ�������ˣ���Ϊ�ܶ��˾��Ƹ��ʱ��ȫ���������ڱ��Ի����Ǳس��⣬�ٶ����кܶ����
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
int main(void)	//������
{
    int *b, 	//һ�������������ڵݹ麯���н�bָ��Ŀռ��ڵ�ֵ����ȫ���У�Ҳ������ʽչ��ʽ��ͬ��ϵ��±�
        i, 		//ѭ���еĸ�������
        f, 		//�ڸ�ʽ���������ʽ�ĸ�������
        e;		//�ж��Ƿ��˳�����ı�־λ
        
    system("color 3e");	//���ó������е�ǰ��ɫ�ͱ���ɫ
	system("cls");		//�����Ļ
	   
u:    
	printf("����������ʽ�Ľ�����\n");
    scanf("%d", &rank);							//��ȡ����ʽ�Ľ���
    b = (int *) malloc (sizeof(int) * rank ); 	//Ϊ��������ռ�
    col = (int *) malloc (sizeof(int) * rank * rank);
    
    for ( i = 0; i < rank; i++)
        *( b + i ) = i;							//Ϊ��������Ҳ������ʽ�±������ֵ
    for ( i = 0; i < rank * rank; i++) {
        if ( i % rank == 0)
            printf("\n��������������ʽ�е�%d�е�ֵ���Կո�ָ�����\n", i / rank + 1 ); //��ʾ��������ʽ��ֵ
    	*(col + i) = rand() % 100;
    	printf("%d\t", *(col + i)); 			  
 		//scanf("%d", c + i );
    }
    
   // Display(c, a);
    
    printf("\n\n");
    perm(b, 0, rank - 1);									//��������ʽ��ֵ
    printf("\n����ʽչ��ʽ����%d��\n", aq( rank ) );		//��ӡ��������ʽ�ĸ�����Ϣ
    if (rank % 2 != 0)
		f = rank + 1;										//�жϵ�ǰ������ʽ��ż���л���������
    else 
		f = rank;
    for (i = 0; i < rank * rank; i++)
    {
        if (i / rank + 1 == f / 2 && i % rank == 0) 		//�ж��Ƿ�ﵽ����ʽ�м��һ������
            printf("D = ");									//�����D = ��
        else 
			if (i % rank == 0) 							//�ж��Ƿ���ÿһ�е����ף�����������ĸ��ո񣬱�֤����ĸ�ʽ����
           		printf("    ");
        if (i % rank == 0) 								//�ж��Ƿ������ף���������Ʊ�����ߣ�������һ��д��һ���
            printf("��");
        if ((i + 1) % rank == 0) 							//�ж��Ƿ�������ʽĳһ�е����һ����
            printf("%10d\t", * ( col + i ) );
        else
			printf("%10d  ", * ( col + i ) );				//����������ʽĳһ�е����һ�����������ֺ�߼�һ���ո�
        if ((i + 1) % rank == 0) 							//�ж��Ƿ񵽴�һ�е���ĩ
            printf("��");
        if ((i + 1) / rank == f / 2 && ( i + 1 ) % rank == 0) //�ж��Ƿ�ﵽ����ʽ�м�һ�е���ĩ�������������ʽ��ֵ
            printf(" = %d\n", sum);
        else if ((i + 1) % rank == 0 ) 				//�ж��Ƿ񵽴���ĩ�������
            printf("\n");
    }
    printf("\n\n");
    printf("�Ƿ�������� 1 / 0 ��\n");//��ʾ�Ƿ��˳�
    scanf("%d", &e);
    step = 0;//ÿ�ζ���������һ�ε����м�¼����
    if ( e != 0 )
	 goto u; //�ж��Ƿ��Ƴ�
    else 
		if ( e == 0 )
		 exit( 0 );
    return 0;
}
