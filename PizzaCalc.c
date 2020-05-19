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


/*
 Swaps the contents of 2 Pizza nodes (not the nodes themselves)
 Might have a better way.
 */
void swap(Pizza* i, Pizza* j){
    char* tempName = i->name;
    float tempPPD = i->pizzaPerDollar;
    
    i->name = j->name;
    i->pizzaPerDollar = j->pizzaPerDollar;
    
    j->name = tempName;
    j->pizzaPerDollar = tempPPD;
}


/*
 Sorts the Pizza linked list first alphabetically, then by
 their pizza per inch values.
 Calls swap() to swap elements.
 Also prints the output, as specified by the
 assignment writeup.
 BUBBLESORT IS SLOW.
 */
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
    
    // Open the file and make a pointer
    FILE* theFile = fopen(argv[1], "r");
    
    char done[] = "DONE\n"; // Done has a newline after it... wtf?
    
    // Allocate the first Pizza node as iterator
    Pizza* pizzaList = (Pizza*) malloc(sizeof(Pizza));
    
    // Keep track of the start node
    Pizza* start = pizzaList;

    // counter cycles 0, 1, 2 to parse tokens
    int counter = 0;
    
    // index keeps track of number of Pizzas and array index
    int index = 0;
    
    while (1){
        // Initialize buffer string for fgets()
        char str[MAX] = "empty";
        
        // Read one line
        fgets(str, MAX, theFile);
        
        // Check for empty file, where buffer is unchanged
        if (strcmp(str, "empty") == 0){
            printf("PIZZA FILE IS EMPTY");
            
            // If no pizza, panic and yeet out everything
            fclose(theFile);
            free(pizzaList);
            return EXIT_SUCCESS;
        }
        
        // When "DONE" is encountered, stop building the list
        if (strcmp(str, done) == 0){
            pizzaList->next = NULL;
            break;
        }
        
        // Make a copy of the current buffer to store in array
        char* copiedString = (char*)malloc(sizeof(char)*MAX);
        strcpy(copiedString, str);
        strtok(copiedString, "\n"); // Remove any newline character at the end
                
        // 1st token is pizza name, set the name field of Pizza
        if (counter == 0){
            pizzaList->name = copiedString;
        }
        
        // 2nd token is diameter, temporarily putting it in pizzaPerDollar
        if (counter == 1){
            pizzaList->pizzaPerDollar = atof(copiedString);
            
            // release memory allocated to copiedString
            free(copiedString);
        }
        
        /* 3rd token is cost, take what was already in pizzaPerDollar
         and do the math.
         */
        if (counter == 2){
            // If cost is 0, no pizza, there is no free lunch!
            if (!atof(copiedString)){
                pizzaList->pizzaPerDollar = 0;
                
                // release memory allocated to copiedString
                free(copiedString);
            } else {
                float cost = atof(copiedString);
                float PPD = pow(pizzaList->pizzaPerDollar/2, 2)*PI/cost;
                pizzaList->pizzaPerDollar = PPD;

                // release memory allocated to copiedString
                free(copiedString);

            }

            // Allocate a new Pizza node and advance the iterator
            pizzaList->next = (Pizza*) malloc(sizeof(Pizza));
            pizzaList = pizzaList->next;
            
            // Also reset the token counter
            counter = 0;

        } else {
            
            // Advance token counter by 1 unless counter = 2
            counter += 1;
        }
        
        // Advance the index
        index += 1;

    }
    
    // Sort the list and print the results
    listSort(start);
    
    // Release memory allocated to Pizza list and the strings stored inside
    while (start->next != NULL){
        Pizza* prev = start;
        free(start->name);
        start = start->next;
        free(prev);
    }
    
    
    // Release everything else
    fclose(theFile);
    free(pizzaList);

    return EXIT_SUCCESS;

}

