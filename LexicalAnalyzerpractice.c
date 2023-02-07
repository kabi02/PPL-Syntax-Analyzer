#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "includes/tokens.h"

bool isIdentifier(const char* ch);
bool isKeyword(const char *str);
bool isReservedword(const char *str);
bool isEqual(const char *str1, const char *str2);
bool isInt(const char* str);
bool isDecimal(char* str);
bool isBoolConst(const char *str);
bool isNoiseword(const char *str);
bool isOperator(char before, char cur, char next);
bool isOP(char ch);
bool isDelimiter(char ch);
bool isBrackets(char ch);
bool isSymbol(const char* str);
char* subString(const char* str, int left, int right);
void fileToString(char *str);
void outputFile(char *str);
const char * opNameA(char str);
const char * opNameB(char str1, char str2);

typedef struct tokens{
    char token;
    struct tokens *next;
}tokens;

    tokens *bottomOfStack = NULL;

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
        printf("%c\n",current->token);
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

//Implementing Function
int main(){
    

	char str[1500];
    fileToString(str);
	printf("Creating a text file for Symbol Table...\n");
	outputFile(str);
    
	printlist(bottomOfStack);

    return (0);
}

//Return true if input is an identifier
bool isIdentifier(const char* ch) {
	if (ch[0] == '0' || ch[0] == '1' || ch[0] == '2' ||
		ch[0] == '3' || ch[0] == '4' || ch[0] == '5' ||
		ch[0] == '6' || ch[0] == '7' || ch[0] == '8' ||
		ch[0] == '9' || isDelimiter(ch[0]) || isSymbol(ch))
		return (false);
	return (true);
}

//Return true if input is a keyword
bool isKeyword(const char* str) {
    switch (str[0]) {
        case 'b':
            if (str[1] == 'o')
                if (str[2] == 'o')
                    if (str[3] == 'l')
                        if (str[4] == 'e')
                            if (str[5] == 'a')
                                if (str[6] == 'n') 
                                    if (str[7] == '\0'){ 
                                        InsertPush(bottomOfStack, boolean_keyword); 
                                        return true;
                                    }else return false;
            if (str[1] == 'r')
                if (str[2] == 'e')
                    if (str[3] == 'a')
                        if (str[4] == 'k') 
                            if (str[5] == '\0'){
                                InsertPush(bottomOfStack, break_keyword); 
                                    return true;
                                } else return false;
        case 'c':
            if (str[1] == 'h')
                if (str[2] == 'a')
                    if (str[3] == 'r') 
                        if (str[4] == '\0'){ 
                            InsertPush(bottomOfStack, char_keyword); 
                            return true; 
                        }else return false;
            if (str[1] == 'o')
                if (str[2] == 'n')
                    if (str[3] == 't')
                        if (str[4] == 'i')
                            if (str[5] == 'n')
                                if (str[6] == 'u')
                                    if (str[7] == 'e') 
                                        if (str[8] == '\0'){
                                        InsertPush(bottomOfStack, continue_keyword);  
                                        return true; 
                                        }else return false;
        case 'd':
            if (str[1] == 'e')
                if (str[2] == 'c')
                    if (str[3] == 'i')
                        if (str[4] == 'm')
                            if (str[5] == 'a')
                                if (str[6] == 'l') 
                                    if (str[7] == '\0'){
                                    InsertPush(bottomOfStack, decimal_keyword);  
                                    return true; 
                                    }else return false;
        case 'e':
            if (str[1] == 'l')
                if (str[2] == 's')
                    if (str[3] == 'e') 
                        if (str[4] == '\0'){
                        InsertPush(bottomOfStack, else_keyword);  
                        return true; 
                        }else return false;
        case 'i':
            if (str[1] == 'f')
                if (str[2] == '\0'){
                InsertPush(bottomOfStack, if_keyword);  
                return true; 
                }else return false;
            if (str[1] == 'n')
                if (str[2] == 't') 
                    if (str[3] == '\0'){
                        InsertPush(bottomOfStack, int_keyword); 
                        return true;
                    }else return false;
        case 'l':
            if (str[1] == 'e')
                if (str[2] == 'n')
                    if (str[3] == 'g')
                        if (str[4] == 't')
                            if (str[5] == 'h') 
                                if (str[6] == '\0'){
                                InsertPush(bottomOfStack, length_keyword);  
                                return true; 
                                }else return false;
        case 'p':
            if (str[1] == 'r') {
                if (str[2] == 'o')
                    if (str[3] == 'c')
                        if (str[4] == 'e')
                            if (str[5] == 'e')
                                if (str[6] == 'd') 
                                    if (str[7] == '\0'){ 
                                    InsertPush(bottomOfStack, proceed_keyword); 
                                    return true; 
                                    }else return false;
                if (str[2] == 'i')
                    if (str[3] == 'n')
                        if (str[4] == 't') 
                            if (str[5] == '\0') {
                            InsertPush(bottomOfStack, print_keyword); 
                            return true; 
                           } else return false;
            }
        case 'r':
            if (str[1] == 'e') {
                if (str[2] == 'a')
                    if (str[3] == 'd')
                        if (str[4] == '\0'){ 
                        InsertPush(bottomOfStack, read_keyword); 
                        return true; 
                        }else return false;
                if (str[2] == 't')
                    if (str[3] == 'u')
                        if (str[4] == 'r')
                            if (str[5] == 'n') 
                                if (str[6] == '\0'){ 
                                InsertPush(bottomOfStack, return_keyword); 
                                return true; 
                                }else return false;
            }
        case 's':
            if (str[1] == 't')
                if (str[2] == 'r')
                    if (str[3] == 'i')
                        if (str[4] == 'n')
                            if (str[5] == 'g') 
                                if (str[6] == '\0'){ 
                                InsertPush(bottomOfStack, string_keyword); 
                                return true; 
                                }else return false;
        case 'w':
            if (str[1] == 'h')
                if (str[2] == 'i')
                    if (str[3] == 'l')
                        if (str[4] == 'e') 
                         if (str[5] == '\0'){ 
                         InsertPush(bottomOfStack, while_keyword); 
                         return true; 
                         }else return false;
        default: return false;
    }
}

