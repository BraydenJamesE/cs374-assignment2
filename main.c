#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int get_initial_choice() { // this function gets the initial choice from the user. Rather to Select a file to process or to exit the program.
    while (true) { // Continually asking for the right input until the correct one is given.
        char choice[2];
        printf("1. Select file to process \n");
        printf("2. Exit the program\n");
        printf("Enter a choice 1 or 2: ");
        scanf("%s", choice);
        printf("You entered: %s \n", choice);

        if (choice[0] == '1'){
            return 1;
        }
        else if (choice[0] == '2') {
            return 2;
        }
        else {
            printf("Invalid Input. Please enter 1 or 2. \n\n");
            continue;
        }
    } // end of while loop
} // end of "get_initial_choice" function


int main(int argc, char **argv) {

    printf("%d", get_initial_choice());

    return 0;
}