#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>


#define DELIMITER ","

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
    mode_t permissions = 0705; // Permissions gathered from this source: https://jameshfisher.com/2017/02/24/what-is-mode_t/


    mkdir(directoryName, permissions); // creating directory


    printf("Created directory with name %s \n", directoryName);
} // end of "createDirectory" function


char* createFile(char* directoryName, char* year) {
    mode_t permissions = 0640; // creating the file permissions. Source: https://jameshfisher.com/2017/02/24/what-is-mode_t/
    char* template = "YYYY.txt";
    char* fileName = malloc(sizeof(char) * (strlen(template) + 1));
    size_t filePathSize = sizeof(char) * (strlen(directoryName) + strlen(template) + 2);
    char* filePath = malloc(filePathSize);

    snprintf(fileName, sizeof(char) * (strlen(template) + 1), "%s.txt", year); // creating a string for the fileName

    snprintf(filePath, filePathSize, "%s/%s", directoryName, fileName); // creating the file in the directory.


    FILE* file = fopen(filePath, "w"); // creating the file
    chmod(filePath, permissions); // setting the permissions of the file
    fclose(file); // closing the file


    free(fileName); // freeing the fileName memory
    return filePath;
} // end of "createFile" function


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


void processFiles(char* fileToProcess, char* directoryName) {
    // read fileToProcess
    int numberOfYears = 2024 - 1900;
    char** listOfMovieTitlesPerYear = malloc(numberOfYears * sizeof(char));
    FILE* fileHandler = fopen(fileToProcess, "r");
    const int LINE_SIZE = 1001;
    char fileContent[LINE_SIZE];
    int index = 0;

    for(int i = 0; i < numberOfYears; i++) {
        listOfMovieTitlesPerYear[i] = NULL;
        printf("%d: %s \n", i, listOfMovieTitlesPerYear[i]);
    }

    while (true) {
        if (fgets(fileContent, LINE_SIZE, fileHandler) != NULL) { // get the file content
            if (index == 0) { // ensuring that the header is not read
                index += 1;
                continue; // if this is the header, continue in the loop
            }

            char* movieTitle = malloc(sizeof(char) * 100);

            char* token;
            char* savePtr = NULL;

            token = strtok_r(fileContent, DELIMITER, &savePtr);
            strcpy(movieTitle, token);
            printf("Movie Title: %s \n", movieTitle);
            token = strtok_r(NULL, DELIMITER, &savePtr); // reading the year
            printf("year: %s \n", token);
            char* filePath = createFile(directoryName, token);

            int yearIndex = atoi(token) - 1900; // getting the index for the "listOfMoviesTitlePerYear" array.

            if (listOfMovieTitlesPerYear[yearIndex] != NULL) { // if the current movie is not the first movie at this index, append it to the list with a comma.
                size_t stringSize = sizeof(char) * (strlen(listOfMovieTitlesPerYear[yearIndex]) + strlen(movieTitle) + 2);
                listOfMovieTitlesPerYear[yearIndex] = realloc(listOfMovieTitlesPerYear[yearIndex], stringSize);
                snprintf(listOfMovieTitlesPerYear[yearIndex], stringSize, "%s%s,", listOfMovieTitlesPerYear[yearIndex] ,movieTitle);
            }
            else { // if this is the first movie at this index, copy the movieTitle directly into that location.
                size_t memorySize = sizeof(char) * (strlen(movieTitle) + 2); // mem. size
                listOfMovieTitlesPerYear[yearIndex] = malloc(memorySize); // allocating mem.
                snprintf(listOfMovieTitlesPerYear[yearIndex], memorySize, "%s,", movieTitle);
            }


            token = strtok_r(NULL, DELIMITER, &savePtr); // skipping the language
            token = strtok_r(NULL, DELIMITER, &savePtr); // skipping the rating
            free(movieTitle);
            free(filePath);
            index += 1;
        }
        else { // if file is empty, break the loop
            break;
        }
    } // end of while loop
    fclose(fileHandler);

    char* template = "YYYY.txt";
    size_t filePathSize = sizeof(char) * (strlen(directoryName) + strlen(template) + 2);

    for(int i = 0; i < numberOfYears; i++) {

        if (listOfMovieTitlesPerYear[i] == NULL) {
            printf("Year %d is NULL. Skipping...\n", i + 1900);
            continue;

        } // if the value is not in the array, continue.
        printf("%d: %s \n", i, listOfMovieTitlesPerYear[i]);
        char* filePath = malloc(filePathSize);
        char* year = malloc(sizeof(char) * (strlen("YYYY") + 1));
        sprintf(year, "%d", i + 1900);
        char* yearWithExtension = malloc(sizeof(char) * (strlen("YYYY.txt") + 1));
        snprintf(yearWithExtension, sizeof(char) * (strlen("YYYY.txt") + 1), "%s.txt", year);
        snprintf(filePath, filePathSize, "%s/%s", directoryName, yearWithExtension);
        printf("FilePath: %s\n", filePath);
        FILE *yearFileHandler;
        yearFileHandler = fopen(filePath, "a+");

        const char* delimiter = ",";
        char* token;
        token = strtok(listOfMovieTitlesPerYear[i], delimiter);
        while (token != NULL) {
            fprintf(yearFileHandler, "%s\n", token);
            printf("Token: %s \n", token);
            token = strtok(NULL, delimiter);

        }
        //fprintf(yearFileHandler, "%s\n", listOfMovieTitlesPerYear[i]);
        fclose(yearFileHandler);
    }
} // end of "processFiles" function


void processLargestFile() {
    char* largestFileName = getLargestFileName();
    printf("\nNow processing the chosen file named %s \n", largestFileName); // outputting to the user

    char* directoryName = generateDirectoryName(); // using a function to generate the directory name and assigning that to a variable
    createDirectory(directoryName); // creating the directory


    processFiles(largestFileName, directoryName);

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