//Supporting function for comparing
bool isEqual(const char *str1, const char *str2) {
    for (; *str1 && *str2 && *str1 == *str2; str1++, str2++);
    return (!(*str1) && !(*str2))? true : false;
}

//Return true if input is an integer
bool isInt(const char* str) {
	int size = strlen(str);
	if(size== 0)
		return (false);
	for (int i = 0; i < size; i++){
		if (str[i] != '0' && str[i] != '1' && str[i] != '2'
			&& str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8'
			&& str[i] != '9' || (str[i] == '-' && i > 0))
            return (false);
	}
	return (true);
}

//Return true if input has a decimal
bool isDecimal(char* str){
	int size = strlen(str);
	bool hasDecimal = false;
	if (size == 0)
		return (false);
	for (int i = 0; i < size; i++) {
		if (str[i] != '0' && str[i] != '1' && str[i] != '2'&& str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8'&& str[i] != '9' && str[i] != '.' ||(str[i] == '-' && i > 0)
			|| str[i] == '.' && hasDecimal)
			return (false);
		if (str[i] == '.')
			hasDecimal = true;
	}
	return (hasDecimal);
}

//Return true if the input is a boolean constant
bool isBoolConst(const char *str) {
    switch (str[0]) {
        case 't':
            if (str[1] == 'r')
                if (str[2] == 'u')
                    if (str[3] == 'e')
                        if (str[4] == '\0') return true; else return false;
        case 'f':
            if (str[1] == 'a')
                if (str[2] == 'l')
                    if (str[3] == 's')
                        if (str[4] == 'e') 
                            if (str[5] == '\0') return true; else return false;
    }
    return false;
}

