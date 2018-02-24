#include<stdio.h>
#include<math.h>
#include<mem.h>
#define NUM 100

/*
 * Clear screen
 */ 
void clrscr(void)
{
}

/*
 * Print menus
 */
void print(void)     /* 使用说明 */
{
	clrscr();
	printf("\n\n\n\n\n\t\t\t\t Introduction \n");
	printf("\t*--------------------------------------------------------------*\n");
	printf("\t*    This program was design for compute linear equations.       *\n");
	printf("\t*    The way of use it is very simple.                           *\n");
	printf("\t*    First : Input the number of the equation;(Input 0 to exit) *\n");
	printf("\t*    Second: Input the coefficient of every eqution;             *\n");
	printf("\t*    Third : Input the constant of every eqution;                *\n");
	printf("\t*    Last : Chose the way you want use to solve the equtions; *\n");
	printf("\t*    That's all, input any key to run it . . .                   *\n");
	printf("\t*-------------------------By__TJX------------------------------*\n");
//	getch();
}

/*
 * Choose the calculation methodes
 */
void chose(void)    /*选择计算方法*/
{ 
	clrscr();
	fflush(stdin);
	printf("\n\n\n\n\n\t\t**********Introduction********** \n");
	printf("\t\t* Chose the way,please.        * \n");
	printf("\t\t* a : Gauss eliminant.         * \n");
	printf("\t\t* b : Gauss_yd eliminant.      * \n");
	printf("\t\t* c : Iterative way.           * \n");
	printf("\t\t* d : Cramer way.              * \n");
	printf("\t\t* e : exit.                    * \n");              
	printf("\t\t*************By__TJX************ \n");
	printf("\t\tPlease choose number :\n");		
}

/*
 * Input the matrix functions
 */ 
void input(double **a1,double b1[],int num)    /*数据输入*/
{
	int i,j,t;
	double *p;
	char de1,de2;
	
	do {
		printf("Please input array a[%d][%d]: \n",num,num);
		printf("Warn: The first number of the array mustn't contain zero! \n");
		for (i=1; i<=num; i++){
			printf("Please input array a[%d][]: \n",i);
			for(j=1;j<=num;j++)	
			{	
				t=0;
				if (i==1&&j==1)
				{
			 		do{
						if(t==0) { 
							printf("\nal[%d][%d]= ", i, j);
							scanf("%lf",&a1[i][j]);
							printf("Input1 a[%d][%d] = %lf \n", i, j, a1[i][j]); 
							t++;
						} else {
							printf("The input is invalid,please input again:\n");
							printf("\nal[%d][%d] = ", i, j);
						 	scanf("%lf",&a1[i][j]);
						 	printf("Input2 a[%d][%d] = %lf \n", i, j, a1[i][j]); 
						 }
					}while(a1[i][j]==0);
				} else  {
					printf("\nal[%d][%d]= ", i, j);
					scanf("%lf",&a1[i][j]);
					printf("Input a[%d][%d] = %lf \n", i, j, a1[i][j]); 
				}
			}
		}
		printf(" \nPlease check the value of array a[%d][%d].\n press Y to input again, press N to enter into next step\n",num,num);
		do{
			de1=getch();
		}while(de1!='y'&&de1!='Y'&&de1!='n'&&de1!='N');
	}while(de1=='y'||de1=='Y');
	
	do{
		printf("Please input array b[%d]: \n",num);
		p=b1+1;
		for(i=1; i<=num;i++) {
			printf(" Please b[%d]:\n", i); 
			scanf("%lf",p++);
		}
		printf(" \nPlease check the value of array b[%d],press Y to input again.\n",num);
		do{
			de2 = getch();
		}while(de2!='y'&&de2!='Y'&&de2!='n'&&de2!='N');
	}while(de2=='y'||de2=='Y');
}

 
int max(double *t1, double x1[],int n)    /*迭代子函数*/
{ 
	int i,temp=0;
	
	for(i=1;i<=n;i++)
		if(fabs(x1[i]-t1[i])>1e-2) 
		{
			temp=1;
			break;
		}
	/* printf("    %d    ",temp); */
	return temp;
}

/*
 * 
 */
int ddcompute(double **a1,double b1[],double x1[],int n) /*迭代法计算*/
{
	double *t;
	int i,j,k=0;
	double sum1=0.0, sum2=0.0;
	t=(double*)malloc(n*sizeof(double));
	printf("\nPlease Input The Initial Value of x:\n");
	for(i=1;i<=n;i++)
		scanf("%lf",&x1[i]);
	do {
		k++;
		for(i=1;i<=n;i++)
		t[i]=x1[i];
		for(i=1;i<=n;i++)
		{ sum1=0.0;sum2=0.0;
		for(j=1;j<=i-1;j++) sum1=sum1+a1[i][j]*x1[j]; /*printf(" sum1= %0.4f ",sum1);*/
		
		for(j=i+1;j<=n;j++) sum2=sum2+a1[i][j]*t[j]; /* printf(" sum2= %0.4f ",sum2);}*/
		if(a1[i][i]==0||fabs(sum1)>1e+12||fabs(sum2)>1e+12)
		{printf(" \nWarning: These equtions can't be solve by this way!\n Press any Key to continue...");
		getch();
		free(t);
		return 0;}
		x1[i]=(b1[i]-sum1-sum2)/a1[i][i];}
	}while(max(t,x1,n));
	/* for(i=1;i<=n;i++)
	{if(i%3==0) printf("\n");
	printf("    %.4f    ",x1[i]);}*/
	free(t);
	return 1; 
}

