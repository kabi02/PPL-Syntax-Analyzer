#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "includes/tokens.h"

char file[10];
FILE *fp;
char *ext;
int popincrement;
int LineNum=1,ErrorCount = 0;

typedef struct tokens{
    char token;
    struct tokens *next;
}tokens; tokens *bottomOfStack = NULL;

int InsertPush(tokens *curr, char token){
    tokens * newtoken = curr;
     if(bottomOfStack == NULL){
        bottomOfStack = (tokens*)malloc(sizeof(tokens));
        bottomOfStack->token = token;
        bottomOfStack->next = NULL;
        return 0;
    }
    while (newtoken->next != NULL){
        newtoken = newtoken ->next;
    }
    newtoken->next = malloc(sizeof(tokens));
    newtoken->next->token = token;
    newtoken->next->next = NULL;
    return 0;
}

void printlist(tokens *bottomOfStack){
    tokens * current = bottomOfStack;
    while (current != NULL){
        printf("%c",current->token);
        current = current->next;
    }
}

char poptoken(tokens *bottomOfStack){
    tokens * current = bottomOfStack;
    while (current->next!=NULL)
    {
        current = current->next;
    }
    return current->token;
}

char popfirsttoken( tokens *bottomOfStack){
    tokens *current = bottomOfStack;
    for(int i = 0; i<popincrement;i++){
        current = current->next;
    }
    popincrement++;
    return current->token;
}

bool isDecStmt(char Token);
bool isAssStmt(char Token);

//Supporting function for comparing
bool isEqual(const char *str1, const char *str2) {
    for (; *str1 && *str2 && *str1 == *str2; str1++, str2++);
    return (!(*str1) && !(*str2))? true : false;
}

void popUntilSemiColon(char temp){
    while(temp != 'Q'){
         switch (temp)
         {
         case 'Q':
            break;
         case '1':case '2':case '3':case '4':case '5':case '6':case '8':case '9':case 'a':
            LineNum++;
            isDecStmt(temp);
            break;
        default:
            break;
        }
        temp = popfirsttoken(bottomOfStack);
    }
    LineNum++;
    isDecStmt(popfirsttoken(bottomOfStack));
}

void DatatypeDecLoop(char currToken){
    if(currToken == '0'){
        currToken = popfirsttoken(bottomOfStack);
        if(currToken == 'Q'){
            printf("end of Variable Declaration\n");
            LineNum++;
            isDecStmt(popfirsttoken(bottomOfStack));
        }else if(currToken == 'w'){
            currToken = popfirsttoken(bottomOfStack);
            switch (currToken)
            {
            case '0': case 'l': case 'm': case 'n': case 'o': case 'p':
                currToken = popfirsttoken(bottomOfStack);
                    if(currToken == 'Q'){
                        printf("This is a Variable assignment\n");
                        LineNum++;
                        isDecStmt(popfirsttoken(bottomOfStack));
                    }else if(currToken == 'R'){
                        currToken = popfirsttoken(bottomOfStack);
                        DatatypeDecLoop(currToken);

                    }else{
                        printf("error at datatype declaration expecting ';' or ','\n");
                        ErrorCount++;
                        popUntilSemiColon(currToken);    
                    }
                break;

            default:
                printf("Teka lang chong expected na identifier or constant eh, nasaan na?\n");
                ErrorCount++;
                popUntilSemiColon(currToken);    
                break;
            }
        }else if(currToken=='R'){
            currToken=popfirsttoken(bottomOfStack);
            DatatypeDecLoop(currToken);
        }else
            printf("Expected ';' ',' or '=' \n");
            ErrorCount++;
            popUntilSemiColon(currToken);    
    }else{
        printf("teka lang kulang ng identifier d2\n");
        ErrorCount++;
        popUntilSemiColon(currToken);    
        
    }

}

