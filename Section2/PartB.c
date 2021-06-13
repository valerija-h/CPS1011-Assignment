/* Question 2B
 * Valerija Holomjova */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

void option();
int get_index(char *key, char *data, size_t key_len, size_t data_len);
void insert(char *key, char *data, size_t key_len, size_t data_len);
void display();
void search(char *key, char *data, size_t key_len, size_t data_len);
void delete(char *key, char *data, size_t key_len, size_t data_len);
void save();

//struct representing the actual data points
struct point{
    char key[MAX]; //stores the users inputted key string
    char data[MAX]; //stores the users inputted data string
};

struct hash{
    struct point *col; //points to the position of the first collision in the index
    int count; //keeps track of how many data points there are in each index
};

//initializing hash_table and SIZE outside the array so its applicable in all functions
int SIZE = 0;
struct hash *hash_table;

int main(){
    int choice; //stores a character to be used in switch statement
    char key[MAX],data[MAX]; //temporarily stores the key string and data string

    printf("Please enter the size of hash table.\n");
    scanf("%d", &SIZE);
    //allocating memory for a number of 'SIZE' elements for the pointer 'hash_table'
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
void insert(char *key, char *data, size_t key_len, size_t data_len)
{
    //calculates the hash_index using a function
    int hash_index = get_index(key,data,key_len,data_len);
    int i = 0;

    //creating a temporary data point called which will hold the key and data
    struct point temp;
    //copying the key and data into the temporary data point
    strcpy(temp.key, key);
    strcpy(temp.data, data);

    //checks if there are 0 collisions in the hash index
    if(hash_table[hash_index].count == 0)
    {
        //allocates memory for the first data point in the particular hash_index
        hash_table[hash_index].col = malloc(sizeof(struct point));
        //the first element in the hash_index is copied from the temporary node
        hash_table[hash_index].col[0] = temp;
        hash_table[hash_index].count = 1;
    } else {
        //executes if there were previous data points in the hash_index
        i = hash_table[hash_index].count;
        //i is used to deduce how much memory is to be reallocated to fit in an additional data point
        hash_table[hash_index].col = realloc(hash_table[hash_index].col, sizeof(struct point)*(i+1));
        //stores the information from the temporary node into the new data point(collision)
        hash_table[hash_index].col[i] = temp;
        hash_table[hash_index].count++;

    }
}

//function the prints values for hash_table
void display() {
    //creating a temporary pointer to a data point
    struct point *temp;

    printf("INDEX\tKEY\tDATA\n");
    for (int i = 0; i < SIZE; i++) {
        //if there are 0 collisions in the index, checks the next index
        if (hash_table[i].count == 0)
            continue;

        //points to the first element in the hash_index
        temp = hash_table[i].col;

        //prints out the values in each collision of the index
        for(int j = 0; j < hash_table[i].count; j++) {
            printf("%d\t%s\t%s\n", i, temp[j].key, temp[j].data);
        }
    }
}

//function that searches for certain elements in the array
void search(char *key, char *data, size_t key_len, size_t data_len) {
    //calculates the hash_index
    int hash_index = get_index(key,data,key_len,data_len);
    //true when values are found
    bool found = false;

    struct point *temp;
    //pointer to the first element in the index
    temp = hash_table[hash_index].col;
    //count represents the number of data points in the array
    int count = hash_table[hash_index].count;

    //checks if the index has 0 collisions or not
    if(hash_table[hash_index].count == 0) {
        //data not found if there are no collisions to search
        found = false;
    } else {
        //loops until the entire index is searched
        for (int i = 0; i < count; i++) {
            //checks if key and data are present in the current collision
            if((strstr(temp[i].key, key) != NULL) && (strstr(temp[i].data, data) != NULL)) {
                found = true;
                break;
            }
        }
    }
    //displays whether the values were found our not
    if(found == false) {
        printf("Data not found.\n");
    } else {
        printf("Data can be found in index %d.\n",hash_index);
    }
}

void delete(char *key, char *data, size_t key_len, size_t data_len){
    //calculates hash_index
    int hash_index = get_index(key,data,key_len,data_len);
    bool found = false; //true when data points are found in array

    struct point *temp;
    //points to the first element in the index
    temp = hash_table[hash_index].col;

    //checks if there are 0 collisions in the hash index
    if(hash_table[hash_index].count == 0) {
        found = false;
    } else {
        //goes through each data-point in the index
        for (int i = 0; i < hash_table[hash_index].count; i++) {
            //executes if the key and data matches in the collision
            if((strstr(temp[i].key, key) != NULL) && (strstr(temp[i].data, data) != NULL)) {
                found = true;
                for (int j = i; j < hash_table[hash_index].count; j++) {
                    temp[j] = temp[j+1];
                }
                //count decreases as one data point is removed
                (hash_table[hash_index].count)--;
                //reallocate the memory to adjust to one less node
                hash_table[hash_index].col = realloc(hash_table[hash_index].col, sizeof(struct point)*(hash_table[hash_index].count));
                break;
            }
        }
    }
    if(found == false) {
        printf("Data not found.\n");
    }
}

void save() {
    FILE *f;
    printf("Saving...\n");
    //opening a file of writing type
    f = fopen("hash_table_b.txt", "w");
    //executes if there is problem opening the file
    if (f == NULL)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    struct point *temp;

    for (int i = 0; i < SIZE; i++) {
        //if there are 0 collisions in the index, check next index
        if (hash_table[i].count == 0)
            continue;

        //points to the first element in the hash_index
        temp = hash_table[i].col;

        //prints out the values in each collision in the index
        for(int j = 0; j < hash_table[i].count; j++) {
            fprintf(f,"Index:%d\tCollision:%d\tKey:%s\tData:%s\n", i, j, temp[j].key, temp[j].data);
        }
    }
    printf("Saved.\n");
    fclose(f);
}
