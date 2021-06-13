/* Question 1D
 * Valerija Holomjova */

#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
#define SPACE ' '
#define COMMA ','
#define DOT '.'


void word_check(char str[], int x, int length, FILE *f);

int main() {
    char ch[MAX]; //stores each character from the text file
    int n = 0; //total number of characters stored in 'ch'
    int letters = 0; //temporarily keeps track of the length of each word
    int i; //index
    FILE *f; //file pointer

    //the file is opened for reading
    f = fopen("auto-correct.txt","r");
    //executes if there is error opening file
    if (f == NULL) {
        printf("Error opening file.\n");
        return (EXIT_FAILURE);
    }

    //scans the entire file, until the end, and stores each characters in an array ch
    while ((ch[n] = getc(f)) != EOF) {
        n++; //counts the number of characters inputted
    }
    ch[n] = '\0'; //sets the last character of the array to NULL

    //closes the file
    fclose(f);
    //reopens the file but this time for writing and overwrites the data
    f = fopen("auto-correct.txt","w+");
    //executes if there is error opening file
    if (f == NULL) {
        printf("Error opening file.\n");
        return (EXIT_FAILURE);
    }

    //goes through loop for total number of characters
    for (i = 0; i < n; i++) {
        //checks if there is a space, comma or dot, indicating the end of a word
        //if there is, letters will be reset to 0, or else, if 12 letters already occurred, function will execute
        if(ch[i] == SPACE || ch[i] == COMMA || ch[i] == DOT) {
            if (letters >= 12) {
                //function that asks the user whether the input was correct
                word_check(ch, i, letters, f);
                //letter counter resets
                letters = 0;
            } else {
                letters = 0; //if there wasn't 12 letters, letter counter reset
            }
        } else {
            letters++; //if not space, comma or dot letter counter incremented
        }

        //checks if there is a double space
        if (ch[i] == SPACE && ch[i-1] == SPACE) {
            //removes space by moving up array by one
            for(int j = i; j < n; j++) {
                ch[j] = ch[j+1];
            }
            //sets last character to null and decreases total number of characters in array
            ch[n-1] = '\0';
            n--;
            //checks if there is a comma and space
        } else if (ch[i] == COMMA && ch[i-1] == SPACE) {
            //replaces space with comma and moves up array by one
            for(int j = i; j < n; j++) {
                ch[j-1] = ch[j];
            }
            //sets last character to null and decreases total number of characters in array
            ch[n-1] = '\0';
            n--;
        } else if (ch[i] == DOT && ch[i-1] == SPACE) {
            //replaces space with dot and moves up array by one
            for (int j = i; j < n; j++) {
                ch[j - 1] = ch[j];
            }
            //sets last character to null and decreases total number of characters in array
            ch[n-1] = '\0';
            n--;
        }
    }

    //prints the corrected version of the input into file
    fprintf(f,"\nCorrected output:\n%s", ch);
    //closes file
    fclose(f);
    return 0;
}

void word_check(char str[], int x, int length, FILE *f) {
    //length = the amount of letters in the word
    //str = the address of the first character in the char array
    //x = the character after the last character of the word in the char array (will be a space, comma or dot)
    int i;

    fprintf(f, "Are you sure you meant ");
    //prints the word that is longer than 12 words
    for (i = (x - length); i < x; i++) {
        fprintf(f, "%c", str[i]);
    }
    fprintf(f, "?\n");
}
