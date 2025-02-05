#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_extra_spaces() {
    FILE *in = fopen("input.txt", "r"); // Open the input file for reading
    FILE *out = fopen("output.txt", "w"); // Open the output file for writing

    if (in == NULL || out == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char ch, prev = ' ';
    while ((ch = fgetc(in)) != EOF) {
        // Skip consecutive spaces
        if (ch != ' ' || prev != ' ') {
            fputc(ch, out); // Write the character to the output file
        }
        prev = ch;
    }

    fclose(in);
    fclose(out);
    printf("Extra spaces removed and written to output.txt\n");
}

int main() {
    // Call the function to remove extra spaces from the input file
    remove_extra_spaces();
    return 0;
}

