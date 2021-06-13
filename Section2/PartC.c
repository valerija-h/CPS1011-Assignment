/* Question 2C
 * Valerija Holomjova */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

void option();
int get_index(char *key, char *data, size_t key_len, size_t data_len);
void insert(char *key, char *data, size_t key_len, size_t data_len);
struct node *create(char *key, char *data);
void display();
void search(char *key, char *data, size_t key_len, size_t data_len);
void delete(char *key, char *data, size_t key_len, size_t data_len);
void save();


//actual data will be stored here
struct node
{
    char data[MAX];
    char key[MAX];
    struct node *next; //points to the next node
};

//point in each index
struct hash
{
    struct node *head; //position of the first node in the list
    int count; //keeps track of the number of collisions
};


//declaring it outside main so it can be used in all functions
struct hash *hash_table;
int SIZE = 0;

int main()
{
    char data[MAX], key[MAX]; //temporarily stores the key string and data string
    char choice; //temporarily stores the key string and data string


    //allocating memory for a number of 'SIZE' elements for the pointer 'hash_table'
    printf("Please enter the size of hash table.\n");
    scanf("%d", &SIZE);
    hash_table = (struct hash *) calloc(SIZE, sizeof(struct hash));

    while (getchar() != '\n');
    //displays the options the user can select
    option();
    //loops until the user inputs 'q'
    while ((choice = getchar()) != 'q')
    {
        //flushes excess characters
        while (getchar() != '\n');
        switch (choice) {
            case 'a' :
                //entering values to insert
                printf("Please enter the key to insert.\n");
                scanf("%s", key);
                printf("Please enter the data to insert.\n");
                scanf("%s", data);
                //function that enters data into array
                insert(key,data,strlen(key),strlen(data));
                //flush excess characters
                while (getchar() != '\n');
                break;

            case 'b':
                //function that displays values previously entered
                display();
                break;

            case'c':
                //entering values to search
                printf("Please enter the key to search.\n");
                scanf("%s", key);
                printf("Please enter the data to search.\n");
                scanf("%s", data);
                //function that searches for elements in array
                search(key,data,strlen(key),strlen(data));
                //flush excess characters
                while (getchar() != '\n');
                break;

            case'd':
                //entering values to delete
                printf("Please enter the key to delete.\n");
                scanf("%s", key);
                printf("Please enter the data to delete.\n");
                scanf("%s", data);
                //function that searches for elements in array
                delete(key,data,strlen(key),strlen(data));
                //flush excess characters
                while (getchar() != '\n');
                break;

            case's':
                //function that saves contents of hash table into text file
                save();
                break;

            default:
                printf("Error.\n");
                break;
        }
        //displays options for users
        option();
    }
}

//function that displays options
void option() {
    printf("\nPlease choose a,b,c,d,e or q.\n");
    printf("a - enter values.\n");
    printf("b - display values.\n");
    printf("c - searching for values.\n");
    printf("d - deleting values.\n");
    printf("s - saving values.\n");
    printf("q - quit.\n");
}

//calculates the value from the key and data
int get_index(char *key, char *data, size_t key_len, size_t data_len)
{
    int i, value = 0, key_sum = 0, data_sum = 0;
    //calculating ASCII value of the key
    for (i = 0; i < key_len; i++) {
        value = *key + i;
        key_sum += value;
    }
    //calculating the ASCII value of the data
    for (i = 0; i < data_len; i++) {
        value = *data + i;
        data_sum += value;
    }
    int total = key_sum + data_sum;
    int hash_index = total % SIZE;
    return hash_index;
}

void insert(char *key, char *data, size_t key_len, size_t data_len)
{
    int hash_index = get_index(key,data,key_len,data_len);

    //points to a new node where the key string and data string is stored
    struct node *newnode = create(key,data);

    //checks if there are 0 collisions in index
    if (hash_table[hash_index].count == 0)
    {
        //sets the head of the index to the new node
        hash_table[hash_index].head = newnode;
        hash_table[hash_index].count = 1;

    } else {
        //adds new node to the list
        //the next node of the new node becomes the data from the previous node
        newnode->next = (hash_table[hash_index].head);
        //updates the head of list, it becomes the new node
        hash_table[hash_index].head = newnode;
        hash_table[hash_index].count++;
    }
}

