#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define maxinputLen 100
#define maxinputleaves 100

#define COUNT 10

typedef struct Block {
    char region[256];
    signed int hash;
    struct Node* root;
    struct Block* next;
    struct Block* previous;
} Block;


struct Node
{
    int data;
    struct Node* left, * right;
};

//For linked list

/*explanation, Once every region has voted, the root will be passed to insertBlock. Here the block is cretaed first.
Then the block has a pointer towards the root, the region. The hash of the block will be the hash of the
previous block along with the hash of the root.


*/

Block* createBlock(const char* region, signed int previousHash, struct Node* root) {
    Block* block = (Block*)malloc(sizeof(Block));
    strcpy(block->region, region);
    block->previousHash = previousHash;
    block->root = root;
    block->next = NULL;
    block->previous = NULL;
    return block;
}

Block* insertBlock(Block** head, const char* region, struct Node* root) {
    Block* block = createBlock(region, 0, root);  // Initialize previousHash as 0 for the first block
    if (*head == NULL) {
        *head = block;
    } else {
        Block* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        block->previous = current;
        block->previousHash = current->hash;
        block->hash = generateBlockHash(current->hash, root->hash);
        current->next = block;
    }
    return block;
}

void printLinkedList(Block* head) {
    Block* current = head;
    while (current != NULL) {
        printf("Region: %s\n", current->region);
        printf("Hash: %s\n", current->hash);
        printf("-----------\n");
        current = current->next;
    }
}

signed int generateBlockHash(const signed int previousHash, const char* rootHash) {
    // Implement your custom hash function here
    // You can combine the previousHash and rootHash to compute the block hash
    // Return the computed hash
    // This is just a placeholder implementation
    return previousHash + strlen(rootHash);
}

// for tree
struct Node* newNode(int data)
{  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
   
    node->data = data;
    node->left = node->right = NULL;
    return (node);
};



// Function to insert nodes in level order
struct Node* insertLevelOrder(int arr[],int i, int n)
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
 
void print2DUtil(struct Node* root, int space)
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
void print2D(struct Node* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
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
{ int len = 0, n;
  n = num;
  while (n != 0)
    {  len++;
        n /= 10;
    }
    return len;
}

void tostring(char str[], unsigned int num)
{ int i, rem, len = 0;
  unsigned int n = num;
  while (n != 0)
    {  len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    { rem = num % 10;
      num = num / 10;
      str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}



unsigned int hash_function(unsigned int input, unsigned int prev_hash){
    printf("\nBEFORE: %d",input);
    int prevhashlength = numberlength(prev_hash);
    char prevhashstring[prevhashlength];
    int inputlength = numberlength(input);
    char inputstring[inputlength];
    tostring(prevhashstring, prev_hash);
    tostring(inputstring, input);
    printf("\nPrev hash: %s",prevhashstring);
    unsigned long n = (strlen(inputstring)+strlen(prevhashstring));
    char* cat= (char*) malloc((n+1)*sizeof(char));
    strcat(cat, prevhashstring);
    strcat(cat, inputstring);
    printf("\nAFTER:%s\n",cat);
    
    unsigned int Hash = hash(cat);
    return Hash;
}


int HowmanyTrans(char Data[maxinputleaves][maxinputLen])
{
int c=-1;
do{ c++; }
while (strcmp(Data[c], ""));
    return c;
}

int main() {
     char Data[maxinputleaves][maxinputLen] = {"AARYA DID IT","AARYA DID NOT","yguhu","AARYA DINOT","AARYA DD NOT","AARY DID NOT","TEJ DID NT"};
    int leaves = HowmanyTrans(Data);
    //leaf nodes not necessarily on same level
    int totalnodes = (2*leaves) - 1;
    //level starting at 1 at root
   
    unsigned int FinalArray[totalnodes];
    int leafindex = 0;
    int level=0;
    for(int i = 1;(pow(2,i))<=totalnodes;i++)
        {
            level = i;
        }
  
    if((totalnodes)==pow(2,level))
    { }
    else
    { level++;}
        


    //fill in leaves right to left
   printf("totalnodes %d\n",totalnodes);
   // printf("level %d\n",level);
    //printf("leaves %d\n",leaves);
    for(int i = (totalnodes-leaves);i<=(totalnodes-1);i++)
    {
        FinalArray[i] = hash(Data[leafindex]);
        leafindex++;
        }
    for(int i = (totalnodes-leaves-1);i>=0;i--)
    {
        int right = 2i+1;
        int left = 2i+2;
        if (totalnodes<=right)
        {FinalArray[i]=FinalArray[right];}
        else
        {FinalArray[i] = hash_function(FinalArray[left], FinalArray[right]);};
    }


    
    for (int i = 0; i < totalnodes-1; i++)
    { printf("%d\n", FinalArray[i]);}
    struct Node* root =  insertLevelOrder(FinalArray,0, totalnodes);
    print2D(root);
    
    }
                                    