//Return true if input is a reserved word
bool isReservedword(const char *str) {
    switch (str[0]) {
        case 'c':
            if (str[1] == 'o') {
                if (str[2] == 'm') {
                    if (str[3] == 'b') {
                        if (str[4] == 'i') {
                            if (str[5] == 'n') {
                                if (str[6] == 'e') {
                                    if (str[7] == '\0') { 
                                    InsertPush(bottomOfStack, combine_reserved); 
                                    return true; 
                                    }else return false;
                                }
                            }
                        }
                    }
                }
            }
        case 'e':
            if (str[1] == 'n') {
                if (str[2] == 'd') {
                    if (str[3] == '\0') { 
                                    InsertPush(bottomOfStack, end_reserved); 
                                    return true; 
                                    }else return false;
                }
            }
            if (str[1] == 'x') {
                if (str[2] == 'i') {
                    if (str[3] == 't') {
                        if (str[4] == '\0') { 
                                    InsertPush(bottomOfStack, exit_reserved); 
                                    return true; 
                                    }else return false;
                        }
                    }
            }
        case 'f':
            if (str[1] == 'r') {
                if (str[2] == 'e') {
                    if (str[3] == 'e') {
                        if (str[4] == '\0') { 
                                    InsertPush(bottomOfStack, free_reserved); 
                                    return true; 
                                    }else return false;
                    }
                }
            }
        case 's':
            if (str[1] == 't') {
                if (str[2] == 'a') {
                    if (str[3] == 'r') {
                        if (str[4] == 't') {
                            if (str[5] == '\0') { 
                                    InsertPush(bottomOfStack, start_reserved); 
                                    return true; 
                                    }else return false;
                        }
                    }
                }
            }
    }
    return false;
}

//Return true if input is a noise word
bool isNoiseword(const char *str) {
    switch (str[0]) {
        case 'O':
                if (str[1] == 'f') 
                    if (str[2] == '\0') {
                    InsertPush(bottomOfStack, Of_noise);  
                    return true; 
                   } else return false;
        case 'T':
            if (str[1] == 'o') 
                    if (str[2] == '\0'){
                    InsertPush(bottomOfStack,To_noise);  
                    return true; 
                    }else return false;
    }
    return false;
}

//Return true if input is an operator
bool isOperator(char before, char cur, char next) {
	if ((cur == '+' && (next == '+' || next == '=')) || (cur == '-' && (next == '-' || next == '='))
		|| (next == '=' && (cur == '=' || cur == '!' ||cur == '>' || cur == '<' || cur == '*' ||
		cur == '/' || cur == '%')) ||(cur == '&' && next == '&') || (cur == '|' && next == '|')
		|| (cur == '?' && next == '=') || (cur == '^' && next == '='))
	return (true);

	if ((cur == '+' || cur == '-' || cur == '*' ||cur == '/' || cur == '%' || cur == '^' ||
		cur == '>' || cur == '<' || cur == '!' ||cur == '=' || cur == '?') && ((before == ' ' && next == ' ')
		|| isDelimiter(next) == false))
		return (true);
	return (false);
}

//Name of single operator
const char * opNameA(char str){
    if(str == '+')
    {   InsertPush(bottomOfStack,Addition_opr); 
        return "Addition";}
    else if(str == '-')
    {    InsertPush(bottomOfStack,Subtraction_opr);
        return "Subtraction";}
    else if(str == '/')
    {    InsertPush(bottomOfStack,Division_opr);
        return "Division";
    }
    else if(str == '*')
    {    InsertPush(bottomOfStack,Multiplication_opr);
        return "Multiplication";
    }
    else if(str == '%')
    {    InsertPush(bottomOfStack,ModuloDivision_opr);
        return "ModuloDivision";
    }
    else if(str == '^')
    {    InsertPush(bottomOfStack,Exponent_opr);
        return "Exponent";
    }
    else if(str == '?')
    {    InsertPush(bottomOfStack,IntegerDivision_opr);
        return "IntegerDivision";
    }
    else if(str == '=')
    {   InsertPush(bottomOfStack,Equal_opr);
        return "Equal";
    }
    else if(str == '>')
    {    InsertPush(bottomOfStack,GreaterThan_opr);
        return "GreaterThan";
    }
    else if(str == '<')
    {    InsertPush(bottomOfStack,LessThan_opr);
        return "LessThan";
    }
    else if(str == '!')
    {    InsertPush(bottomOfStack,LogicalNot_opr);
        return "LogicalNot";
    }
    return "";
}

