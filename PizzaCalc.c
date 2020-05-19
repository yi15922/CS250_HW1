#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 64
#define PI 3.14159265358979323846


typedef struct Pizza {
    char* name;
    float pizzaPerDollar;
    Pizza* next;
} Pizza;

void swap(Pizza* i, Pizza* j){
    char* tempName = i->name;
    float tempPPD = i->pizzaPerDollar;
    
    i->name = j->name;
    i->pizzaPerDollar = j->pizzaPerDollar;
    
    j->name = tempName;
    j->pizzaPerDollar = tempPPD;
}


void listSort(Pizza* list){
    Pizza* i;
    Pizza* j;
    
    for (i = list; i->next != NULL; i = i->next){
        for (j = i->next; j->next != NULL; j = j->next){
            if (i->pizzaPerDollar == j->pizzaPerDollar && strcmp(j->name, i->name) < 0){
                swap(i, j);
            } else
            if (i->pizzaPerDollar < j->pizzaPerDollar){
                swap(i, j);
            }
        }
        printf("%s %f\n", i->name, i->pizzaPerDollar);
    }
}



int main(int argc, char* argv[]){
    FILE* theFile = fopen(argv[1], "r");
    
    char string[MAX];
    char done[] = "DONE\n";
    
    
    Pizza* pizzaList = (Pizza*) malloc(sizeof(Pizza));
    Pizza* start = pizzaList;
    
    char** stringArray = (char**)malloc(sizeof(char*));
    
    int counter = 0;
    int index = 0;
    
    while (1){
        char str[MAX];
        fgets(str, MAX, theFile);
        if (strcmp(str, done) == 0){
            pizzaList->next = NULL;
            break;
        }
        
        char* copiedString = (char*)malloc(sizeof(char)*MAX);
        strcpy(copiedString, str);
        strtok(copiedString, "\n");
        
        stringArray[index] = copiedString;
        
            
        if (counter == 0){
            pizzaList->name = stringArray[index];
            //printf("\t%s", pizzaList->name);
        }
        
        if (counter == 1){
            pizzaList->pizzaPerDollar = atof(stringArray[index]);
            //printf("\t%f\n", pizzaList->pizzaPerDollar);
        }
        
        if (counter == 2){
            //float cost = atof(string);
            if (!atof(stringArray[index])){
                pizzaList->pizzaPerDollar = 0;
            } else {
                pizzaList->pizzaPerDollar = pow(pizzaList->pizzaPerDollar/2, 2)*PI/atof(stringArray[index]);
            }
            //printf("\t%f\n", cost);
            //printf("\t%f\n", PPD);
            //printf("\t%f\n", pizzaList->pizzaPerDollar);
            
            pizzaList->next = (Pizza*) malloc(sizeof(Pizza));
            pizzaList = pizzaList->next;
            
            counter = 0;

        } else {
            counter += 1;
        }
        
        index += 1;
        stringArray = (char**)realloc(stringArray, (index+1)*sizeof(char*));
        
    }
    
    listSort(start);
    
    while (start->next != NULL){
        //printf("%s:\t%f\n", start->name, start->pizzaPerDollar);
        Pizza* prev = start;
        start = start->next;
        free(prev);
    }
    
                   /*
    for (int i = 0; i < index; i++){
        printf("%s\n", stringArray[i]);
    }
                    */
    
    
    for (int i = 0; i < index; i++){
        free(stringArray[i]);
    }
    fclose(theFile);
    free(stringArray);
    free(pizzaList);

    return EXIT_SUCCESS;

}

