/*
Zak Rawles
5341679
2/9/24
COP3502C-0040
Lab Assignment 4 (Insert in linked list and convert to string)

Program reads atext file describing howmany trings will be read then how long they are. takes those strings and
puts each one in a linked lists and then converts them from a linked list to a string which is printed. 
*/

#include <stdio.h>
#include <stdlib.h>


typedef struct node {
char letter;
struct node* next;
} node;



// Returns number of nodes in the linkedList.
int length(node* head)
{
    //counter for number of nodes in list
    int NumOfNodes = 0;

    //traverse while head is not null / end of list
    while(head != NULL){
        NumOfNodes++; //update the counter
        head = head->next; //traverse the list
    }

    return NumOfNodes; //return final count


}



// parses the string in the linkedList
// if the linked list is head -> |a|->|b|->|c|
// then toCString function wil return "abc"
char* toCString(node* head)
{
    //init strings length and set it to value of length function
    int StringLength = length(head);

    //use dma to create a new character array and add 1 for the null terminator
    char *CharArray = (char*)malloc((StringLength+1)*sizeof(char*));
    if(CharArray == NULL){
        printf("Memory Allocation Error in CharArray");
        exit(1);
    }
    //loop through the array taking the letter from each node
    int i = 0;
    while (head != NULL) {
        CharArray[i++] = head->letter;
        head = head->next;
    }
    CharArray[i] = '\0'; // null terminator needed for the string to be valid

    //final array
    return CharArray;
    
}



// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
    //make new node and check for null, define what letter is added to the node
    node* Current = (node*)malloc(sizeof(node));
    if (Current == NULL) {
        printf("Current Node Memory Allocation Failed\n");
        exit(1);
    }
    Current->letter = c;
    Current->next = NULL; //tail

    //no head, current is head
    if (*pHead == NULL) {
        *pHead = Current;
    } 
    else {
        //traverse until null and insert the node at the tail
        node* temp = *pHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = Current;
    }
}


// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
    if(*pHead == NULL){
        return;
    }
    //traverse the list checking till NULL
    while(*pHead != NULL){
        //temp ptr to traverse the list
        node *curr = *pHead;
        free(curr);
        *pHead = (*pHead)->next;
        
    }

    *pHead = NULL;
    
}


int main(void)
{
int i, strLen, numInputs;
node* head = NULL;
char* str;
char c;
FILE* inFile = fopen("input.txt","r");
fscanf(inFile, " %d\n", &numInputs);
while (numInputs-- > 0)
{
fscanf(inFile, " %d\n", &strLen);
for (i = 0; i < strLen; i++)
{
fscanf(inFile," %c", &c);
insertChar(&head, c);
}
str = toCString(head);
printf("String is : %s\n", str);
free(str);
deleteList(&head);
if (head != NULL)
{
printf("deleteList is not correct!");
break;
}
}
fclose(inFile);
}