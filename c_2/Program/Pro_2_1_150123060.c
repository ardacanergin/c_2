//*********************************************************
//Arda Can Ergin 150123060
//The purpose of this program is to print the median of an array
//Input is taken from the user via file reading
//file format must be addNumber[space]'number'\n, findMedian\n
//some comment lines used for debugging and left intentionally
//*********************************************************

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>


void addNumber(int* numArray, int size, int num);
void sortArray(int* numArray, int size);
double findMedian(int* numArray, int size);
void copyArray(int maxSize,int size,int row,int original[], int copy[][maxSize+1]);
void explanationPrint(int size,int row,int matrix[][size+1]);

//implemented for debug reasons
void printArray(int* numArray, int size) {
    //puts("in method");
    for(int i=0; i<size; i++) {
        if(i==size-1) {
            printf("%d",numArray[i]);
        } else
            printf("%d,",numArray[i]);
    }
}

int main() {
    //open file and check if it can be opened
    FILE *file;
    if((file= fopen("input.txt","r"))==NULL) {
        puts("file can not be opened");
    } else {
        //puts("file opened successfully");
    }

    int size=0;
    int sizeExp=0;

    const char addnum[] ="addNumber";
    const char findmed[]="findMedian";

    //read the file 1st time so that we now what will be the size of my numArray
    char charArray[11];//the possible biggest number of characters can be find in input file, null character included

    while(!(feof(file))) {
        fscanf(file,"%s",charArray);
        if(strcmp(charArray,addnum)==0) {
            size++;
        } else if(strcmp(charArray,findmed)==0) {
            sizeExp++;
        }
    }

    //close the file
    if(fclose(file)==0) {
        //puts("file closed successfully");
    } else
        puts("file close error:1st");

    //printf("size: %d\n",size); for debugging
    int explanation[sizeExp][size+1];
    int numArray[size];
    int maxSize=size;
    int maxSizeExp=sizeExp;
    size=0;
    sizeExp=0;
    //need to keep to record of determined numArrays until a findMedian method is seen that will call explanation output
    //new FILE pointer to reset the pointer to start of the file
    FILE *file2;

    if((file2=fopen("input.txt","r"))==NULL) {
        puts("file open error");
    } else {
        //puts("file re-open successful");
    }

    //I could've used rewind method however we did not see that on lectures so closed and opened file again to
    //set the pointer at the beginning of the file
    //rewind(file);

    int num=0;
    char method[11];

    printf("\n----------------------\n");

    //loop to read the file
    while(!(feof(file2))) {
        //puts("inside while loop"); for debugging

        //decide what will be the method
        fscanf(file,"%s",method);
        //execute that method
        if(strcmp(method,addnum)==0) {
            size++;
            fscanf(file,"%d",&num);
            // printf("%num:%d\n",num); for debugging
            addNumber(numArray,size,num);
            sortArray(numArray,size);
            //printArray(numArray,size); for debugging
        }
        if(strcmp(method,findmed)==0) {
            sizeExp++;
            printf("Median of array: %.2lf\n",findMedian(numArray,size));
            copyArray(maxSize, size, sizeExp,numArray,explanation);
            //printf("%d",maxSize);
            //printf("%d",size);
            //printf("%d",sizeExp);
        }
    }

    explanationPrint(maxSize,sizeExp,explanation);

    //a different approach from what we saw in lecture
    /*while((value=fscanf(file,"%s",method))==1){
            puts("inside while loop");

        if(strcmp(method,addnum)==0){
            printf("before num scan %d\n",num);
            int value=fscanf(file,"%d", &num);
            printf("after num scan %d\n%d",num,value);

            addNumber(numArray,size,num);
            size++;
            sortArray(numArray,size);
            printArray(numArray,size);
            printf("in while %d\n",size);
        }
        if(strcmp(method,findmed)==0){
            printf("Median of array: %lf",findMedian(numArray,size));
        }
    }*/

    printf("\n----------------------\n");

    //close the second file
    if(fclose(file2)==0) {
        //puts("file cosed for second time");
    } else
        puts("file close error:2nd");
}

void sortArray(int* numArray, int size) {
    //insertion sort
    int temp,j;
    for(int i=1; i<size; i++) {

        temp=numArray[i];
        j=i-1;
        while((j>=0) && (numArray[j]>temp)) {

            numArray[j+1]=numArray[j];
            j--;
        }
        numArray[j+1]=temp;
    }
}

void addNumber(int* numArray, int size, int num) {
    numArray[size-1]=num;
}

double findMedian(int* numArray, int size) {
    double median;
    //printf("size: %d\n",size); for debugging
    //printf("first: %d\n",numArray[(size-1)/2]);
    //printf("second: %d\n",numArray[((size-1)/2)+1]);

    if(size%2==0) {
        median=(numArray[(size-1)/2]+numArray[(size-1)/2+1])*0.5;
    } else {
        median=numArray[(size-1)/2];
    }

    return median;
}

void copyArray(int maxSize,int size,int row,int original[], int copy[][maxSize+1]) {
    //main purpose of the method is to copy the array of integers that has been read before findMedian command, to a matrix
    //which will be used for printing the explanation, afterwards
    for(int i=0; i<size; i++) {
        copy[row-1][i]=original[i];

        //printf(" copy array: %d\n",copy[row-1][i]);
    }
    copy[row-1][maxSize]=size;
    //printf("size of copy: %d\n",copy[row-1][maxSize]);
}

void explanationPrint(int size,int row,int matrix[][size+1]) {
    printf("\n\nExplanation:\n");
    //printf("%d,",matrix[0][0]);
    //printf("%d\n",matrix[0][1]);
    //printf("%d,",matrix[1][0]);
    //printf("%d\n",matrix[1][1]);

    //print the explanation
    for(int i=0; i<row; i++) {

        int col=matrix[i][size];
        // printf("col is: %d\n",col);

        //create new array to split the explanation matrix, necessary since findMedian method will be used again
        int newArray[col];

        printf("Median of [");

        for(int j=0; j<col; j++) {
            if(j==col-1) {
                printf("%d", matrix[i][j]);
            } else {
                printf("%d,", matrix[i][j]);
            }
            newArray[j]=matrix[i][j];
        }

        printf("]");
        printf(" is ");
        if(col%2==0) {
            printf("(%d+%d",newArray[(col-1)/2],newArray[(col-1)/2+1]);
            printf(")/2 = ");
        }
            printf("%.2lf\n\n", findMedian(newArray, col));
    }
}

