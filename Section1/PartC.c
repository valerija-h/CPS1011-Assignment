/* Question 1C
 * Valerija Holomjova */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool compare_strings_case(char string1[],char string2[]);   //function that compares strings that are case-sensitive
bool compare_strings(char string1[],char string2[]);        //function that compares strings that are case-insensitive

int main(){
    FILE *f;             //pointer to a file object
    char *line = NULL;   //address of first character in buffer (in the line)
    size_t length;       //length of each line (or size of buffer)
    bool end = false;    //true if at least one condition is met (file is recognizable)
    bool html_1 = false; //true if <html> is present (at start)
    bool html_2 = false; //true if </html> is present (at end)

    //opens a text file which it will read
    f = fopen("input.txt","r");
    //executes if there is trouble opening file
    if (f == NULL)
    {
        printf("Error opening file.\n");
        return (EXIT_FAILURE);
    }

    //scans each line and stores it in a buffer
    while ((getline(&line, &length, f)) != EOF)
    {
        //checks if <html> or if </html> is present in file
        if ((compare_strings(line,"<html>")) == true) {
            end = true;
            html_1 = true;
        }
        else if ((compare_strings(line,"</html>")) == true) {
            end = true;
            html_2 = true;
        }

        //if the start of the html hasn't been detected, it will search for a C file
        //ensures that the file can't be both C and HTML type (also cause of break below)
        if( html_1 == false) {
            //checks if #include is present in file
            if ((compare_strings_case(line, "#include")) == true) {
                printf("The file is of C type.\n");
                end = true;
                //exits while loop to stop searching
                break;
            }
        }
    }

    if(html_1 == true && html_2 == true) {
        //if the file contains both </html> and <html>, it is a complete html file
        printf("The file is of HTML type.\n");
    } else if (html_1 == true || html_2 == true) {
        //if it contains either </html> or <html> but not both, it is an incomplete html file
        printf("The HTML file is incomplete.");
    }

    //executes if file is neither of specified above
    if (end == false) {
        printf("Can't recognize file type.\n");
    }

    //closes file
    fclose(f);
    return 0;
}

//function that compares case-sensitive strings
bool compare_strings_case(char string1[],char string2[]) {
    bool contains = false;
    //if strings are identical, function will return TRUE
    if(strstr(string1, string2) != NULL) {
        contains = true;
    }
    return contains;
}

//function compares case-insensitive strings
bool compare_strings(char string1[],char string2[]) {
    bool contains = false;
    //if strings are identical (case-insensitive), function will return TRUE
    if (strcasestr(string1, string2) != NULL) {
        contains = true;
    }
    return contains;
}
