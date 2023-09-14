#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 1000
char buffer[MAX][MAX],transitions[MAX][MAX][MAX],target[1000],temp;
int buffindex=0,DFSM=1,position=-1,found;

int main(int argc, char *argv[])
{
	//verifying the command line argument
    if(argc!=2)
    {
        printf("The given no.of arguments are incorrect please check your arguments in command line:\n");
    }
    else
    {

    printf("%s\n",argv[1]); //printing the input file name


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
    printf("bufferindex:%d\n\n",buffindex);


    // printing the stored non-empty lines
    for (int i = 0; i < buffindex; i++) {
       printf("buffer[%d]: %s\n", i, buffer[i]);
    }
    
    //char temp;
    //temp=buffer[0][0];
    //printf("buffer[%d][%d]=%c\n",0,0,temp);

    //aphalet Length defining
    int alphalength=strlen(buffer[0]);
    printf("\nalphalength:%d\n\n",alphalength);


    //accessing the buffer
    //printf("\nseparate :%c\n",buffer[2][0]);

 
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
        
    }

    //strcpy(transitions[0][1],"vasu");
    //printf("new=%s\n",transitions[0][0]);

    //assigning  0 to all NxN elements
    for(int i=0;i<buffindex-1;i++)
    {
        for(int j=0;j<buffindex-1;j++)
        {
            strcpy(transitions[i][j],"0");
        }
    }

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Printing the 0 assigned matrix<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    printf("\t");
    for(int i=0;i<buffindex-1;i++)
    {   
        printf("s%d\t",i);
    }
    printf("\n");


    for(int i=0;i<buffindex-1;i++)
    {
        printf("s%d\t",i);
        for(int j=0;j<buffindex-1;j++)
        {
            printf("%s\t",transitions[i][j]);
        }
        printf("\n\n");
    }

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
                printf("found buffer[%d][%d]:%d==%d\n",i,j,num,target);
                if(j==0)
                {

                    strcpy(transitions[i][target],"a");
                }
                
                if(j==1)
                {
                    strcpy(transitions[i][target],"b");
                }

            }
            else
            {
                printf("not found buffer[%d][%d]:%d!=%d\n",i,j,num,target);
            }
            
        }
        }
    }

    //
    strcpy(transitions[1][2],"b");

    // printing the converted input

     printf("\n\n\n\t");
    for(int i=0;i<buffindex-1;i++)
    {   
        printf("s%d\t",i);
    }
    printf("\n");


    for(int i=0;i<buffindex-1;i++)
    {
        printf("s%d\t",i);
        for(int j=0;j<buffindex-1;j++)
        {
            printf("%s\t",transitions[i][j]);
        }
        printf("\n\n");
    }












    

    }
}

    
