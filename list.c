#include <stdio.h>
#include <malloc.h>

struct list_header {
    struct list_header *next;
};

struct list_header *list_init() {
    struct list_header *hdr = malloc(sizeof(struct list_header));
    hdr->next = NULL;
    return hdr;
}

void list_append(struct list_header *list, struct list_header *item) {
    for (; list->next; list = list->next);
    list->next = item;
    item->next = NULL;
}

void list_free(struct list_header *list) {
    for (struct list_header *cur = list; cur;) {
        struct list_header *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}

struct book {
    struct list_header list;

    char *name;
    int year;
    double price;
    int pages;
    char *language;
    double weight;
};

struct book *create_book(char *name, double price, int pages, char *language, double weight, int year) {
    struct book *b = malloc(sizeof(struct book));
    b->name = name;
    b->year = year;
    b->price = price;
    b->pages = pages;
    b->language = language;
    b->weight = weight;
    return b;
}

int main() {
    struct list_header *head = list_init();

    list_append(head, create_book("Harry Potter and the Sorcerer's Stone", 40, 256, "en", 1.7, 1997));
    list_append(head, create_book("Harry Potter and the Chamber of Secrets", 41, 272, "en", 1.7, 1998));
    list_append(head, create_book("Harry Potter and the Prisoner of Azkaban", 42, 336, "en", 2.2, 1999));
    list_append(head, create_book("Harry Potter and the Goblet of Fire", 43, 464, "en", 2.3, 2000));
    list_append(head, create_book("Harry Potter and the Order of the Phoenix", 44, 576, "en", 2.8, 2003));
    list_append(head, create_book("Harry Potter and the Order of the Phoenix", 44, 576, "en", 2.8, 2003));
    list_append(head, create_book("Harry Potter and the Order of the Phoenix", 44, 576, "en", 2.8, 2003));
    list_append(head, create_book("Harry Potter and the Half-Blood Prince", 45, 672, "en", 1.0, 2005));
    list_append(head, create_book("Harry Potter and the Deathly Hallows", 46, 784, "en", 1.0, 2007));

    int i = 0;
    for (struct list_header *cur = head->next; cur; cur = cur->next, i++) {
        struct book *b = cur;

        printf("%d) %s - published in %d, costs %.2f hryvnas, %d pages, language - %s, %.3f kg\n", i, b->name, b->year, b->price,
               b->pages, b->language, b->weight);
    }

    list_free(head);
}
