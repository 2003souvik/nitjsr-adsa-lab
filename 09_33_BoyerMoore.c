#include <stdio.h>
#include <string.h>
#define NO_OF_CHARS 256  // Total number of possible characters (ASCII)

// Function to get the maximum of two integers
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Function to preprocess the pattern and fill the bad character array
void badCharHeuristic(char *pattern, int size, int badchar[NO_OF_CHARS])
{
    int i;

    // Initialize all occurrences as -1
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    // Fill the actual value of the last occurrence of each character in the pattern
    for (i = 0; i < size; i++)
        badchar[(int)pattern[i]] = i;
}

// Boyer–Moore search function (Bad Character Heuristic)
void search(char *text, char *pattern)
{
    int m = strlen(pattern);
    int n = strlen(text);

    int badchar[NO_OF_CHARS];

    // Preprocess the pattern
    badCharHeuristic(pattern, m, badchar);

    int s = 0; // s is the shift of the pattern with respect to text

    while (s <= (n - m))
    {
        int j = m - 1;

        // Keep reducing index j of pattern while characters of pattern and text are matching
        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        // If the pattern is present at current shift, then index j will become -1
        if (j < 0)
        {
            printf("Pattern found at index %d\n", s);

            // Shift the pattern so that next character in text aligns with the last occurrence in pattern
            s += (s + m < n) ? m - badchar[text[s + m]] : 1;
        }
        else
        {
            // Shift the pattern so that the bad character in text aligns with the last occurrence in pattern
            s += max(1, j - badchar[text[s + j]]);
        }
    }
}

// Main function
int main()
{
    char text[100], pattern[50];

    printf("Enter the text: ");
    gets(text);

    printf("Enter the pattern to search: ");
    gets(pattern);

    search(text, pattern);

    return 0;
}