struct node *create(char *key, char *data)
{
    struct node *newnode;
    //creates a new node and allocates memory for it
    newnode = (struct node *) malloc(sizeof(struct node));
    //stores strings in the new node
    strcpy(newnode->key, key);
    strcpy(newnode->data, data);
    //sets the next node to null
    newnode->next = NULL;
    return newnode;
}

void display() {
    struct node *this_node;

    printf("INDEX\t\tKEY\t\tDATA\n");

    for (int i = 0; i < SIZE; i++) {
        //if there are 0 collisions in the index, check next index
        if (hash_table[i].count == 0)
            continue;

        this_node = hash_table[i].head;
        //loops until reaches NULL in the next node, meaning end of node
        while (this_node != NULL) {
            printf("%d\t\t%s\t\t%s\n", i, this_node->key, this_node->data);
            this_node = this_node->next;
        }
    }
}

void search(char *key, char *data, size_t key_len, size_t data_len) {

    int hash_index = get_index(key, data, key_len, data_len);
    bool found = false;

    struct node *this_node;
    //setting the current node to the head of the list in the index
    this_node = hash_table[hash_index].head;
    //checks if there are 0 collisions
    if (hash_table[hash_index].count == 0) {
        found = false;
    } else {
        //until the last node is checked(NULL)
        while (this_node != NULL) {
            //checks if the strings are present in the node
            if ((strstr(this_node->key, key) != NULL) && (strstr(this_node->data, data) != NULL)) {
                printf("Data is located in index %d.", hash_index);
                found = true;
                break;
            }
            this_node = this_node->next;
        }
    }
    //if data can not be found
    if (found == false)
        printf("Data not found.\n");
}

void delete(char *key, char *data, size_t key_len, size_t data_len){
    int hash_index = get_index(key,data,key_len,data_len);
    bool found = false;

    struct node *temp, *this_node;
    //sets the position of the node to the head of the index
    this_node = hash_table[hash_index].head;

    //checks if there 0 collisions
    if (hash_table[hash_index].count == 0) {
       found = false;
    } else {
        //if data is not found in the head of the index, temp will represent the previous node
        temp = this_node;

        //loops until it checks the last node
        while (this_node != NULL) {
            //checks if the key and data matches
            if ((strstr(this_node->key, key) != NULL) && (strstr(this_node->data, data) != NULL)) {
                found = true;

                //checks if the node is at the head of the index
                if (this_node == hash_table[hash_index].head)
                    //sets the head to NULL
                    hash_table[hash_index].head = this_node->next;
                else
                    //the following nodes of temp are set to the following nodes of next
                    //this_node is no longer needed in the list
                    temp->next = this_node->next;

                //reduces amount of collisions in the table
                hash_table[hash_index].count--;
                //deallocates memory of this_node
                free(this_node);
                break;
            }
            //if the key and data does not match, check the next node
            //in the next loop, temp will represent the node before this_node as this_node is assigned to the next node
            temp = this_node;
            this_node = this_node->next;
        }
    }

    if (found == true)
        printf("Data deleted.\n");
    else
        printf("Data not found.\n");

}

void save(){
    FILE *f;
    printf("Saving...\n");
    //opening a file of writing type
    f = fopen("hash_table_c.txt", "w");
    //executes if there is problem opening the file
    if (f == NULL)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    struct node *this_node;

    for (int i = 0; i < SIZE; i++) {
        //if there are 0 collisions in the index, check next index
        if (hash_table[i].count == 0)
            continue;

        this_node = hash_table[i].head;
        int j = 0;

        //loops until reaches NULL in the next node, meaning the last node has been checked
        while (this_node != NULL) {
            fprintf(f,"Index:%d\tCollision:%d\tKey:%s\tData:%s\n", i, j, this_node->key, this_node->data);
            this_node = this_node->next;
            j++;
        }
    }
    printf("Saved.\n");
    fclose(f);
}