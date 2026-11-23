#include <stdio.h>

void bubble_sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

int main(void) {
    int a[] = {4, 2};
    int n = sizeof(a) / sizeof(a[0]);

    bubble_sort(a, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
// create a comment
// create a second comment
