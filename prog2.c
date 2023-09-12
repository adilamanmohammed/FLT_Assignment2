#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 1000
char buffer[MAX][MAX],statenum;
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

    printf("%s\n",argv[1]); //printing the input files names


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

    //aphalet Length defining
    int alphalength=strlen(buffer[0]);
    printf("alphalength:%d\n",alphalength);


    //accessing the buffer
    //printf("\nseparate :%c\n",buffer[2][0]);

 
    int finalstatelength= strlen(buffer[buffindex-1]);

    printf("final state: %s\t FSlength :%d FSarrayIndex:%d\n ",buffer[buffindex-1],finalstatelength,buffindex-1);



    }
}

    
