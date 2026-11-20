#include <stdio.h>

char* zip(char in[], char out[]) {
    int i = 0, j = 0;
    while (in[i] != '\0') {
        char ch = in[i];
        int count = 0;
        while (in[i] == ch) {
            count++;
            i++;
        }
        out[j++] = ch;

        char temp[20];
        int t = 0;
        while (count > 0) {
            temp[t++] = (count % 10) + '0';
            count /= 10;
        }
        while (t > 0) {
            out[j++] = temp[--t];
        }
    }
    out[j] = '\0';
    return out;
}

char* unzip(char in[], char out[]) {
    int i = 0, j = 0;
    while (in[i] != '\0') {
        char ch = in[i++];
        int count = 0;
        while (in[i] >= '0' && in[i] <= '9') {
            count = count * 10 + (in[i] - '0');
            i++;
        }
        for (int k = 0; k < count; k++) {
            out[j++] = ch;
        }
    }
    out[j] = '\0';
    return out;
}

int compare(char s1[], char s2[]) {
    int i = 0;
    while (s1[i] == s2[i] && s1[i] != '\0') {
        i++;
    }
    return s1[i] - s2[i];
}

int main() {
    char s[1000];
    printf("введите строку");
    scanf("%999s", s);

    char compressed[2000];
    char decompressed[2000];

    printf("сжатая:   %s\n", zip(s, compressed));
    printf("расжатая: %s\n", unzip(compressed, decompressed));

    if (compare(s, decompressed) == 0) {
        printf("сходятся!\n");
    } else {
        printf("не сходятся(((\n");
    }
    return 0;
}