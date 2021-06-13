/* Question 2A
 * Valerija Holomjova */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
#define SIZE 5

void option();
int get_index(char *key, char *data, size_t key_len, size_t data_len);
void insert(char *key, char *data, size_t key_len, size_t data_len);
void display();
void search(char *key, char *data, size_t key_len, size_t data_len);
void delete(char *key, char *data, size_t key_len, size_t data_len);
void save();

//struct containing key and data that the user will input
struct point {
    char key[MAX];
    char data[MAX];
};

//creating a 2D array 'TABLE' with type hash_table outside array so it's applicable in all functions
//array is predefined with parameters SIZE
struct point TABLE[SIZE][SIZE];

int main() {
    char key[MAX], data[MAX], choice;

    //setting the first character of the strings in each elements to NULL
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            TABLE[i][j].key[0] = '\0';
            TABLE[i][j].data[0] = '\0';
        }
    }

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

//function that calculates the hash_index using the ASCII value of key and data
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

//function that enters values into the array
void insert (char *key, char *data, size_t key_len, size_t data_len)
{
    bool empty = false;
    int count = 0, i; //count keeps track of the collisions in the index
    //calculates the hash_index using a function
    int hash_index = get_index(key,data,key_len,data_len);

    //checks if position in array is empty
    while (empty == false) {
        //executes if the total number of collisions in the hash index has been reached
        if (count == 5) {
            printf("The total number of collisions in the hash table has been reached.");
            break;
        }
        if (TABLE[hash_index][count].key[0] == '\0') {
            //copies key
            for (i = 0; i < key_len; i++) {
                TABLE[hash_index][count].key[i] = key[i];
            }
            //copies data
            for (i = 0; i < data_len; i++) {
                TABLE[hash_index][count].data[i] = data[i];
            }
            //true because an empty space was found, and strings were copied
            empty = true;
        } else {
            //increment count to keep searching for an empty space
            count++;
        }
    }
}

//function the prints values for hash table
void display() {
    printf("INDEX\tKEY\tDATA\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            //only prints values that were previously inputted (not NULL)
            if (TABLE[i][j].key[0] != '\0') {
                printf("%d\t%s\t%s\n", i, TABLE[i][j].key, TABLE[i][j].data);
            }
        }
    }
}

//function that searches for certain elements in the array
void search (char *key, char *data, size_t key_len, size_t data_len) {
    //search if element is in array, true if found
    bool found = false;

    //gets index from key and data
    int hash_index = get_index(key,data,key_len,data_len);

    for(int i = 0; i < SIZE; i++)
    {
        //checks if key and data are present in the array
        if((strstr(TABLE[hash_index][i].key,key) != '\0') && (strstr(TABLE[hash_index][i].data,data) != '\0')) {
            found = true;
            printf("Data can be found in index %d.\n",hash_index);
            break;
        } else {
            found = false;
        }
    }
    if (found == false) {
        printf("Data cannot be found.\n");
    }
}

//function that searches for certain elements in the array then deletes them
void delete (char *key, char *data, size_t key_len, size_t data_len) {
    //search if element is in array, true if found
    bool found = false;

    //gets index from key and data
    int hash_index = get_index(key,data,key_len,data_len);

    for (int i = 0; i < SIZE; i++) {
        //checks if key and data are present in array
        if ((strstr(TABLE[hash_index][i].key, key) != '\0') && (strstr(TABLE[hash_index][i].data, data) != '\0')) {
            //if present, sets found to true
            found = true;

            //replaces the data and increments the array by one
            for (int j = i; j < SIZE; j++) {
                //copies the strings
                for (int k = 0; k < MAX; k++) {
                    TABLE[hash_index][j].key[k] = TABLE[hash_index][j+1].key[k];
                    TABLE[hash_index][j].data[k] = TABLE[hash_index][j+1].data[k];
                }
                //setting the last elements in the array to 0
                TABLE[hash_index][SIZE].key[0] = '\0';
                TABLE[hash_index][SIZE].data[0] = '\0';
            }
            printf("Data successfully deleted.\n");
            break;
        } else {
            //false if there was not match in the array
            found = false;
        }
    }

    if (found == false) {
        printf("Data cannot be found.\n");
    }
}

//function that saves to output file
void save() {
    FILE *f;
    printf("Saving...\n");
    //opening a file of writing type
    f = fopen("hash_table_a.txt", "w");
    //executes if there is problem opening the file
    if (f == NULL)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    //copies the elements of the array into a text file
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            //if null is present in the string or key 'Null' will be displayed
            if (TABLE[i][j].key[0] == '\0' || TABLE[i][j].data[0] == '\0' ) {
                fprintf(f, "Null\n");
            } else {
                fprintf(f, "%s, ", TABLE[i][j].key);
                fprintf(f, "%s\n", TABLE[i][j].data);
            }
        }
    }
    printf("Saved.\n");
    fclose(f);
}
