#include <malloc.h>
#include <string.h>
#include <stdio.h>

void invert_str(char *str) {
    char *start = str;
    char *end = str;
    for (; *end != 0; end++);

    end--;
    while (start < end) {
        char c = *end;
        *end-- = *start;
        *start++ = c;
    }
}

char *read_str() {
    char *str = malloc(512);
    fgets(str, 512, stdin);

    for (char *cur = str; *cur != 0; cur++) {
        if (*cur == '\n') {
            *cur = 0;
            break;
        }
    }

    return str;
}

int main() {
    printf("Please input string: ");
    char *str = read_str();

    printf("Your string        : %s\n", str);
    invert_str(str);
    printf("Inverted string    : %s\n", str);

    free(str);
}