//Name of double operator
const char * opNameB(char str1, char str2){
    if(str1 == '+' && str2 == '+')
    {    InsertPush(bottomOfStack,Increment_opr);
        return "Increment";}
    else if(str1 == '-' && str2 == '-')
    {   InsertPush(bottomOfStack,Decrement_opr);
        return "Decrement";}
    else if(str1 == '+' && str2 == '=')
    {   InsertPush(bottomOfStack,AdditionAssignment_opr);
        return "AdditionAssignment";}
    else if(str1 == '-' && str2 == '=')
    {   InsertPush(bottomOfStack,SubtractionAssignment_opr);
        return "SubtractionAssignment";}
    else if(str1 == '*' && str2 == '=')
    {   InsertPush(bottomOfStack,MultiplicationAssignment_opr);
        return "MultiplicationAssignment";}
    else if(str1 == '/' && str2 == '=')
    {   InsertPush(bottomOfStack,DivisionAssignment_opr);
        return "DivisionAssignment";}
    else if(str1 == '%' && str2 == '=')
    {   InsertPush(bottomOfStack,ModuloDivision_opr);
        return "ModuloDivisionAssignment";}
    else if(str1 == '^' && str2 == '=')
    {   InsertPush(bottomOfStack,ExponentAssignment_opr);
        return "ExponentAssignment";}
    else if(str1 == '?' && str2 == '=')
    {   InsertPush(bottomOfStack,IntegerDivision_opr);
        return "IntegerDivisionAssignment";}
    else if(str1 == '=' && str2 == '=')
    {   InsertPush(bottomOfStack,isEqualTo_opr);
        return "isEqualTo";}
    else if(str1 == '>' && str2 == '=')
    {   InsertPush(bottomOfStack,GreaterThanEqualTo_opr);
        return "GreaterThanEqualTo";}
    else if(str1 == '<' && str2 == '=')
    {   InsertPush(bottomOfStack,LessThanEqualTo_opr);
        return "LessThanEqualTo";}
    else if(str1 == '!' && str2 == '=')
    {   InsertPush(bottomOfStack,NotEqualTo_opr);
        return "NotEqualTo";}
    else if(str1 == '&' && str2 == '&')
    {   InsertPush(bottomOfStack,LogicalAnd_opr);
        return "LogicalAnd";}
    else if(str1 == '|' && str2 == '|')
    {   InsertPush(bottomOfStack,LogicalOr_opr);
        return "LogicalOr";}
      return "";
}

//Contains Operator
bool isOP(char ch){
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ',' ||  ch == '>' ||
		ch == '<' || ch == '=' || ch == '!' || ch == '(' || ch == ')' ||
		ch == '^' || ch == '&' || ch == '%' || ch == '|' || ch == ' ' || ch == '?')
		return (true);
	return (false);
}

//Return true if input is a delimiter
bool isDelimiter(char ch) {
	if ((ch == ';' || ch == ',' || isOP(ch) == 1 || ch == '\n' || ch == ' ' || ch == '\t' || isBrackets(ch) == 1))
		return (true);
	return (false);
}

//Return true if the input is bracket
bool isBrackets(char ch){
	if(ch == '(' || ch == ')' || ch == '{' ||  ch == '}' )
		return (true);
	return (false);
}

//Name of delimiter
const char * delimiterName(char str1){
    if(str1 == '{')
    {    InsertPush(bottomOfStack,OpenCurlyBrace);
        return "OpenCurlyBrace";}
     else if(str1 == '}')
    {    InsertPush(bottomOfStack,CloseCurlyBrace);
        return "CloseCurlyBrace";}
     else if(str1 == '(')
    {    InsertPush(bottomOfStack,OpenParenthesis);
        return "OpenParenthesis";}
     else if(str1 == ')')
    {    InsertPush(bottomOfStack,CloseParenthesis);
        return "CloseParenthesis";}
     else if(str1 == ';')
    {    InsertPush(bottomOfStack,SemiColon_delim);
        return "SemiColon";}
     else if(str1 == ',')
    {    InsertPush(bottomOfStack,Comma_delim);
        return "Comma";}
      return "";
}

