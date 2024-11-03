#include <stdio.h>

void prefix_scan(int *input, int *output, int n) {
    output[0] = input[0];  // Initialize the first element

    // Compute prefix sum
    for (int i = 1; i < n; i++) {
        output[i] = output[i - 1] + input[i];
    }
}

int main() {
    int n = 10;
    int input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int output[n];

    prefix_scan(input, output, n);

    // Print the results
    printf("Prefix Sum: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", output[i]);
    }
    printf("\n");

    return 0;
}