bool isAssStmt(char currToken){
    if(currToken == identifier) {
        currToken = popfirsttoken(bottomOfStack);
        if(currToken == Equal_opr) {
            currToken = popfirsttoken(bottomOfStack);
            switch (currToken)
            {
            case identifier: case int_const: case str_const: case bool_const: case dec_const: case char_const:
                currToken = popfirsttoken(bottomOfStack);
                if(currToken == SemiColon_delim) {
                    printf("\nLine: %d this is an Assignment Statement - ", LineNum);
                    printf("End of ass stmt\n");
                    LineNum++;
                    isAssStmt(popfirsttoken(bottomOfStack));
                }
                else if(currToken == Comma_delim) {
                    printf("loop lodi\n");
                    currToken = popfirsttoken(bottomOfStack);
                    isAssStmt(currToken);
                }
                break;
            
            default:
                break;
            }
        }
    }
}

bool isDecStmt(char Token) {
    char currToken;
    switch (Token)
    {
    case '1':  case '2':  case '3':  case '4':  case '5': // Datatypes
        printf("\nLine: %d This is a Variable Declaration  -  ",LineNum);
            currToken = popfirsttoken(bottomOfStack);
            DatatypeDecLoop(currToken);
        break;

    default:
        printf("Parse Done with Error: %d\n",ErrorCount);
        break;
    }
}

bool isReadStmt(char currToken) {
    if(currToken == read_keyword) {
        currToken = popfirsttoken(bottomOfStack);
        if(currToken == OpenParenthesis) {
            currToken = popfirsttoken(bottomOfStack);
            if(currToken == identifier) {
                currToken = popfirsttoken(bottomOfStack);
                if(currToken == CloseParenthesis) {
                    currToken = popfirsttoken(bottomOfStack);
                    if(currToken == SemiColon_delim) {
                        printf("Line %d - Start of read stmt - ", LineNum);
                        printf("End of read stmt\n");
                        LineNum++;
                    }
                }
            }
        }
    }
}

bool isUnary(char currToken) {
    if(currToken == identifier) {
        
    }
}

bool isIterative(char currToken) {
    if(currToken == while_keyword) {
        currToken = popfirsttoken(bottomOfStack);
        if(currToken == OpenParenthesis) {
            currToken = popfirsttoken(bottomOfStack);
        }
    }
}

void fileOpen(){
    int confirm, hasPeriodt = 0;
    while(1){
        printf("Enter File Name: ");
        scanf("%s",&file);
        for(int i = 0; i < strlen(file); i++){
            if(file[i] == '.'){
                hasPeriodt = 1;
                break;
            }
        }
        if(hasPeriodt == 0){
            printf("Error! Missing File Extension.\n\n");
            printf("Do you want to try again? (0-Yes / 1-No) : ");
                scanf("%d",&confirm);
                if(confirm == 0)
                    continue;
                else
                    exit(0);
        }

        ext = strrchr(file, '.');
        if(isEqual(ext, ".txt")){
            fp = fopen(file,"r");
            if(fp == NULL) {
		        printf("Error! Can't find file.\n\n");
                printf("Do you want to try again? (0-Yes / 1-No) : ");
                scanf("%d",&confirm);
                if(confirm == 1)
                    exit(0);
	        }
            else
                break;

            fclose(fp);
        } 
        else{
            printf("Error! Incorrect file extension.\n\n");
            printf("Do you want to try again? (0-Yes / 1-No) : ");
                scanf("%d",&confirm);
                if(confirm == 1)
                    exit(0);
        }
    }
}

bool inserter(){
    FILE * fp = fopen(file, "r");
    char c;
    int size = 0, flag = 0;
    fp = fopen(file, "r");
    do {
        c = fgetc(fp);
        if(c == '\t') {
            flag = 1;
            while(flag == 1) {
                c = fgetc(fp);
                if(c == '\n' || c == EOF) {
                    flag = 0;
                    break;
                }
            }
        }
        if(c!='\n')
            InsertPush(bottomOfStack, c);
    }while(!feof(fp));
    //printf("%d", size);
}

int main(){
    fileOpen();
    inserter();
    isReadStmt(popfirsttoken(bottomOfStack));
    return 0;
}