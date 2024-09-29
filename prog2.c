/*
Name : Adil Aman Mohammed
Course : Formal language theory
Assignment no: 2
CWID : A20395630
Description: The following code is DFSM to Regular Expression Logic which converts the given DFSM to Regular Expressions
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>

#define MAX 1000
char buffer[MAX][MAX],transitions[MAX][MAX][MAX],target[1000],temp[1000];
char rev[MAX], outg[MAX], Solved[MAX];
int buffindex=0,DFSM=1,position=-1,found;

//to find the receiving states for a rip state
int findrev(int x)
{ int c=0;
    memset(buffer, '\0', sizeof(buffer));
    for(int i=0;i<buffindex;i++)
    {
        

            if(strcmp(transitions[i][x],"p")!=0)
            {
                char buffer[100];
                sprintf(buffer, "%d", i);
                if(c==0)
                {
                if(atoi(buffer)!=x)
                {
                strcpy(rev,buffer);
                c++;
                }
                }
                else
                {
                if(atoi(buffer)!=x)
                {
                strcat(rev,buffer);
                c++;
                }
                }
                
        }
         
    }
    //printf(" rev=%s",rev);
    return strlen(rev);
}


//to find the outgoing states for a rip state
int findout(int x)
{ 
    int c=0;
    memset(buffer, '\0', sizeof(buffer));
    for(int i=0;i<buffindex;i++)
    {
        

            if(strcmp(transitions[x][i],"p")!=0)
            {
                char buffer[100];
                sprintf(buffer, "%d", i);
                if(c==0)
                {
                if(atoi(buffer)!=x)
                {
                strcpy(outg,buffer);
                c++;
                }
                }
                else
                {
                if(atoi(buffer)!=x)
                {
                strcat(outg,buffer);
                c++;
                }
                }
                 
                
        }
         
    }
    //printf(" outg=%s\n",outg);
    return strlen(outg);
}

//print total matrix for debugging
void printmatrix()
{
    printf("\n\n\n\t");
    for(int i=0;i<buffindex;i++)
    {   
        printf("s%d\t",i);
    }
    printf("\n");


    for(int i=0;i<buffindex;i++)
    {
        printf("s%d\t",i);
        for(int j=0;j<buffindex;j++)
        {
            printf("%s\t",transitions[i][j]);
        }
        printf("\n\n");
    }
}

//algorithm as per the lecture ppt
void formula(int p,int q,int rip)
{
    if(p!=buffindex-1 && q!=0)
    {
        if(strcmp(transitions[p][q],"p")!=0)
        {
            strcpy(Solved, transitions[p][q]);
            strcat(Solved,"U");
        }
        if(strcmp(transitions[p][q],"eps")!=0)
        {
            strcpy(Solved, transitions[p][q]);
            strcat(Solved,"U");
        }
        strcat(Solved,transitions[p][rip]);
        strcat(Solved,"(");
        strcat(Solved,transitions[rip][rip]);
        strcat(Solved,")");
        strcat(Solved,"*");
        strcat(Solved,transitions[rip][q]);
        strcpy(transitions[p][q], Solved);
        //printf("solved =%s ",Solved);
        //printf("transitions[%d][%d]:%s ",p,q,transitions[p][q]);
        //printmatrix();
    }


}


//rip function 
void ripstate(int x)
{
    int m=findrev(x);
    int n=findout(x);

    //printf(" m=%d n=%d\n",m,n);


    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            char str_a[2]; // Adjust the size as needed
            char str_b[2];
            sprintf(str_a, "%c", rev[i]); // Convert rev[2] to a string
            sprintf(str_b, "%c", outg[j]);
            int a = atoi(str_a),b = atoi(str_b);
            //printf("\np=%d q=%d\n",a,b);

            formula(a,b,x);
        }
    }
    
}







int main(int argc, char *argv[])
{
	//verifying the command line argument
    if(argc!=2)
    {
        printf("The given no.of arguments are incorrect please check your arguments in command line:\n");
    }
    else
    {

    //printf("%s\n",argv[1]); //printing the input file name


    //open the 1nd file DFSM.txt
    FILE *file1 = fopen(argv[1], "r");
    if (file1 == NULL) 
    {
        perror("Check with DFSM.txt Error opening the file");
        return 1;
    }

    

    //Read lines and store non-empty lines (excluding lines with only spaces)
    while (fgets(buffer[buffindex], MAX, file1)) {
        int length = strlen(buffer[buffindex]);

        // Remove spaces from the line and store only non-space characters
        int newLength = 0;
        for (int i = 0; i < length; i++) {
            if (buffer[buffindex][i] != ' ' && buffer[buffindex][i] != '\n') {
                buffer[buffindex][newLength] = buffer[buffindex][i];
                newLength++;
            }
        }
        buffer[buffindex][newLength] = '\0'; // Null-terminate the modified line

        if (newLength > 0) {
            buffindex++;
        }
    }
    
    //Closing file 1
    fclose(file1);

    //printing the buffer index
    //printf("bufferindex:%d\n\n",buffindex);

    //check for file empty
    if(buffindex==0)
	{
		printf("\nDFSM.txt is empty\n");
        exit(0);
    }

    // printing the stored non-empty lines
    printf("\n<<<<<<<<<<<<<<Taken input: DFSM.txt>>>>>>>>>>>>>>>>\n\n");
    for (int i = 0; i < buffindex; i++) {
       printf("buffer[%d]: %s\n", i, buffer[i]);
    }
    
    //char temp;
    //temp=buffer[0][0];
    //printf("buffer[%d][%d]=%c\n",0,0,temp);

    //aphalet Length defining
    int alphalength=strlen(buffer[0]);
    //printf("\nalphalength:%d\n\n",alphalength);


    //accessing the buffer
    //printf("\nseparate :%c\n",buffer[4][0]);

 
    int finalstatelength= strlen(buffer[buffindex-1]);

    //printf("final state: %s\t FSlength :%d FSarrayIndex:%d\n ",buffer[buffindex-1],finalstatelength,buffindex-1);


     //check that the given transitions is valid DFSM or Not
    int V=0;
    for(int j=1;j<=alphalength;j++)
    {
        if(strlen(buffer[j])==alphalength)
        {
            //printf("buffer[%d]:%ld=alphalength:%d\n",j,strlen(buffer[j]),alphalength);
            V=0;
        }
        else{
            printf("transition is not valid state:%d length:%ld\n",j,strlen(buffer[j]));
	    printf("NO\n\n");
            //V=1;
            exit(0); //can use exit(1);
        }
    }

    //printf("V=%d\n\n\n",V); //V is a flag to indicate that the given transition is invalid


    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Conversion of transition<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //if v is not flaged then proceed
    if(V==0)
    {
        
    

    //strcpy(transitions[0][1],"vasu");
    //printf("new=%s\n",transitions[0][0]);

    //assigning  0 to all NxN elements
    for(int i=0;i<buffindex;i++)
    {
        for(int j=0;j<buffindex;j++)
        {
            strcpy(transitions[i][j],"p");
        }
    }

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Printing the 0 assigned matrix<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    /*printf("\t");
    for(int i=0;i<buffindex;i++)
    {   
        printf("s%d\t",i);
    }
    printf("\n");


    for(int i=0;i<buffindex;i++)
    {
        printf("s%d\t",i);
        for(int j=0;j<buffindex;j++)
        {
            printf("%s\t",transitions[i][j]);
        }
        printf("\n\n");
    }*/

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>print matrix<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Conversion of given input<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    for(int i=1;i<buffindex-1;i++)
    { 
        for(int target=1;target<buffindex-1;target++)
        { 
        for(int j=0;j<alphalength;j++)
        {   
            int num = buffer[i][j] - '0';
            if(num==target)
            {
                if(strcmp(transitions[i][target],"p")==0)
                {
                    strncpy(transitions[i][target], &buffer[0][j], 1);
                }
                else
                {
                    strcpy(temp, "(");
                    

                    strcat(transitions[i][target], "U");
                    strcat(transitions[i][target], &buffer[0][j]);
                    strcat(transitions[i][target], ")");
                    strcat(temp, transitions[i][target]);
                    strcpy(transitions[i][target], temp);
                }
            }
            else
            {
                //printf("not found buffer[%d][%d]:%d!=%d\n",i,j,num,target);
            }
            
        }
        }
    }

    //Initializing New start state value
    strcpy(transitions[0][1], "eps");

    for(int i=0;i<finalstatelength;i++)
    {
        int temp2;
        temp2=buffer[buffindex-1][i]-'0';
        //printf("index=%d buffer[%d][%d]=%d",buffindex-1,buffindex-1,i,buffer[buffindex-1][i]);
        //printf("  temp2=%d\n",temp2);
        strcpy(transitions[temp2][buffindex-1],"eps");
    }


    //<<<<<<<<<<<<<<<<printing the converted input>>>>>>>>>>>>>>>>
    printf("\n <<<<<<<<<<<Converted Input matrix>>>>>>>>>>");

     printf("\n\n\n\t");
    for(int i=0;i<buffindex;i++)
    {   
        printf("s%d\t",i);
    }
    printf("\n");


    for(int i=0;i<buffindex;i++)
    {
        printf("s%d\t",i);
        for(int j=0;j<buffindex;j++)
        {
            printf("%s\t",transitions[i][j]);
        }
        printf("\n\n");
    }

    //printf("%s\n",transitions[3][3]); //debugging


    //<<<<<<<<<<<<<<<<<<<<<<<<Finding Rip Combination and rip the state >>>>>>>>>>>>>>>>>

    for(int rip=1;rip<buffindex-1;rip++)
    { 
        //printf("\nrip=%d ",rip);
        ripstate(rip);
   

    }

    printf("\nThe Regular Expression :");
    printf("(S,F)= %s\n\n",transitions[0][buffindex-1]);

    }
    }
}

    
