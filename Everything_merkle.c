//Merkle tree with voting interface, and counts votes, errors:Merkle tree not getting built
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "IDauthenticator.h"
#define maxinputLen 100
#define maxinputleaves 100
#define COUNT 10
#define MAX_STRINGS 100
#define MAX_LENGTH 100
#define NUM_CANDIDATES 4

struct Node
{
    int data;
    struct Node *left, *right;
};

struct Node *newNode(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));

    node->data = data;
    node->left = node->right = NULL;
    return (node);
};

// Function to insert nodes in level order
struct Node *insertLevelOrder(unsigned int arr[], int i, int n)
{
    struct Node *root = NULL;
    // Base case for recursion
    if (i < n)
    {
        root = newNode(arr[i]);

        // insert left child
        root->left = insertLevelOrder(arr,
                                      2 * i + 1, n);

        // insert right child
        root->right = insertLevelOrder(arr,
                                       2 * i + 2, n);
    }
    return root;
};

void print2DUtil(struct Node *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(struct Node *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

#define MAX_LINE_LENGTH 100
#define MAX_STRING_COUNT 100

int moveCSVContents(const char *sourcePath, const char *destinationPath)
{
    FILE *sourceFile = fopen(sourcePath, "r");
    FILE *destinationFile = fopen(destinationPath, "w");

    if (sourceFile == NULL || destinationFile == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];

    // Read from source file and write to destination file
    while (fgets(line, MAX_LINE_LENGTH, sourceFile) != NULL)
    {
        fputs(line, destinationFile);
    }

    // Close the files
    fclose(sourceFile);
    fclose(destinationFile);

    printf("Content moved successfully.\n");

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readCSVFile(const char *filePath, char **stringArray)
{
    FILE *file = fopen(filePath, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int stringCount = 0;

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
    {
        // Remove newline character from the end of the line
        line[strcspn(line, "\n")] = '\0';

        // Allocate memory for the string and copy it to the string array
        stringArray[stringCount] = malloc(sizeof(char) * (strlen(line) + 1));
        strcpy(stringArray[stringCount], line);

        stringCount++;

        if (stringCount >= MAX_STRING_COUNT)
        {
            printf("Exceeded maximum string count.\n");
            break;
        }
    }

    // Close the file
    fclose(file);

    return stringCount;
}

unsigned int hash(char *str)
{
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int numberlength(int num)
{
    int len = 0, n;
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    return len;
}

void tostring(char str[], unsigned int num)
{
    int i, rem, len = 0;
    unsigned int n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

unsigned int hash_function(unsigned int input, unsigned int prev_hash)
{

    int prevhashlength = numberlength(prev_hash);
    char prevhashstring[prevhashlength];
    int inputlength = numberlength(input);
    char inputstring[inputlength];
    tostring(prevhashstring, prev_hash);
    tostring(inputstring, input);

    unsigned long n = (strlen(inputstring) + strlen(prevhashstring));
    char *cat = (char *)malloc((n + 1) * sizeof(char));
    strcat(cat, prevhashstring);
    strcat(cat, inputstring);
    printf("\nAFTER:%s\n", cat);

    unsigned int Hash = hash(cat);
    return Hash;
}

int HowmanyTrans(char Data[maxinputleaves][maxinputLen])
{
    int c = -1;
    do
    {
        c++;
    } while (strcmp(Data[c], ""));
    return c;
}

void transferStrings(char *strings[maxinputleaves], char Data[maxinputleaves][maxinputLen])
{
    for (int i = 0; i < maxinputleaves; i++)
    {
        if (strings[i] != NULL)
        {
            strncpy(Data[i], strings[i], maxinputLen - 1);
            Data[i][maxinputLen - 1] = '\0'; // Ensure null-termination
        }
    }
}

void processStrings(char *strings[], int count)
{   printf("HIII");
    printf("Processing %d strings:\n", count);
    for (int i = 0; i < count; i++)
    {
        printf("String %d: %s\n", i + 1, strings[i]);
    }
    char Data[maxinputleaves][maxinputLen];
    memset(Data, 0, sizeof(Data)); // Initialize Data array to all zeros

    // I MADE THE FUNCTIONS FOR A 2D ARRAY BUT TOOK A 1D INPUT SO I HAD TO DO THIS -- strings is 1D and Data is 2D
    transferStrings(strings, Data);

    int leaves = HowmanyTrans(Data);
    // leaf nodes not necessarily on same level
    int totalnodes = (2 * leaves) - 1;
    // level starting at 1 at root

    unsigned int FinalArray[totalnodes];
    int leafindex = 0;
    int level = 0;
    for (int i = 1; (pow(2, i)) <= totalnodes; i++)
    {
        level = i;
    }

    if ((totalnodes) == pow(2, level))
    {
    }
    else
    {
        level++;
    }

    // fill in leaves right to left
    printf("totalnodes %d\n", totalnodes);
    // printf("level %d\n",level);
    // printf("leaves %d\n",leaves);
    for (int i = (totalnodes - leaves); i <= (totalnodes - 1); i++)
    {
        FinalArray[i] = hash(Data[leafindex]); // THIS IS ME REMOVING HASHING CUZ WE'RE HASHING WITH TIME ANYWAYS
        // FinalArray[i] = Data[leafindex];
        leafindex++;
    }
    for (int i = (totalnodes - leaves - 1); i >= 0; i--)
    {
        int right = 2 * i + 1;
        int left = 2 * i + 2;
        if (totalnodes <= right)
        {
            FinalArray[i] = FinalArray[right];
        }
        else
        {
            FinalArray[i] = hash_function(FinalArray[left], FinalArray[right]);
        };
    }

    for (int i = 0; i < totalnodes - 1; i++)
    {
        printf("%d\n", FinalArray[i]);
    }
    struct Node *root = insertLevelOrder(FinalArray, 0, totalnodes);
    print2D(root);
    printf("Processing complete.\n");
}

char *getCurrentTime()
{
    time_t currentTime;
    time(&currentTime);
    return ctime(&currentTime);
}

// Function to write vote counts to a CSV file
void writeVoteCountsToCSV(const char *filename, int voteCounts[]) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Unable to open the file for writing.\n");
        return;
    }

    for (int i = 0; i < 4; i++) {
        fprintf(file, "%d\n", voteCounts[i]);
    }

    fclose(file);
}

// Function to read vote counts from a CSV file
void readVoteCountsFromCSV(const char *filename, int voteCounts[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        // If the file doesn't exist or is empty, initialize the vote counts to 0
        for (int i = 0; i < 4; i++) {
            voteCounts[i] = 0;
        }
        return;
    }

    for (int i = 0; i < 4; i++) {
        fscanf(file, "%d", &voteCounts[i]);
        
    }

    fclose(file);
}

int main()
{
    
    const char *votefile = "VoteCounts.csv";
    int voteCounts[4];

    // Read vote counts from the CSV file
    readVoteCountsFromCSV(votefile, voteCounts);
    // for(int i=0;i<5;i++)
    //     printf("%d\n",voteCounts[i]);

    char *strings[maxinputleaves] = {0}; // HERE YA'LL NEED TO ADD THE FILE READ PREVIOUS INPUTS OPTION, THIS IS INITIAL STRING

    int count = 0;
    char input[MAX_LENGTH];
    int choice;
    char *currentTime;

    //const char *filePath = "input.csv";
    // // char* stringArray[MAX_STRING_COUNT] = { NULL };
    // int stringCount = readCSVFile(filePath, strings);
    // if (stringCount <= 0)
    // {
    //     printf("An error occurred while reading the file.\n");
    // }

    // // Print the strings from the array
    // for (int i = 0; i < stringCount; i++)
    // {
    //     printf("String %d: %s\n", i + 1, strings[i]);
    // }
    // count = readCSVFile(filePath, strings);

    while (1)
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
        if (flag==1)
        {
            printf("Your ID is valid!\n");
        }
        else if(flag==-1)
        {
            printf("You have already voted!\n");
            flag=0;
        }
        else
        {
            printf("Your ID is not valid...\n");
        }

        if (flag)
        {
            printf("\n1. Candidate 1\n2. Candidate 2\n3. Candidate 3\n4. Candidate 4\n");
            printf("Enter your option: ");
            int option;
            scanf("%d", &option);
            if (option == 1 || option == 2 || option == 3 || option == 4)
            {   
                // token system
                const char *filename = "ValidIDs.csv";
                modifycsv(filename, indexNumber - 1);

                // adding votes system
                if (option >= 1 && option <= 4) {
                    voteCounts[option - 1]++;
                    printf("Your vote has been recorded.\n");

                
                sprintf(input, "%d", option);
                //fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0'; // Remove newline character

                unsigned int inputHash = hash(input);

                unsigned int timeHash;

                currentTime = getCurrentTime();
                printf("Current time: %s", currentTime);

                timeHash = hash(currentTime);

                unsigned int combinedHash = hash_function(inputHash, timeHash);

                char combinedHashString[65]; // Array to store the combined hash as a string
                sprintf(combinedHashString, "%u", combinedHash);
                
                strings[count] = malloc(sizeof(char) * (strlen(combinedHashString) + 1));
                strcpy(strings[count], combinedHashString);
                count++;

                // Write the updated vote counts to the CSV file
                writeVoteCountsToCSV(votefile, voteCounts);

                //const char *filename = "ValidIDs.csv";
                modifycsv(filename, indexNumber - 1);

            }
            else
            {
                printf("Invalid option. Program terminating...\n");
                break;
            }

            
        }
    }

    // do
    // {
    //     printf("Enter a string: "); // HERE U CAN ADD TRANSACTIONS
    //     fgets(input, sizeof(input), stdin);
    //     input[strcspn(input, "\n")] = '\0'; // Remove newline character

    //     unsigned int inputHash = hash(input);

    //     unsigned int timeHash;

    //     currentTime = getCurrentTime();
    //     printf("Current time: %s", currentTime);

    //     timeHash = hash(currentTime);

    //     unsigned int combinedHash = hash_function(inputHash, timeHash);

    //     char combinedHashString[65]; // Array to store the combined hash as a string
    //     sprintf(combinedHashString, "%u", combinedHash);

    //     strings[count] = malloc(sizeof(char) * (strlen(combinedHashString) + 1));
    //     strcpy(strings[count], combinedHashString);
    //     count++;

    //     printf("Do you want to add another string? (y/n): ");
    //     scanf(" %c", &choice);
    //     getchar(); // Consume the newline character
    // } while (choice == 'y' || choice == 'Y');

    processStrings(strings, count); // HERE IS WHERE THE ACTUAL MERKLE TREE GETS MADE

    // const char *sourcePath = "CURRENTHASHES.csv";
    // const char *destinationPath = "OLDHASHES.csv";

    // int result = moveCSVContents(sourcePath, destinationPath);
    // if (result != 0)
    // {
    //     printf("An error occurred while moving the contents.\n");
    // }

    // Free the memory allocated for each string
    for (int i = 0; i < count; i++)
    {
        free(strings[i]);
    }
return 0;

}
}    
