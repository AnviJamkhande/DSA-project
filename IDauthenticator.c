#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> // atoi
#include <string.h> // strtok
#define ID_SIZE 10

#define MAXI_LINE_LENGTH 1000
#define MAX_FIELD_LENGTH 20


struct ValidIDs
{
    char VoterID;
    int token;
};

// MAINTAINING THE index OF VOTER ID
int indexNumber = 1;


void modifycsv(const char *filename, int lineIndex) {
    FILE *file = fopen(filename, "rb+");

    if (file == NULL) {
        printf("Error: Unable to open the file.\n");
        return;
    }

    
    char line[MAXI_LINE_LENGTH];

    int currentLineIndex = 0;

    if (lineIndex == 0) {
        // Modifying the first line (lineIndex = 0)
        if (fgets(line, MAXI_LINE_LENGTH, file)) {
            if (strlen(line) >= 12) {
                fseek(file, 11, SEEK_SET); // Move the file pointer to the 12th character of the first line
                fputc('0', file); // Overwrite the character with '0'
                printf("You have successfully voted!\n");
            } else {
                printf("Error: You have already voted once.\n");
            }
        } else {
            printf("Error: Failed to read the first line.\n");
        }
    } else {
        // Modifying a line other than the first line
        while (fgets(line, MAXI_LINE_LENGTH, file)) {
            if (currentLineIndex == lineIndex - 1) {
                if (strlen(line) >= 12) {
                    fseek(file, 11, SEEK_CUR); // Move the file pointer to the 12th character
                    fputc('0', file); // Overwrite the character with '0'
                    printf("You have successfully voted!\n");
                } else {
                    printf("Error: You have already voted once.\n");
                }
                break; // Exit the loop after modifying the line
            }
            currentLineIndex++;
        }
    }

    fclose(file);
}


int areSame(char input[], char buffer[]) {
    int i = 0;
    while (i < 10) {
        if (input[i] != buffer[i]) {
            return 0;
        }
        i++;
    }
    return 1;
}

int IDauthenticator(FILE *myfile, char input[]) {
    int valid = 0;
    char buffer[80];

    while (fgets(buffer, 80, myfile)) {
        if (areSame(input, buffer)) {
            int secondEntry = buffer[10 + 1] - '0'; // Convert the second entry character to an integer
            if (secondEntry == 1) {
                valid = 1;
            }
            else{ 
                valid = -1;
            }
            break;
        }
        indexNumber++;
    }

    fclose(myfile);
    return valid;
}
