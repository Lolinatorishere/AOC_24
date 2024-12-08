#include <stdio.h>
#include <stdlib.h>

#define isasciinum(STRING)\
    if(STRING >= 48 && STRING <= 57)

int clear_buffer(char *buffer){
    for(int i = 0 ; i < 128 ; i++){
        buffer[i] = '\0';
    }
    return 0;
}

int compare_ints(const void *a, const void *b) {
    int64_t int_a = *(int64_t *)a;
    int64_t int_b = *(int64_t *)b;

    if (int_a < int_b) return -1;
    else if (int_a > int_b) return 1;
    else return 0;
}

void parce_numbers(char *input, int j, int *num1, int *num2){
    char buffer[128];
    int k = 0;
    int which = 0;
    for (int i = 0 ; i < j ; i++){
        isasciinum(input[i]){
            buffer[k] = input[i];
            k++;
        }else{
            if(which == 0 && buffer[0] != '\n'){
                *num1 = atoi(buffer);
            }else{
                *num2 = atoi(buffer);
            }
            which++;
            clear_buffer(buffer);
            k=0;
        }
    }
}

int array_similarity(int64_t number, int64_t *array2, int arrMax){
    int similarity_multiplier = 0;
    for(int i = 0 ; i < arrMax ; i++){
        if (array2[i] == number){
            similarity_score++;
        }
    }
    return similarity_multiplier;
}

int main(){
    char filedir[] = "input.txt";
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

    int64_t *array1 = malloc(sizeof(int64_t)*arrMax);
    int64_t *array2 = malloc(sizeof(int64_t)*arrMax);
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
            parce_numbers(buffer, j, &num1, &num2);
            j = 0;
            array1[arrPos] = num1;
            array2[arrPos] = num2;
            arrPos++;
        }
        if(i+1 == filesize){
            parce_numbers(buffer, j, &num1, &num2);
            j = 0;
            array1[arrPos] = num1;
            array2[arrPos] = num2;
            arrPos++;
        }
    }
    fclose(file);

    qsort(array1, arrMax, sizeof(int64_t), compare_ints);
    qsort(array2, arrMax, sizeof(int64_t), compare_ints);
    int64_t total = 0, temp = 0, mult = 0;
    
    for(i = 0 ; i < arrMax; i++){
        if(temp != array1[i]){
            mult = array_similarity(array1[i]);
        }
        temp = array1[i];
    }
    printf("%li\n",total);

    free (array1);
    free (array2);
    return 0;
}
