//Arda Can Ergin 150123060
//*************************************************************
//The purpose of this program is to make simple calculations such as summation and extraction
//only characters that can be used are +, -, (, (, ' '
//program give precedence the operations inside the most inner parentheses and skips the spaces
//entering other characters than provided ones results in error
//please compile with -std=c99 and make sure that your directory is accessible by current user since program uses file writing and reading
//also if file open fails disable the anti-virus software, sometimes anti-virus softwares, see IDE as a virus and make them unable to
//access to a file
//**************************************************************


#include <stdio.h>
#include <stdlib.h>
#include<string.h>


int calculate(char *s);
char *read(char *cal,FILE *input);
int checkError(char *cal);
char *findParentheses(char *s);

//method used for debugging
void printString(char *s) {
    printf("\n");
    int i=0;
    while(s[i]!='\0') {
        printf("%c ",s[i]);
        i++;
    }
    printf(" -endOfArray\n");
}

int main() {

    //take the string input on the console and write it to a file
    //that was the easiest way i can think of to manage a string without predetermined size
    FILE *file;
    file = fopen("input.txt","w");
    if(file==NULL) {
        puts("file open failed");
        perror("Error opening file");
        exit(EXIT_FAILURE);
    } else {
        //puts("file open successfull");
    }
    printf("Enter a mathematical operation that only contains ||'(',')','+','-',' ' and digits||\n"
           "(Press enter to end input):\n");

    char temp;
    int size=0;
    while(1) {
        temp = getchar();
        if(temp=='\n') {
            fputc(temp,file);
            break;
        } else {
            fputc(temp,file);
            size++;
        }
    }

    fclose(file);
    //printf("%d",size);

    char cal[size+1];
    //puts("cal initialized");

    FILE *newFile;
    //to set the file pointer to beginning of the file
    //i would normally use rewind() however we did not see that in the lectures
    newFile = fopen("input.txt","r");
    if(newFile==NULL) {
        puts("newFile open failed");
    } else {
        //puts("newFile open success");
    }
    read(cal,newFile);

    if(checkError(cal)) {
        puts("ERROR INVALID INPUT");
        return -1;
    }
    //puts("after read");
    //printString(cal);
    printf("result: %d",calculate(cal));
}

//function to read a file and write a char array
char *read(char *cal, FILE *file) {

    char ch;
    int i=0;
    while(1) {
        ch=fgetc(file);
        if(ch=='\n' || ch =='\0') {
            cal[i]='\0';
            //puts("end of file");
            break;
        } else {
            cal[i]=ch;
        }
        i++;
    }
    fclose(file);
    return cal;
}

//function to calculate
int calculate(char *s) {
    int num=0;
    int result=0;
    int sign=1;
    int i=0;

    while(s[i]!='\0') {
        //skip spaces
        if(s[i]==' ') {
            i++;
            continue;
        }
        //extract number
        while(s[i]>='0' && s[i]<= '9') {
            num = num*10 + s[i]-'0';
            i++;
        }
        //calculate result
        result += num*sign;
        num=0;

        //determine signs (order is irrelevant)
        if(s[i]=='+') {
            sign=1;
            i++;
        }
        if(s[i]=='-') {
            sign=-1;
            i++;
        }
        //recursive approach for inside the parentheses
        if(s[i]=='(') {
            char *end;
            end = findParentheses(&s[i]);
            int size;
            if(end==NULL) {
                puts(") could not be found");
                printString(*s);
                exit(1);
            }
            size= end-&s[i]-1;
            char *subOp;
            subOp= (char*)malloc(size+1);
            if(subOp==NULL) {
                puts("allocation failed");
            }
            strncpy(subOp,&s[i+1],size);
            subOp[size]='\0';
            //printString(subOp);
            result += sign*calculate(subOp);
            free(subOp);
            i= end-s+1;//+2 for skipping both of the parentheses
        }
        //some expressions used for debugging
        /*if(s[i]=='\0'){
         puts("malfunction");
        }*/
        //printf("%d\n",result);
    }
    return result;
}
//method needed to correctly determine the placement of the parentheses
char *findParentheses(char *s) {
    int counter=0;
    int i=0;
    //puts("outside of while");
    while(s[i]!='\0') {
        //printf("inside of while %d\n",i);
        if(s[i]=='(') {
            counter++;
        }
        if(s[i]==')') {
            counter--;
        }
        if(counter==0) {
            //puts("parentheses is found");
            return &s[i];
        }
        i++;
    }
    puts("parentheses find failed");
}

int checkError(char *s) {
    int leftP=0;
    int rightP=0;
    int i=0;

    if(s[0]=='+' || s[0] =='-') {
        printf("error: unary operator-%d\n",i);
        return 1;
    }

    while(s[i]!='\0') {

        //check if all characters are valid
        if(s[i]>='0' && s[i]<='9' ) {
            //puts("is digit");
        } else if (s[i]=='-' || s[i]=='+') {
            if(s[i+1]=='+' || s[i+1]=='-') {
                printf("error: unary operator-%d\n",i);
                return 1;
            }
            //puts("is operator");
        } else if(s[i]==' ') {
            //puts("is space");
        } else if(s[i]=='(' || s[i]==')') {
            if(s[i]=='(') {
                if(s[i+1]=='+' || s[i+1]=='-') {
                    printf("error: unary operator-%d\n",i);
                    return 1;
                }
                leftP++;
            } else {
                rightP++;
            }
            //puts("is parentheses");
        } else {
            puts("invalid character: input must only contain digits, spaces, parentheses, '+' and '-' operators");
            return 1;
        }
        i++;
    }
    //check if all parentheses closed correctly
    if(rightP!=leftP) {
        puts("error: unclosed parentheses exits");
        return 1;
    }
    return 0;
}