int gscompute(double **a1,double b1[],double x1[],int n) /*高斯消元法计算*/
{
	int i,j,k;
	double m,sum;
	for(k=1;k<=n-1;k++)
		for(i=k+1;i<=n;i++)
		{
			if(a1[k][k]==0) {printf(" \nThese equtions can't be solve is this way.\n Press any Key to continue...");
			getch();
			return 0; 
		}
	if ((m=0-a1[i][k]/a1[k][k])==0)
	{i++; continue;}	
	else 
	{for(j=k+1;j<=n;j++)
	a1[i][j]=a1[i][j]+a1[k][j]*m;
	b1[i]=b1[i]+b1[k]*m;}}
	/* yi xia ji suan x zhi */
	x1[n]=b1[n]/a1[n][n];
	for(i=n-1;i>=1;i--)
	{sum=0.0;
	for(j=n;j>=i+1;j--)
	sum=sum+a1[i][j]*x1[j];
	x1[i]=(b1[i]-sum)/a1[i][i];}
	return 1;    
}

/*
 * Gauss  
 */
int gs_ydcompute(double **a1,double b1[],double x1[],int n) /*高斯_约当法计算*/
{
	int i,j,k;
	double m,sum;
	for(k=1;k<=n;k++)
	{
		i=1;
		while(i<=n)
		{ 
			if(a1[k][k]==0) 
			{
				printf(" \nThese equtions can't be solve is this way.\n Press any Key to continue...");
				getch();                    
				return 0;
			}
			if(i!=k)
			{ if((m=0-a1[i][k]/a1[k][k])==0) {i++; continue;}
			else {for(j=k+1;j<=n;j++)
			a1[i][j]=a1[i][j]+a1[k][j]*m;
			b1[i]=b1[i]+b1[k]*m;}
			i++;}
			else i++;    
			}
	}
	/* yi xia ji suan x zhi */   
	for(i=n;i>=1;i--)
	x1[i]=b1[i]/a1[i][i];
	return 1;
}

/*
 * Computed
 */ 
double computed(double **a,int h,int l, int *c1,int n) /*计算系数行列式D值*/
{
	int i, j, p=1;
	double sum=0.0;
	
	if (h==n)
		sum=1.0;
	else {
		i=++h;
		c1[l]=0;
		for(j=1;j<=n;j++)
		if(c1[j])
		if(a[i][j]==0) p++;
		else {sum=sum+a[i][j]*computed(a,i,j,c1,n)*pow(-1,1+p); p++; }  
	 	c1[l]=1; 
 	}
	return sum;
}


void ncompute(double **a,double b[],double x[],int n,int *c,double h)      /*克莱姆法计算*/
{
	int i,j;
	double t[NUM];
	
	for(j=1;j<=n;j++)
	{
		 for(i=1;i<=n;i++)
		{
		t[i]=a[i][j];
		a[i][j]=b[i];
		}
		x[j]=computed(a,0,0,c,n)/h;
		for(i=1;i<=n;i++)
		a[i][j]=t[i];
 	}
}

int main(void)
{
	double x[NUM];
	double b[NUM];
	int i,j=2,n=0;
	int *c;
	double he;
	char m,decision;
	double **a;
	
	a=(double**)malloc(NUM*sizeof(double*));
	for (i=0; i<NUM; i++)
		a[i]=(double*)malloc(NUM*sizeof(double));
	print();
	do{
		clrscr();
		do {
			if(n>=NUM) 
				printf("n is too large,please input again:\n");
			else
				printf("Please input the total number of the equations n(n<NUM): \n");
			scanf("%d",&n);
		} while(n>NUM);
		if(n==0) {
			for(i=1; i<NUM; i++) 
				free(a[i]);
			free(a);
		 	exit(1);
		}
		input(a,b,n);
		c=(int *)malloc((n+1)*sizeof(int));
		memset(c,1,(n+1)*sizeof(int));
		he = computed(a,0,0,c,n);
		if(fabs(he)>1e-4)   
		{
			Other:    chose();
			do{
				m=getche();
			}while(m!='a'&&m!='b'&&m!='A'&&m!='B'&&m!='c'&&m!='C'&&m!='d'&&m!='D'&&m!='e'&&m!='E');
			switch(m)
			{
			case 'a':
			case 'A': 
				j=gscompute(a,b,x,n);
				break;
			case 'b': 
			case 'B':
				j=gs_ydcompute(a,b,x,n); 
				break;
			case 'c':
			case 'C':
				j=ddcompute(a,b,x,n); 
				break;
			case 'd': ;
			case 'D': 
				j=1;
				ncompute(a,b,x,n,c,he);
				break;
			case 'e': ;
			case 'E':
			 	j=2;
		 		break;
			default:
			 	j=2;
		 		break;
			}
			if(j==1)
			{
				clrscr();
				printf("\n\n\n\n");
				printf("     D=%.4f \n",he);
				for(i=1;i<=n;i++){
					if(i%5==0)
					 printf("\n");
					printf("    %.4f    ",x[i]);}
				}
			else if(j==0)   
			{printf(" \nThese equtions can't be solve is this way.\nPlease chose the other way."); goto Other;}
			else {for(i=1; i<NUM; i++) free(a[i]);
			free(a);
			free(c);
			exit(1);}
		}
		else printf(" \n\n\tD=%.4f\n This linear equations hasn't accurate answer!",he);
		printf(" \n Do you want to continue?(Y/N) \n");
		do{
		decision=getchar();}while(decision!='y'&&decision!='Y'&&decision!='n'&&decision!='N');
	}while(decision=='y'||decision=='Y');
	for(i=1; i<NUM; i++) free(a[i]);
	free(a);
	free(c);
	return 0; 
}
