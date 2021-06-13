/* Question 1E
 * Valerija Holomjova */

#include <stdio.h>

void view_stackframe(int array[], int length);

int main()
{
    //n represents the size of the array 'value'
    int n = 5;
    int value[n];

    //initializing elements of the array 'value'
    value[0] = 1;
    value[1] = 10;
    value[2] = 50;
    value[3] = 22;
    value[4] = 47;
    value[5] = 36;

    //calling function that will print out the values and memory address of each element
    view_stackframe(value, n);
    return 0;
}

void view_stackframe(int value[], int length){
    int i;
    //prints out the value and memory address in two separate columns
    for(i = 0; i <= length; i++)
    {
        printf("%d\t\t%p\n", value[i], value[i]);
    }
}


