#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>




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


int getFileSize(const char* fileName) { // This function returns the number of newline chars in the given file (indicating its length).
    int newlineCounter = 0;
    FILE* file = fopen(fileName, "r");
    if (file != NULL) {
        char character;
        while ((character = fgetc(file)) != EOF) {
            if (character == '\n') {
                newlineCounter++;
            }
        }
    }
    fclose(file);
    return newlineCounter;
} // end of "getFileSize" function


char* getLargestFileName() {
    DIR *dir;
    struct dirent *entry;
    dir = opendir(".");
    char* largestFileName = malloc(sizeof(char) * 255); // 255 is the max file name length on mac.
    int largestFileSize = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strncmp(entry->d_name, "movies_", strlen("movies_")) == 0
        && strcmp(entry->d_name + strlen(entry->d_name) - strlen(".csv"), ".csv") == 0) { // checking files that have the required prefix "movies_" and have the extension ".csv"
            int currentFileSize = getFileSize(entry->d_name); // getting the current file size
            if (currentFileSize > largestFileSize) { // if the current file size is greater than the largest file so far, update the largest file to the current file
                largestFileSize = currentFileSize;
                strcpy(largestFileName, entry->d_name); // copy the current file name to the largest file name string
            }
        }
    } // end of while loop
    return largestFileName;
} // end of "getLargestFileName" function


void createDirectory(char* directoryName) {




} // end of "createDirectory" function


char* generateDirectoryName() { // this function generates and returns a directory name.
    char* directoryName = malloc(sizeof(char) * strlen("edwabray.movies.") + 8); // creating the mem. space for the directory name
    char* directoryNumber = malloc(sizeof(char) * 7); // creating the space to store the random number as a string.
    int randomNumber = random() % 100000; // generating a random number between 0 and 99999
    strcpy(directoryName, "edwabray.movies."); // copying the initial name of the directory into the variable
    sprintf(directoryNumber, "%d", randomNumber); // converting random int into string
    strcat(directoryName, directoryNumber); // adding random int string into directory name
    free(directoryNumber);
    return directoryName;
} // end of "generateDirectoryName" function


void processLargestFile() {
    char* largestFileName = getLargestFileName();
    printf("\nNow processing the chosen file named %s \n", largestFileName); // outputing to the user

    char* directoryName = generateDirectoryName(); // using a function to generate the directory name and assigning that to a variable
    createDirectory(directoryName); // creating the directory

    free(directoryName);
    free(largestFileName);
} // end of "processLargestFile" function


void processSmallestFile() {

} // end of "processSmallestFile" function


char* getSpecificFileName() { // This function reads the fileName from the user
    char* fileName = malloc(sizeof(char) * 1000); // memory freed in "processingSpecificFile" function
    printf("Enter the complete file name: "); // prompting the user
    scanf("%999s", fileName);
    return fileName;
} // end of "getSpecificFileName" function



void processSpecificFile () {
    char* fileName = getSpecificFileName(); // calling this function to get the name
    printf("Now processing the chosen file named %s \n", fileName);


    free(fileName); // freeing the allocated memory
} // end of "processSpecificFile" function


int main(int argc, char **argv) {
    srandom(time(NULL));

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