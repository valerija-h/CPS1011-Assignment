/* Question 1B
 * Valerija Holomjova */

#include <stdio.h>
#include <stdlib.h>
#define P_A 2.05 //price artichokes per kg
#define P_O 1.15 //price onions per kg
#define P_C 1.09 //price carrots per kg
#define DISC .05 //discount

char get_choice(); //function the reads user input for choice
float get_weight(); //function the reads user input for weight
void display(float TW_A, float TW_O, float TW_C); //function that displays a summary of all the items and costs
void get_receipt(float TW_A, float TW_O, float TW_C); //function that saves the summary in a file

int main() {
    char choice;
    float TW_A = 0, TW_O = 0, TW_C = 0; //total weight of apple, onion and carrot

    //greats the user
    printf("Welcome to YourGreens.com.\n");
    //gets the choice of the user and loops until user enters q
    while ((choice = get_choice()) != 'q')
    {
        switch (choice)
        {
            case 'a' :
                printf("\nPlease enter amount of artichokes in kg. \n");
                //adds weight to the total weight of artichokes
                TW_A += get_weight();
                break;

            case 'b' :
                printf("\nPlease enter amount of onions in kg. \n");
                //adds weight to the total weight of onions
                TW_O += get_weight();
                break;

            case 'c' :
                printf("\nPlease enter amount of carrots in kg. \n");
                //adds weight to the total weight of carrots
                TW_C+= get_weight();
                break;

            default :
                //displays after incorrect input
                printf("\nProgram Error.\n");
                break;

        }
    }

    //removes excess possible characters
    while (getchar() != '\n');

    //function that displays a summary of all the items and costs
    display(TW_A,TW_O,TW_C);

    //asks the user if they wants a copy of the receipt
    printf("\nWould u like a copy of this receipt?.\n");
    printf("Please enter 'yes' or 'no'.\n");

    //if user enters yes it will copy of receipt/puts it in separate text file
    if ((getchar()) == ('y')) {
        //function that prints the summary into a seperate text file
        printf("Saving receipt...\n");
        get_receipt(TW_A,TW_O,TW_C);
    }

    //end of code
    printf("Thank you for shopping with us! Have a nice day!");
    return 0;
}

//function that reads the choice input from the user
char get_choice(void)
{
    char ch;
    //displays the choices that the user can pick
    printf("\nPlease choose one of the following options:\n");
    printf("a -\t Enter amount of artichokes in kg.\n");
    printf("b -\t Enter amount of onions in kg.\n");
    printf("c -\t Enter amount of carrots in kg.\n");
    printf("q -\t Proceed to checkout.\n");
    //reads users input
    ch = getchar();
    //ensures that reader inputs the correct letters
    if((ch < 'a' || ch > 'c') && ch != 'q'){
        //flushes the buffer (so that it prints error once)
        while (getchar() != '\n');
        printf("\nPlease input a,b,c or q.\n");
        //re-reads the user input if previous input was incorrect.
        ch = getchar();
    }
    //returns value to back to main
    return ch;
}

//function that reads the weight input from the user
float get_weight()
{
    float weight;

    //checks if the user enters a number, else it will be considered invalid input
    if (scanf("%f", &weight) == 1) {
        //flushing buffer to disallow excess input to be considered later
        while (getchar() != '\n');
        //ensures that reader inputs appropriate weight
        if (weight > 0 && weight < 100) {
            return weight;
        } else {
            printf("Error, please input value above 0 and below 100.\n");
            return 0;
        }
    }
    else
    {
        //flushing buffer to disallow excess input to be considered later
        while (getchar() != '\n');
        printf("Invalid input. Try again.\n");
        return 0;
    }
}

