/* Question 1A
 * Valerija Holomjova */

#include <stdio.h>
#define BASE 200 //starting amount for each person

int main() {
    float CI, SI;
    const float CI_rate = 0.1; //Joan's interest rate compounded annually
    const float SI_rate = 0.15; //Tom's simple interest rate annually

    int year = 1;
    CI = BASE + (BASE*CI_rate); //Joan's CI after one year
    SI = BASE + (BASE*SI_rate); //Tom's SI after one year

    while(CI < SI) //loop will repeat until Joan's CI exceeds Tom's SI
    {
        CI += CI * CI_rate; //calculates CI and adds onto the total of previous CI every loop(year)
        SI += BASE * SI_rate; //calculates SI and adds onto the total of previous SI every loop(year)
        year++; //keeps track of the years
    }

    printf("It takes %d years for Joan's invested sum to overtake Tom's.\n", year);
    printf("After %d years Joan's sum is $%.2f and Tom's sum is $%.2f.\n", year,CI,SI);
}