//Return true if input is has symbol
bool isSymbol(const char* ch){
	bool hasSymbol = false;
	 int size = strlen(ch);
	 for(int i = 0; i < size; i++){
		 	if(ch[i] == '(' || ch[i] == ')' || ch[i] == '[' || ch[i] == ']' || ch[i] == '{' || ch[i] == '}' ||
    		ch[i] == '<' || ch[i] == '>' || ch[i] == '+' || ch[i] == '=' || ch[i] == '-' ||
    		ch[i] == '|' || ch[i] == '/' || ch[i] == '\\' || ch[i] == ';' || ch[i] == ':' || ch[i] == '\'' ||
   			ch[i] == '\"' || ch[i] == ',' || ch[i] == '.' || ch[i] == '?' || ch[i] == '`' || ch[i] == '~' ||
    		ch[i] == '@' || ch[i] == '!' || ch[i] == '$' || ch[i] == '#' || ch[i] == '^' || ch[i] == '*' ||
    		ch[i] == '%' || ch[i] == '&')
		hasSymbol = true;
	 }
	 return hasSymbol;
}

//Take out the substring
char* subString(const char* str, int left, int right){
	char* subStr = (char*)malloc(sizeof(char) * (right - left+2));
	for (int i = left; i <= right; i++)
		subStr[i - left] = str[i];
	subStr[right - left + 1] = '\0';
	return (subStr);
}

//Reads the input file
void fileToString(char *str){
    FILE *fp;
	char file[10];
    char *ext;
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
        if(isEqual(ext, ".cb")){
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
        } 
        else{
            printf("Error! Incorrect file extension.\n\n");
            printf("Do you want to try again? (0-Yes / 1-No) : ");
                scanf("%d",&confirm);
                if(confirm == 1)
                    exit(0);
        }
    }
    char ch;
    int i = 0;
	int comments = 0, stringLiteral = 0;
do {
        ch = fgetc(fp);
		if(ch == '#' && (isDelimiter(str[i-1]) || i == 0))
			comments++;
		if(ch == '\n'){
			if(comments>0){
				comments=comments-1;
				str[i] = '\\';
				i++;
				str[i] = 'n';
				i++;
				str[i] = ' ';
				i++;
				continue;
			}else{
				str[i]= ' ';
				i++;
				continue;
			}
		}
		if(ch == '\"')
            stringLiteral++;
        if(ch == '\"' && (stringLiteral==1)){
            str[i] = ' ';
            i++;
        }if(ch == '\"' && (stringLiteral==2)){
            stringLiteral=0;
        }
        str[i] = ch;
        i++;
    } while (ch != EOF);
str[i-1] = '\0';
fclose(fp);
}

