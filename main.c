#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int getInitialChoice() { // this function gets the initial choice from the user. Rather to Select a file to process or to exit the program.
    while (true) { // Continually asking for the right input until the correct one is given.
        char choice[2];
        printf("1. Select file to process \n");
        printf("2. Exit the program\n");
        printf("Enter a choice 1 or 2: ");
        scanf("%1s", choice);
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


int getFileProcessChoice() { // getFileProcessChoice
    while (true) {
        char choice[2];
        printf("\nWhich file do you want to process?\n");
        printf("Enter 1 to pick the largest file\n");
        printf("Enter 2 to pick the smallest file\n");
        printf("Enter 3 to specify the name of a file\n");
        printf("Enter a choice from 1 to 3: ");
        scanf("%1s", choice);

        switch (choice[0]) {
            case '1':
                return 1;
            case '2':
                return 2;
            case '3':
                return 3;
            default:
                printf("Invalid input. Please enter 1, 2, or 3. \n");
                break;
        }
    } // end of while loop
} // end of "getFileProcessChoice" function


void processLargestFile() {

} // end of "processLargestFile" function


void processSmallestFile() {

} // end of "processSmallestFile" function


char* getSpecificFileName() { // This function reads the fileName from the user
    char* fileName = malloc(sizeof(char) * 1000); // memory freed in "processingSpecificFile" function
    printf("Enter the complete file name: "); // prompting the user
    scanf("%999s", fileName);
    return fileName;
} // end of "getSpecificFileName" function


void createDirectory() {
    printf("Created directory with name ");
} // end of "createDirectory" function


void processSpecificFile () {
    char* fileName = getSpecificFileName(); // calling this function to get the name
    printf("Now processing the chosen file named %s \n", fileName);

    createDirectory();

    free(fileName); // freeing the allocated memory
} // end of "processSpecificFile" function


int main(int argc, char **argv) {

    if (getInitialChoice() == 2) { // ending program
        printf("Ending program...");
        return 0;
    }
    else { // giving user additional options
        switch (getFileProcessChoice()) {
            case 1:
                processLargestFile();
            case 2:
                processSmallestFile();
            case 3:
                processSpecificFile();
            default:
                printf("There was an error in processing your choice. Goodbye.");
        }
    }

    return 0;
}