void display(float TW_A, float TW_O, float TW_C)
{
    printf("\n------------- Checkout -------------\n");
    //calculations for the price of each vegetable
    float TP_A = TW_A * P_A;
    float TP_O = TW_O * P_O;
    float TP_C = TW_C * P_C;
    //calculations for total price and total weight
    float total_p = TP_A + TP_O + TP_C;
    float total_w = TW_A + TW_O + TW_C;

    //will only print products that have been bought
    if (TP_A > 0 || TW_A > 0) {
        printf("%.2f kg of Artichokes : $%.2f \n", TW_A, TP_A);
    }
    if (TP_O > 0 || TW_O > 0) {
        printf("%.2f kg of Onions : $%.2f \n", TW_O, TP_O);
    }
    if (TP_C > 0 || TW_C > 0) {
        printf("%.2f kg of Carrots : $%.2f \n", TW_C, TP_C);
    }

    //prints the total of all products before discounts and shipping costs
    printf("Total : $%.2f\n", total_p);
    printf("------------------------------------\n");

    float discount = 0;
    //calculate discount if the price is above 100
    if (total_p > 100.0)
    {
        discount = (total_p * DISC);
        printf("Total with 5%% discount : $%.2f\n", total_p - discount);
    }

    //calculate shipping price according to the price
    int index;
    float ship = 0;
    if(total_w == 0) {
        ship = 0;
    } else if(total_w <= 5.0) {
        ship = 6.5;
    } else if (total_w > 5.0 && total_w < 20.0) {
        ship = 14.0;
    } else if (total_w >= 20) {
        ship = 14.0;
        //function that adds 0.50 per kg for shipments of 20kg more
        for (index = total_w; index >= 20.0; index--) {
            ship += 0.5;
        }
    }

    //prints shipping cost and final overall price.
    printf("Shipping cost : $%.2f\n", ship);
    printf("------------------------------------\n");
    printf("Overall total : $%.2f\n", total_p - discount + ship);
}

void get_receipt(float TW_A, float TW_O, float TW_C)
{
    //opens a file called bill.text where the receipt will be 'printed'
    FILE *f = fopen("bill.txt", "w");
    //if cant open file
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(EXIT_FAILURE);
    }

    fprintf(f,"\n------------- Checkout -------------\n");
    //calculations for the price of each vegetable
    float TP_A = TW_A * P_A;
    float TP_O = TW_O * P_O;
    float TP_C = TW_C * P_C;
    //calculations for total price and total weight
    float total_p = TP_A + TP_O + TP_C;
    float total_w = TW_A + TW_O + TW_C;

    //will only print products that have been bought
    if (TP_A > 0 || TW_A > 0) {
        fprintf(f,"%.2f kg of Artichokes : $%.2f \n", TW_A, TP_A);
    }
    if (TP_O > 0 || TW_O > 0) {
        fprintf(f,"%.2f kg of Onions : $%.2f \n", TW_O, TP_O);
    }
    if (TP_C > 0 || TW_C > 0) {
        fprintf(f,"%.2f kg of Carrots : $%.2f \n", TW_C, TP_C);
    }

    //prints the total of all products before discounts and shipping costs
    fprintf(f,"Total : $%.2f\n", total_p);
    fprintf(f,"------------------------------------\n");

    float discount = 0;
    //calculate discount if the price is above 100
    if (total_p > 100.0)
    {
        discount = (total_p * DISC);
        fprintf(f,"Total with 5%% discount : $%.2f\n", total_p - discount);
    }

    //calculate shipping price according to the price
    int index;
    float ship = 0;
    if(total_w == 0)
    {
        ship = 0;
    } else if(total_w <= 5.0)
    {
        ship = 6.5;
    } else if (total_w > 5.0 && total_w < 20.0) {
        ship = 14.0;
    } else if (total_w >= 20) {
        ship = 14.0;
        //function that adds 0.50 per kg for shipments of 20kg more
        for (index = total_w; index >= 20.0; index--) {
            ship += 0.5;
        }
    }

    //prints shipping cost and final overall price.
    fprintf(f,"Shipping cost : $%.2f\n", ship);
    fprintf(f,"------------------------------------\n");
    fprintf(f,"Overall total : $%.2f\n", total_p - discount + ship);
}




