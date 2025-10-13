#include <stdio.h>
#include <string.h>
#define d 256  // number of characters in input alphabet

// Rabin-Karp Algorithm for Pattern Searching
void search(char pattern[], char text[], int q)
{
    int M = strlen(pattern);
    int N = strlen(text);
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for text
    int h = 1;

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of pattern and first window of text
    for (i = 0; i < M; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++) {

        // Check hash values of current window of text and pattern
        if (p == t) {
            // Check for characters one by one
            for (j = 0; j < M; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }

            // If p == t and pattern[0...M-1] = text[i...i+M-1]
            if (j == M)
                printf("Pattern found at index %d\n", i);
        }

        // Calculate hash value for next window of text
        if (i < N - M) {
            t = (d * (t - text[i] * h) + text[i + M]) % q;

            // We might get negative value of t, converting it to positive
            if (t < 0)
                t = (t + q);
        }
    }
}

// Main function
int main()
{
    char text[100], pattern[50];
    int q = 101; // A prime number

    printf("Enter the text: ");
    gets(text);

    printf("Enter the pattern to search: ");
    gets(pattern);

    search(pattern, text, q);
    return 0;
}