//Create a .txt file for the symbol table
void outputFile(char *str) {
	FILE *fp;
    fp = fopen("Output.txt","w");

	int left = 0, right = 0;
	int size = strlen(str);

	while (right <= size && left <= right) {
		if (!isDelimiter(str[right]))
			right++;
		if(str[left]=='\"'){
			do{ right++;
				if(str[right]== '\0')
					break;
			}while(str[right]!= '\"');
			right++;
			char* subStr = subString(str, left, right - 1);
            InsertPush(bottomOfStack,str_const);
			fprintf(fp,"%c\t\tstr_const = '%s'\n",poptoken(bottomOfStack), subStr);
			left = right;
		}
		else if(str[left]=='\''){
			do{ right++;
				if(str[right]== '\0')
					break;
			}while(str[right]!= '\'');
			right++;
			char* subStr = subString(str, left, right - 1);
			if(strlen(subStr) == 3){
                InsertPush(bottomOfStack,char_const);
                fprintf(fp,"%c\t\tchar_const - '%s'\n",poptoken(bottomOfStack), subStr);
            }else{
                InsertPush(bottomOfStack,unrecognized);
                fprintf(fp, "%c\t\tunrecognized - '%s'\n",poptoken(bottomOfStack), subStr);}
			left = right;
		}
		else if(str[left]=='#'){
			do{
				if(str[right]== '\0')
					break;
				if(str[right]== '\\' && str[right+1]== 'n')
					break;
				 right++;
			}while(1);
			char* subStr = subString(str, left, right - 1);
			right=right+2;
			left = right;
		}	
		else if (isDelimiter(str[right]) && left == right) {
			if(isOperator(str[right-1], str[right], str[right+1])
				&& (isalpha(str[right+1])!=0 || isdigit(str[right+1])!=0 || str[right+1] == ' ')
				&& (isalpha(str[right-1])!=0 || isdigit(str[right-1])!=0 || str[right-1] == ' '))
				fprintf(fp,"%c\t\t%s_opr - '%c'\n",poptoken(bottomOfStack), opNameA(str[right]), str[right]);
			else if (isOperator(str[right-1], str[right], str[right+1]) && (isalpha(str[right+1])==0 && isdigit(str[right+1])==0)){
				fprintf(fp,"%c\t\t%s_opr - '%c%c'\n",poptoken(bottomOfStack), opNameB(str[right], str[right+1]), str[right], str[right+1]);
				right++;
			}
			else if (isBrackets(str[right]) && (str[right]) != ' ')
				fprintf(fp,"%c\t\t%s - '%c' \n",poptoken(bottomOfStack), delimiterName(str[right]), str[right]);
			else if (isDelimiter(str[right]) && (str[right]) != ' ' && !isBrackets(str[right])){
                if(str[right] != '\t')
				    fprintf(fp,"%c\t\t%s_delim - '%c'\n",poptoken(bottomOfStack), delimiterName(str[right]), str[right]);
            }
			right++;
			left = right;
		}
		else if (isDelimiter(str[right]) && left != right || (right == size && left != right)) {
			char* subStr = subString(str, left, right - 1);
			// int len = strlen(subStr);
        	// subStr[len - 1] = '\0';
			if (isKeyword(subStr))
				fprintf(fp,"%c\t\t%s_keyword - '%s'\n",poptoken(bottomOfStack), subStr,subStr);
			else if(isNoiseword(subStr))
				fprintf(fp,"%c\t\t%s_noise - '%s'\n",poptoken(bottomOfStack), subStr,subStr);
			else if(isReservedword(subStr))
				fprintf(fp,"%c\t\t%s_reserved = '%s'\n",poptoken(bottomOfStack), subStr,subStr);
			else if (isInt(subStr)){
                InsertPush(bottomOfStack,int_const); 
				fprintf(fp,"%c\t\tint_const - '%s'\n",poptoken(bottomOfStack), subStr);
            }
			else if (isDecimal(subStr)){
                InsertPush(bottomOfStack,dec_const);
				fprintf(fp,"%c\t\tdec_const - '%s'\n",poptoken(bottomOfStack), subStr);
			}else if(isBoolConst(subStr)){
                InsertPush(bottomOfStack,bool_const);
				fprintf(fp,"%c\t\tbool_const - '%s'\n",poptoken(bottomOfStack), subStr);
			}else if (isIdentifier(subStr) && !isDelimiter(str[right - 1]) && strlen(subStr)<64){
                InsertPush(bottomOfStack,identifier); 
                fprintf(fp,"%c\t\tidentifier - '%s'\n",poptoken(bottomOfStack), subStr,subStr);
                }
            else if (isIdentifier(subStr) && !isDelimiter(str[right - 1]) && strlen(subStr)>=64){
                InsertPush(bottomOfStack,unrecognized);
                fprintf(fp,"%c\t\tunrecognized - '%s'\n",poptoken(bottomOfStack), subStr);
			}else if (!isIdentifier(subStr) && !isDelimiter(str[right - 1])){
                InsertPush(bottomOfStack,unrecognized);
				fprintf(fp,"%c\t\tunrecognized - '%s'\n",poptoken(bottomOfStack), subStr);
			}if (isBrackets(str[right]) && (str[right]) != ' ')
				fprintf(fp,"%c\t\t%s - '%c'\n",poptoken(bottomOfStack), delimiterName(str[right]), str[right]);
            else if (isOperator(str[right-1], str[right], str[right+1]) && (isalpha(str[right+1])==0 && isdigit(str[right+1])==0)){
				fprintf(fp,"%c\t\t%s_opr - '%c%c'\n",poptoken(bottomOfStack), opNameB(str[right], str[right+1]), str[right], str[right+1]);
				right++;
			}else if (isDelimiter(str[right]) && (str[right]) != ' ' && (str[right-1]) != ' ')
				fprintf(fp,"%c\t\t%s_delim = '%c'\n",poptoken(bottomOfStack), delimiterName(str[right]), str[right]);
			else if(isOP(str[right]) && str[right] != ' ')
				fprintf(fp,"%c\t\t%s_opr - '%c'\n",poptoken(bottomOfStack), opNameA(str[right]), str[right]);
			right++;
			left = right;
		}
	}
	fclose(fp);
}