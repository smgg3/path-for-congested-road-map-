/*
Implemented by
Authors:
Sravani Murakonda
Prasanna Muppidi
Harshini Medikonda
Time:11:30PM
Subject : Design and Analysis of Algorithms
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

#define INF 10000000                                                    //to define infinite value i.e no path between i and j

//#define FILENAME "input1.txt"
//#define FILENAME "input2.txt"
//#define FILENAME "N10bs.txt"
//#define FILENAME "N10cs.txt"
//#define FILENAME "N10ds.txt"
//#define FILENAME "N10tb.txt"
//#define FILENAME "N10ts.txt"
//#define FILENAME "N15as.txt"
//#define FILENAME "N15bs.txt"
//#define FILENAME "N20as.txt"
//#define FILENAME "N20bs.txt"
//#define FILENAME "N25ab.txt"
//#define FILENAME "N25as.txt"
//#define FILENAME "N30as.txt"
//#define FILENAME "N30ab.txt"
//#define FILENAME "N35as.txt"
//#define FILENAME "N35ab.txt"
//#define FILENAME "N50as.txt"
//#define FILENAME "N50ab.txt"
//#define FILENAME "N75as.txt"
#define FILENAME "N75ab.txt"


clock_t start; clock_t end;  clock_t dif;                               //defines variables for clock

int main(){
        printf("\n****************************************************\n\nGivenExampleStrategy\n\n");
        start=clock();                                                  //Starts the clock to measure running time of the program
        int count=0,i,j,k,a,b;                                          //Defines Counter for key-basic-operations to 0 for storing no.of key basic operations
	int N,S,D;                                                      //Defines 3 integers N,S,D to read and store no.of nodes,Source,Destination from input file
	FILE *f=fopen(FILENAME,"r");                                    //Opens the input file in read mode
	const char s[2]=",";                                            //To split input file using delim , using s
	char *token,line[20];                                           //Defines token to store split strings one at a time in each line,and line to read each input file line into it
        char mat_type;                                                  //mat_type stores the type of input line whether F or C or E
        int from,to,val;                                                //from->to=val edge cost
	if(f!=NULL)                                                     //Checks file is null or not and proceeds if not null
	{
		if(fgets(line,sizeof line,f)!=NULL)                             //Checks whether the line read is null or not and proceeds if not null
                {
		        token=strtok(line,s);                                   //strtok splits line depends on s i.e "," here
		        N=atoi(token);                                          //atoi function Converts token string fromat to int
		        token = strtok(NULL,s);                                 //It removes next null value in the input file
		        S=atoi(token);                                          //atoi function Converts token string fromat to int                                
		        token = strtok(NULL,s); 
		        D=atoi(token);                                          //atoi function Converts token string fromat to int
		        token = strtok(NULL,s);                                 //It removes next null value in the input file
		        printf("Size of Given input Graph is : %d\n",N);        //Prints size of the given Graph matrix
		}
		int E[N+1][N+1],F[N+1][N+1],C[N+1][N+1],G[N+1][N+1],MyDist[N+1][N+1],Hop[N+1][N+1],Parent[N+1][N+1],Path[N+1][N+1][N+1];//Edge Cost Matrix,Flow Matrix,Capacity Matrix,Adjacency Matrix,All Pairs Shortest Path,Hop Count Matrix,Parent Matrix,Path Matrix
		float Load[N+1][N+1];                                           //Load Matrix
		for(i=1;i<=N;i++)                                               //Loop intializes the above defined matrices i,j pair values
                        for(j=1;j<=N;j++)
                        {
                                E[i][j]=INF;F[i][j]=0;C[i][j]=0;G[i][j]=0;MyDist[i][j]=INF;Load[i][j]=0;
			        if(i==j)
                                       {E[i][j]=0;MyDist[i][j]=0;Hop[i][j]=0;Parent[i][j]=i;}       
                        }

		for(i=1;i<=N;i++)                                               //Using 3-D array to store path
                        for(j=1;j<=N;j++)
                                for(k=0;k<=N;k++)
                                        if(k==0)
                                                Path[i][j][k]=1;                //Defines Path[i][j][0] is to store the next available position for inserting path node and initially index 1 location 
                                        else
                                                Path[i][j][k]=0;                //Initializes to 0
		while(fgets(line, sizeof line, f) != NULL)                      //Reads the input file till the end
		{		
			token = strtok(line, s);
			for(i=1;i<5;i++) 
			{ 
					if(i==1&&token)
						mat_type=token[i];              //assigns first val in line to mat_type
					else if(i==2&&token)
                                                from=atoi(token);	        //assigns second value to from					
					else if(i==3&&token)
						to=atoi(token);                 //assigns third value to to 
					else if(i==4&&token)
						val=atoi(token);                //assigns fourth value to val i.e from->to=val
					token = strtok(NULL,s);                 //removes null values in input line
			} 
			switch (mat_type)                                       //Assigns input values to E,F,C based on mat_type
			{
				case 'E':
					{E[from][to]=val;MyDist[from][to]=val;G[from][to]=1;Parent[from][to]=from;break;}//if mat_type is E assigns val to E matrix and defines G,MyDist,Paent matrices
				case 'F':
					{F[from][to]=val;break;}                                                        //if mat_type is F assigns val to F matrix
				case 'C':
					{C[from][to]=val;break;}                                                        //if mat_type is C assigns val to C matrix
			}
		} 
	        /*Finding All Pairs Shortest Path between every pair of nodes*/
		for(k=1;k<=N;k++)
			for(i=1;i<=N;i++)
				for(j=1;j<=N;j++)
					if(MyDist[i][k]+MyDist[k][j]<MyDist[i][j])                                      //Checks Floyd Warshall Condition to find shortest path
					{
						MyDist[i][j]=MyDist[i][k]+MyDist[k][j];count++;                         //if condition satisfies then inserts k node in i,j path
						Parent[i][j]=Parent[k][j];	                                        //changes the parent matrix and assigns parent of i,j as k
					}
		/*Calculates Path Matrix*/
		for(i=1;i<=N;i++)
			for(j=1;j<=N;j++)
			{
				a=i;b=j;
				for(k=1;k<=N&&a!=b;k++)
				{
					Path[i][j][Path[i][j][0]]=b;                            //inserts b into path matrix i.e j or parent of a,b
					b=Parent[a][b];                                         //assigns parent of a,b to b
					Path[i][j][0]++;count++;                                //increase next available location by 1 to store path nodes
				}
				Path[i][j][Path[i][j][0]]=a;                                    //inserts i into the starting of the path
			}                       
		/*Print Path Matrix*/
		printf("Path Matrix :\n");
		for(i=1;i<=N;i++)
		{
			printf("|");
			for(j=1;j<=N;j++)
			{
				printf("\t(");
				for(k=Path[i][j][0];k>0;k--)
					printf("%d,",Path[i][j][k]);
				printf(")\t");
				Hop[i][j]=Path[i][j][0]-1;
			}
			printf("\t|\n");
		}
		/*Print Hop Count Matrix */
		printf("Hop Count Matrix :\n");
		for(i=1;i<=N;i++)
		{
			printf("|");
			for(j=1;j<=N;j++)
				printf("%d\t",Hop[i][j]);                                       //print hop count of i,j path
			printf("\t|\n");
		}
		/*Calculates Load Matrix*/
		for(i=1;i<=N;i++)
			for(j=1;j<=N;j++)
				for(k=Path[i][j][0];k>1;k--)
					{Load[Path[i][j][k]][Path[i][j][k-1]]=Load[Path[i][j][k]][Path[i][j][k-1]]+F[i][j];  count++;}            //Calculates load considering total flow and counter++
		float coef;
                float NCM[N+1][N+1],Final_Delay[N+1][N+1];                                   //new congestion edge matrix and final shortest path delay matrix
		for(i=1;i<=N;i++){for(j=1;j<=N;j++){NCM[N+1][N+1]=0;Final_Delay[i][j]=0;}}   //initializes NCM,Final_Delay
                /*Finding Congested Edge Matrix  When single car is in the system*/
		for(i=1;i<=N;i++)
		{
			for(j=1;j<=N;j++)
			{
				if(E[i][j]!=INF&&i!=j)
                                {
                                if(Load[i][j]<=C[i][j]){
				coef=(C[i][j]+1)/(C[i][j]+1-Load[i][j]);                        //calculates coefficient for congestion
				NCM[i][j]=coef*E[i][j];     }                                    //calculates congestion edge cost for i,j
                                count=count+5;                                                  //increments counter by 5
                                }
			}
		}
		printf("\nCongestion Edge Matrix :\n");
		for(i=1;i<=N;i++)
		{
			printf("|");
			for(j=1;j<=N;j++)
			{
				
				if(NCM[i][j]<0)
					NCM[i][j]=0;
                                if(Load[i][j]>C[i][j])
                                        printf("-nan\t");
                                else if(Load[i][j]==0&&i!=j)
                                        printf("na\t");
                                else
                                        printf("%.2f\t",NCM[i][j]);                             //prints congestion edge matrix
				Final_Delay[i][j]=NCM[i][j];
			}
			printf("\t|\n");
		}
		for(i=1;i<=N;i++)
		{
			for(j=1;j<=N;j++)
			{
				if(Load[i][j]==0&&i!=j)Final_Delay[i][j]=0;
			}
		}
		for(i=1;i<=N;i++)
		{
			for(j=1;j<=N;j++)
			{
				for(k=Path[i][j][0];k>1;k--)
				{
						if(Path[i][j][0]>2)
						{Final_Delay[i][j]=NCM[Path[i][j][k]][Path[i][j][k-1]]+Final_Delay[i][j];count++;}//Calculates Final Congestion shortest path
				}
			}
		}
                printf("\nPredicted Path Delay Matrix :\n");
		for(i=1;i<=N;i++)
		{
			printf("|");
			for(j=1;j<=N;j++)
			{
                                if(i==j)
                                        MyDist[i][j]=0;
				printf("%d\t",MyDist[i][j]);                                             //prints final delay matrix
			}
			printf("\t|\n");
		}
		printf("\nCongestion Actual Delay Matrix :\n");
		for(i=1;i<=N;i++)
		{
			printf("|");
			for(j=1;j<=N;j++)
                                if(Load[i][j]>C[i][j])
                                        printf("-nan\t");
                                else
				printf("%.2f\t",Final_Delay[i][j]);
			printf("\t|\n");
		}
                printf("*****************Final Output :*****************\n");
                printf("\nShorest Path between source %d and destination %d is: %d.\n\n",S,D,MyDist[S][D]);//prints shortest path between given source and destination
		printf("\nShorest Path between source %d and destination %d is: %.2f.\n\n",S,D,Final_Delay[S][D]);//prints shortest path between given source and destination with congestion
                printf("\nHop Count for source %d and destination %d is: %d.\n",S,D,Hop[S][D]);//prints hop count for given source and destination with congestion
        }
          
        end=clock();                                                                                            //ends the clock
        dif=end-start;                                                                                          //calculates total running time into diff
        count++;                                                                                                //increments counter by 1
        printf("\nTotal Running Time of the Algorithm in Seconds is %.7f\n\n",(float)(dif)/CLOCKS_PER_SEC);     //prints Total running time of the algorithm
        printf("\nTotal no.of Key-Basic Operations are : %d\n\n***********************************\n",count);                                        //prints counter for no.of key basic operations
}
