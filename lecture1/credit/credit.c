#include<stdio.h>
#include<cs50.h>
#include<string.h>
#define or ||
#define and &&
#define not !
int reversed_digits_list(long input, int *reversed_list, int amount_digits)
{
    for (int i = 0; i < amount_digits; i++)
    {
        reversed_list[i] = input % 10;
        input /= 10;
    }
    return 0;
}

int make_digits_normal(int reversed_list[], int *normal_digits, int amount_digits)
{
    int j = 0;
    for (int i = amount_digits - 1; i >= 0; i--, j++)
    {
        normal_digits[j] = reversed_list[i];
    }
    return 0;
}


bool solve(int reversed_list[], int num_digits)
{
    int sum = 0;
    for (int i = 1; i < num_digits; i+= 2)
    {
        sum += (reversed_list[i] * 2) % 10;
        if (reversed_list[i] * 2 >= 10)
        {
            sum++;
        }
    }
    for (int i = 0; i < num_digits; i += 2)
    {
        sum += reversed_list[i];
    }
    if (sum % 10 != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int main(void)
{
    long input = get_long("Number: ");


    int digits = 0;
    long copy_input = input;
    for (int i = 0; copy_input >= 1; i++, copy_input /= 10, digits++);
    int reversed_digits[digits];
    reversed_digits_list(input, reversed_digits, digits);
    int buffer_list[digits];
    make_digits_normal(reversed_digits, buffer_list, digits);
    bool is_valid = solve(reversed_digits, digits);
    bool output = false;
    if (is_valid)
    {
        if (digits == 16)
        {
            if (buffer_list[0] == 4)
            {
                output = true;
                printf("VISA\n");
            }
            if (buffer_list[0] == 5)
            {
                if (buffer_list[1] == 1 or buffer_list[1] == 2 or buffer_list[1] == 3 or buffer_list[1] == 4 or buffer_list[1] == 5)
                {
                    output = true;
                    printf("MASTERCARD\n");
                }
            }
        }

        if (digits == 13)
        {
            if (buffer_list[0] == 4)
            {
                output = true;
                printf("VISA\n");
            }
        }

        if (digits == 15)
        {
            if (buffer_list[0] == 3)
            {
                if (buffer_list[1] == 4 or buffer_list[1] == 7)
                {
                    output = true;
                    printf("AMEX\n");
                }
            }
        }
    }

    if (not output)
    {
        printf("INVALID\n");
    }

}


/*

#include<stdio.h>
#include<cs50.h>
#define or ||
#define and &&
#define not !
int digits_list(long input, int *digits, int amount_digits) {
    int reversed_list[amount_digits];
    for (int i = 0; i < amount_digits; i++) {
        reversed_list[i] = input % 10;
        input /= 10;
    }
    int j = 0;
    for (int i = amount_digits - 1; i >= 0; i--, j++) {
        digits[j] = reversed_list[i];
    }
    return 0;
}


int correctly_order_digits(int digits_list[], int amount_digits, int *correct_digits) {
    correct_digits[0] = digits_list[amount_digits - 2];
    correct_digits[1] = digits_list[amount_digits - 1];
    for (int i = 0, j = 2; i < amount_digits - 2; i++, j++) {
        correct_digits[j] = digits_list[i];
    }
    return 0;
}


bool check_valid(int correct_digits[], int amount_digits) {
    int sum = 0;
    for (int i = 0; i < amount_digits; i+= 2) {
        sum += (correct_digits[i] * 2) % 10;
        if (correct_digits[i] * 2 >= 10) {
            sum ++;
        }
    }
    for (int i = amount_digits - 1; i >= 0; i -= 2) {
        sum += correct_digits[i];
    }
    if (sum % 10 != 0) {
        return false;
    } else {
        return true;
    }
}



int main(void) {
    long input = get_long("Number: ");


    int digits = 0;
    long copy_input = input;
    for (int i = 0; copy_input >= 1; i++, copy_input /= 10, digits++);
    int buffer_list[digits];
    digits_list(input, buffer_list, digits);
    int correct_digits[digits];
    correctly_order_digits(buffer_list, digits, correct_digits);
    bool is_valid = check_valid(correct_digits, digits);
    bool output = false;
    if (is_valid) {
        if (digits == 16) {
            if (buffer_list[0] == 4) {
                output = true;
                printf("VISA\n");
            }
            if (buffer_list[0] == 5) {
                if (buffer_list[1] == 1 or buffer_list[1] == 2 or buffer_list[1] == 3 or buffer_list[1] == 4 or buffer_list[1] == 5) {
                    output = true;
                    printf("MASTERCARD\n");
                }
            }
        }

        if (digits == 13) {
            if (buffer_list[0] == 4) {
                output = true;
                printf("VISA\n");
            }
        }

        if (digits == 15) {
            if (buffer_list[0] == 3) {
                if (buffer_list[1] == 4 or buffer_list[1] == 7) {
                    output = true;
                    printf("AMEX\n");
                }
            }
        }
    }

    if (not output) {
        printf("INVALID\n");
    }

}
*/