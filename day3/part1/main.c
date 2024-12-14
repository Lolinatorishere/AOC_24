#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define filedir "input.txt"

#define isasciinum(STRING)\
    if(STRING >= 48 && STRING <= 57)

int clear_buffer(char *buffer, int buffer_size){
    for(int i = 0 ; i < buffer_size ; i++){
        buffer[i] = '\0';
    }
    return 0;
}

int stringCmp(char *string1, char *string2){
    int i = 0, j = 0;
    while(string1[i] != '\0'){
        i++;
    }
    while(string2[j] != '\0'){
        j++;
    }
    if(i != j){
        return 0;
    }
    for(i = 0 ; i < j ; i++){
        if(string1[i] != string2[i]){
            return 0;
        }
    }
    return 1;
}

int parse_numbers(char *input, int64_t *num1, int64_t *num2){
    //fputs(input, stdout);
    //printf("\n");
    *num1 = 0;
    *num2 = 0;
    int mult_flag = 0, comma_flag = 0;
    char *buffer = malloc(sizeof(char)*4);
    for (int i = 0 ; i <= 8 ; i++){
        if(input[i] == ')' && i <= 2){
            //printf("no");
            free(buffer);
            return 0;
        }
        isasciinum(input[i]){
            buffer[mult_flag] = input[i];
            mult_flag++;
            if(mult_flag == 4){
                free(buffer);
                //printf("no");
                return 0;
            }
            continue;
        }
        if(input[i] == ',' && comma_flag == 0){
            mult_flag = 0;
            comma_flag = 1;
            *num1 = atol(buffer);
            clear_buffer(buffer, 4);
        }
        if(input[i] == ')') {
            *num2 = atol(buffer);
            free(buffer);
            //printf("yes\n");
            return 1;
        }
    }
    //printf("no");
    free(buffer);
    return 0;
}

int64_t parse_text(char *input, int64_t filesize){
    char buffer[5], num_buffer[8];
    char *begin_search = malloc(sizeof(char)*5);
    int offset = 4, mult_offset = 8, temp_offset = 0;
    int64_t internal = 0;
    int64_t j = 0;
    int64_t total = 0, num1 = 0, num2 = 0;
    int num_flag = 0;
    int yes = 0, no = 0;
    strcpy(begin_search, "mul(");
    for(int i = 0 ; i < filesize ; i++){
        //printf("%i\n", i);
        if(i+offset >= filesize){
            i = filesize;
            continue;
        }
        while(j < offset){
            if(i+j+offset >= filesize){
                j = offset;
                continue;
            }
            buffer[j] = input[j+i];
            j++;
        }
        buffer[5] = '\0';
        j = 0;
        if(stringCmp(buffer, begin_search) == 1){
            i = i+offset;
            for(int j = 0 ; j < mult_offset; j++){
                if(i+mult_offset >= filesize){
                    j = mult_offset;
                    continue;
                }
                num_buffer[j] = input[j+i];
            }
            if(parse_numbers(num_buffer, &num1, &num2) != 0){
                yes++;
                if(num1 >= 1000){
                    printf("num1: %li\n", num1);
                }
                if(num2 >= 1000){
                    printf("num2: %li\n", num2);
                }
                total += (num1 * num2);
                printf("(%li * %li) +\n",num1, num2);
            }else{
                no++;
                num1 = 0;
                num2 = 0;
            }
            //printf("total: %li\n",total);
            clear_buffer(num_buffer, 8);
        }
    }
    printf("yes: %i\n",yes);
    printf("no: %i\n",no);
    free (begin_search);
    return total;
}

int main(){
    FILE *file;
    int filecheck = 1;
    int64_t filesize = 0;
    char fchar;
    int64_t total = 0;

    file = fopen(filedir, "r");

    if(file == NULL){
        printf("File Doesnt Exist");
        return 1;
    }
    // get the ammount of numbers to allocate for memory
    // arrMax
    while(filecheck != 0){
        fseek(file,filesize,SEEK_SET);
        fchar = fgetc(file);
        if(fchar == EOF){
            filecheck = 0;
        }
        filesize++;
    }
    char *buffer = malloc(sizeof(char)*filesize);
    filecheck = 1;
    for(int i = 0 ; i < filesize ; i++){
        fseek(file,i,SEEK_SET);
        fchar = fgetc(file);
        buffer[i] = fchar;
    }
    fclose(file);
    printf("answer: %li",parse_text(buffer, filesize));
    free (buffer);
    return 0;
}

