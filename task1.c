#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SZ 512

struct seq_item {
    char name[MAX_SZ];
    struct seq_item *next;
};

struct seq_header {
    char obj[MAX_SZ];
    struct seq_item *items;
};

void free_seq(struct seq_header *seq) {
    for (struct seq_item *item = seq->items; item;) {
        struct seq_item *tmp = item;
        item = item->next;
        free(tmp);
    }
}

char *readline() {
    char *line = malloc(MAX_SZ);
    char *cur = line;

    while (1) {
        char c = getchar();
        if (c == EOF) exit(0);
        if (c == '\n') break;
        if (cur >= line + MAX_SZ - 1) {
            printf("line too long\n");
            exit(1);
        }

        *cur++ = c;
    }
    *cur = 0;

    return line;
}

int read_category(struct seq_header *seq, char **line) {
    char *cur = seq->obj;
    *cur = 0;

    int res;
    while (1) {
        char c = *(*line)++;
        if (c == 0) {
            return 2;
        }
        if (c == ' ') {
            res = -1;
            break;
        }
        if (c == ':') {
            res = 1;
            break;
        }

        *cur++ = c;
    }

    *cur = 0;
    return res;
}

int read_item(struct seq_header *seq, char **line) {
    struct seq_item *item = seq->items;
    for (; item->next; item = item->next);

    item = item->next = malloc(sizeof(struct seq_item));
    memset(item, 0, sizeof(struct seq_item));

    char *cur = item->name;
    int res;

    while (1) {
        char c = *(*line)++;
        if (c == 0) {
            printf("unexpected end of input");
            exit(1);
        }
        if (c == ',') {
            res = -1;
            break;
        }
        if (c == ';') {
            res = 1;
            break;
        };

        *cur++ = c;
    }

    *cur = 0;

    if (*item->name != ' ') {
        printf("item '%s' must begin with whitespace\n", item->name);
        exit(1);
    }

    return res;
}

void write(char **line, char *str) {
    for (char c = *str; c != 0; c = *++str) {
        *(*line)++ = c;
    }
}

void strcpy1(char *dst, char *src) {
    for (char c = *src; c != 0; c = *++src)
        *dst++ = c;
    *dst = 0;
}

int strcmp1(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }

    return *str1 - *str2;
}

void swap(struct seq_item *a, struct seq_item *b) {
    char temp[MAX_SZ];
    strcpy1(temp, a->name);
    strcpy1(a->name, b->name);
    strcpy1(b->name, temp);
};

void bubbleSort(struct seq_item *start) {
    int swapped;
    struct seq_item *ptr1;
    struct seq_item *lptr = NULL;

    if (start == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr) {
            if (strcmp1(ptr1->name, ptr1->next->name) > 0) {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

int read_seq(char **line, char **line_out_cur) {
    struct seq_header seq = {0};
    seq.items = malloc(sizeof(struct seq_item));
    memset(seq.items, 0, sizeof(struct seq_item));

    int res;
    while ((res = read_category(&seq, line)) != 1) {
//        printf("read category %d\n", res);

        write(line_out_cur, seq.obj);
        if (res == 2) {
            free_seq(&seq);
            return 1;
        }
        write(line_out_cur, " ");
    }

//    printf("category: %s\n", seq.obj);
    write(line_out_cur, seq.obj);
    write(line_out_cur, ":");

    while ((res = read_item(&seq, line)) != 1) {
//        printf("read item %d\n", res);
    }

    bubbleSort(seq.items->next);

    for (struct seq_item *item = seq.items->next; item != NULL; item = item->next) {
//        printf("item name: %s\n", item->name);
        write(line_out_cur, item->name);
        write(line_out_cur, ",");
    }
    *(*line_out_cur - 1) = ';';

    free_seq(&seq);

    return -1;
}

void process_line() {
    char *line = readline();
    char *line_cur = line;

    char line_out[MAX_SZ];
    char *line_out_cur = line_out;

    while (read_seq(&line_cur, &line_out_cur) != 1);

    free(line);

    *line_out_cur = 0;
    printf("%s\n", line_out);
}

int main() {
    process_line();
}
