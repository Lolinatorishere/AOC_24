#include <stdio.h>
#include <stdlib.h>

#define filedir "input.txt"

#define isasciinum(STRING)\
    if(STRING >= 48 && STRING <= 57)

int clear_buffer(char *buffer){
    for(int i = 0 ; i < 128 ; i++){
        buffer[i] = '\0';
    }
    return 0;
}

int is_safe(int64_t *input);

void buffer_set(int64_t *input, int64_t *output, int index_skip, int maxindex){
    int i = 0,j = 0;
    for(i = 0 ; i <= maxindex ; i++){
        if(i == index_skip){
            i++;
        }
        output[j] = input[i];
        j++;
    }
}

int make_safe(int64_t *input, int line){
    int arraysize = 0;
    int issue_val = 0;
    int value = 0;
    while(input[arraysize] != -1){
        arraysize++;
    }
    if(is_safe(input) == 1){
        return 1;
    }
    int64_t *buffer = malloc(sizeof(int64_t)*arraysize);
    for(int i = 0 ; i < arraysize ; i++){
        buffer_set(input, buffer, i, arraysize);
        if(is_safe(buffer) == 1){
            printf("%i\n",line);
            value = 1;
            i = arraysize;
            continue;
        }
    }
    free(buffer);
    return value;
}

int is_safe(int64_t *input){
    int64_t temp = 0;
    int i = 0;
    int directionFlag = 0;
    while(input[i+1] != -1){
        temp = input[i+1] - input[i];
        if(temp > 0 && temp <= 3){
            if(directionFlag != 0 && directionFlag != 1){
                return 0;
            }
            i++;
            temp = 0;
            directionFlag = 1;
            continue;
        }
        if(temp < 0 && temp >= -3){
            if(directionFlag != 0 && directionFlag != -1){
                return 0;
            }
            directionFlag = -1;
            i++;
            temp = 0;
            continue;
        }
        return 0;
    }
    return 1;
}
void parce_numbers(char *input, int j, int64_t **array, int arrPos){
    char buffer[128];
    int numbers = 0;
    int k = 0, l = 0;
    for (int i = 0 ; i < j ; i++){
        isasciinum(input[i]){
            buffer[k] = input[i];
            k++;
        }else{
            numbers++;
        }
    }
    k = 0;
    clear_buffer(buffer);
    array[arrPos] = malloc(sizeof(int64_t)*numbers+1);
    for(int i = 0 ; i < j ; i++){
        isasciinum(input[i]){
            buffer[k] = input[i];
            k++;
            //fputs(buffer, stdout);
        }else{
            array[arrPos][l] = atoi(buffer);
            clear_buffer(buffer);
            l++;
            k = 0;
        }
    }
    array[arrPos][l] = -1;
    //printf("numbers: %i\n", numbers);
}

int main(){
    FILE *file;
    int filecheck = 1;
    int arrMax = 0;
    int64_t filesize = 0;
    char fchar;

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
        if(fchar == '\n'){
            arrMax++;
        }
        filesize++;
    }
    int64_t **array1 = malloc(sizeof(int64_t*)*arrMax);

    filecheck = 1;
    int i = 0, j = 0, arrPos = 0;
    char buffer[128];
    int num1 = 0;
    int num2 = 0;

    for(i = 0 ; i < filesize ; i++) {
        fseek(file,i,SEEK_SET);
        fchar = fgetc(file);
        buffer[j] = fchar;
        j++;
        if(fchar == '\n'){
            parce_numbers(buffer, j, array1, arrPos);
            j = 0;
            arrPos++;
        }
    }
    fclose(file);
    int safe = 0;
    for(int i = 0 ; i < arrMax ; i++){
        safe += make_safe(array1[i], i);
    }
    free (array1);
    printf("safe: %i",safe);
    return 0;
}

