#include <stdio.h>
#include <string.h>

#define MAX 150000
#define MAX_STRING 100

// Arrays to store the words for numbers.
const char *ONES[] = {
    "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

const char *TEENS[] = {
    "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
    "sixteen", "seventeen", "eighteen", "nineteen"
};

const char *TENS[] = {
    "", "", "twenty", "thirty", "forty", "fifty",
    "sixty", "seventy", "eighty", "ninety "
};

// Function pointer type for the provider function.
typedef void (*provider_function)(int, char*);

// Storing results for numbers we've already seen.
char saved[MAX][MAX_STRING] = {0};

// Cached version of the convert function.
void cached_convert(provider_function provider, int money, char *words) {
    if (money < MAX && saved[money][0] != '\0') {
        strcpy(words, saved[money]);
        return;
    }

    // Calls provider function
    provider(money, words);

    // Cache result
    if (money < MAX) {
        strcpy(saved[money], words);
    }
}

// Converts the integer into words.
void convert(int money, char *words) {
    int dollars = money / 100;
    int cents = money % 100;

    if (dollars >= 1000) {
        strcat(words, ONES[dollars / 1000]);
        strcat(words, " thousand ");
        dollars %= 1000;
    }

    if (dollars >= 100) {
        strcat(words, ONES[dollars / 100]);
        strcat(words, " hundred ");
        dollars %= 100;
    }

    if (dollars >= 20) {
        strcat(words, TENS[dollars / 10]);
        if (dollars % 10 != 0) {
            strcat(words, "-");
            strcat(words, ONES[dollars % 10]);
        }
    } else if (dollars >= 10) {
        strcat(words, TEENS[dollars - 10]);
    } else if (dollars > 0) {
        strcat(words, ONES[dollars]);
    }

    // Append the word dollar(s) to string
    if (dollars == 1) {
        strcat(words, " dollar");
    } else if (dollars > 0) {
        strcat(words, " dollars");
    }

    // Append cents to string.
    if (cents > 0) {
        if (dollars > 0) {
            strcat(words, " and ");
        }
        if (cents >= 20) {
            strcat(words, TENS[cents / 10]);
            if (cents % 10 != 0) {
                strcat(words, "-");
                strcat(words, ONES[cents % 10]);
            }
        } else if (cents >= 10) {
            strcat(words, TEENS[cents - 10]);
        } else {
            strcat(words, ONES[cents]);
        }
        strcat(words, " cents");
    }
}

int main(void) {
    int money; 
    char words[MAX_STRING];

    while (scanf("%d", &money) != EOF) { 
        words[0] = '\0'; // Clear string
        cached_convert(convert, money, words); 
        printf("%d = %s\n", money, words); 
    }
    return 0;
}