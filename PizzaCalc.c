#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Defining constants
#define MAX 64
#define PI 3.14159265358979323846


/*
 Type definition for Pizza
 Has 3 fields: name, pizzaPerCost, and next
 Call with Pizza
 */
typedef struct Pizza {
    char* name;
    float pizzaPerDollar;
    Pizza* next;
} Pizza;

Pizza* create(FILE* theFile){
    
    char str[MAX] = "empty";
    char done[] = "DONE\n"; // Done has a newline after it... wtf?
    Pizza* aPizza = (struct Pizza*)malloc(sizeof(Pizza));

    for (int i = 0; i < 3; i++){
        
        fgets(str, MAX, theFile);
        if (strcmp(str, "empty") == 0){
            printf("PIZZA FILE IS EMPTY");
            
            // If no pizza, panic and yeet out everything
            free(aPizza);
            
            return NULL;
        }
        
        if (strcmp(str, done) == 0){
            free(aPizza);
            return NULL;
        }
        
        
        char* copiedString = (char*)malloc(sizeof(char)*MAX);
        strcpy(copiedString, str);
        strtok(copiedString, "\n"); // Remove any newline character at the end
        
        if (i == 0){
            aPizza->name = copiedString;
        }
        
        if (i == 1){
            aPizza->pizzaPerDollar = atof(copiedString);
            free(copiedString);
        }
        
        if (i == 2){
            // If cost is 0, no pizza, there is no free lunch!
            if (!atof(copiedString)){
                aPizza->pizzaPerDollar = 0;
                free(copiedString);
            } else {
                float cost = atof(copiedString);
                float PPD = pow(aPizza->pizzaPerDollar/2, 2)*PI/cost;
                free(copiedString);
                aPizza->pizzaPerDollar = PPD;
            }
        }
    }
    
    aPizza->next = NULL;
    return aPizza;
}

void insert(Pizza* current, Pizza** head){
    
    
    Pizza* prev = NULL;
    Pizza* iter = *head;
    
    while (iter != NULL && iter->pizzaPerDollar > current->pizzaPerDollar){
        prev = iter;
        iter = iter->next;
    }
    
    
    if (prev == NULL){
        
        current->next = iter;
        *head = current;

    } else {
        
        while (iter != NULL && iter->pizzaPerDollar == current->pizzaPerDollar){
            if (strcmp(current->name, iter->name) < 0){
                prev->next = current;
                current->next = iter;
                return;
            }
            prev = iter;
            iter = iter->next;
        }
        
        prev->next = current;
        current->next = iter;
    }
        
    return;
}

int main(int argc, char* argv[]){
    
    // Open the file and make a pointer
    FILE* theFile = fopen(argv[1], "r");
    
    Pizza** head = (Pizza**)malloc(sizeof(Pizza*));
    *head = NULL;
    

    while (1){
        Pizza* current = create(theFile);
        if (current == NULL){
            
            fclose(theFile);
            break;
        }
        insert(current, head);
        //printf("%s\n", head->name);
    }
    
    Pizza* iter = *head;
    Pizza* temp;
    
    while (iter != NULL){
        printf("%s %f\n", iter->name, iter->pizzaPerDollar);
        free(iter->name);
        temp = iter;
        iter = iter->next;
        free(temp);
    }
    
    // Release everything else
    
    free(head);
    return EXIT_SUCCESS;

}

