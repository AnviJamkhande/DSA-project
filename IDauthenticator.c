#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> // atoi
#include <string.h> // strtok
#define ID_SIZE 10

#define MAX_LINE_LENGTH 1000
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

    
    char line[MAX_LINE_LENGTH];

    int currentLineIndex = 0;

    if (lineIndex == 0) {
        // Modifying the first line (lineIndex = 0)
        if (fgets(line, MAX_LINE_LENGTH, file)) {
            if (strlen(line) >= 12) {
                fseek(file, 11, SEEK_SET); // Move the file pointer to the 12th character of the first line
                fputc('0', file); // Overwrite the character with '0'
                printf("Success: Modified the 12th character to '0' in the first line.\n");
            } else {
                printf("Error: The first line does not have 12 characters.\n");
            }
        } else {
            printf("Error: Failed to read the first line.\n");
        }
    } else {
        // Modifying a line other than the first line
        while (fgets(line, MAX_LINE_LENGTH, file)) {
            if (currentLineIndex == lineIndex - 1) {
                if (strlen(line) >= 12) {
                    fseek(file, 11, SEEK_CUR); // Move the file pointer to the 12th character
                    fputc('0', file); // Overwrite the character with '0'
                    printf("Success: Modified the 12th character to '0' in line %d.\n", lineIndex);
                } else {
                    printf("Error: Line %d does not have 12 characters.\n", lineIndex);
                }
                break; // Exit the loop after modifying the line
            }
            currentLineIndex++;
        }
    }

    fclose(file);
}

int areSame(char input[], char buffer[])
{
    int i = 0;
    while (i < ID_SIZE)
    {
        if (input[i] != buffer[i])
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int IDauthenticator(FILE *myfile, char input[])
{
    int bool;
    char buffer[80];

    while (fgets(buffer, 80, myfile))
    {

        if (areSame(input, buffer))
        {
            // printf("I have entered this\n");
            bool = 1;
            break;
        }
        bool = 0;
        indexNumber++;
    }
    fclose(myfile);
    return bool;
}

// ++++++++ for voting token+++++++++
// char voterCount(FILE *myfile, char input[])
// {
//     char *token;
//     char buffer[80];
//     char c;
//     indexNumber = 8;
//     printf("%d\n", indexNumber);

//     // while(fgets(buffer, 80, myfile ))
//     //  {
//     //     puts(buffer);
//     //     /* Some processing */
//     //  }

//     while (fgets(buffer, sizeof(buffer), myfile) && indexNumber > 0)
//     {
//         printf("entered ");
//         token = strtok(buffer, ",");   
//         printf("%s ", token);
//         token = strtok(NULL, ",");  
//         printf("%s ", token); 
//         indexNumber--;
//     }
//     struct ValidIDs tokenization = {*input, 0};
//     int flag = fwrite(&tokenization, sizeof(struct ValidIDs), 1, myfile);
//     return *token;
// }

int main()
{
    FILE *myfile = NULL;
    myfile = fopen("ValidIDs.csv", "r+");

    if (myfile == NULL)
    {
        printf("Trouble parsing through IDs. \nRetry again in some time....\n");
        exit(0); // or return 1
    }

    char input[80];
    printf("Enter your voter ID: ");
    scanf("%s", input);

    int flag = IDauthenticator(myfile, input);
    if (flag)
    {
        printf("Your ID is valid!\n");
    }
    else
    {
        printf("Your ID is not valid...\n");
    }

    printf("%d\n", indexNumber);

    if (flag){
        const char *filename = "ValidIDs.csv";
        modifycsv(filename, indexNumber-1);
    }
    // {
    //     printf("\n1. Candidate 1\n2. Candidate 2\n3. Candidate 3\n4. Candidate 4\n");
    //     printf("Enter your option: ");
    //     int option;
    //     scanf("%d\n", &option);
    //     if (option == 1 || option == 2 || option == 3 || option == 4)
    //     {
    //         char num = voterCount(myfile, input);
    //         printf("output is: %c\n", num);
    //         if (num)
    //         {
    //             printf("You have already voted once!\n");
    //         }
    //         else
    //         {
    //             printf("You have successfully voted Candidate %d\n", option);
    //         }
    //     }
    //     else
    //     {
    //         printf("Invalid option. Program terminating...\n");
    //     }
    // }

    return 0;
}