#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DIM 30

struct node {
    char string[DIM];
    bool active;
    struct node *next;
};

int dimension;

void my_strcpy(char a[DIM], char b[DIM]) {
    for (int i = 0; i < dimension; ++i) {
        a[i] = b[i];
    }
}

int my_strcmp(char a[DIM], char b[DIM]) {
    for (int i = 0; i < dimension; ++i) {
        if (a[i] > b[i])
            return 1;
        if (a[i] < b[i])
            return -1;
    }
    return 0;
}

void print_string(char a[DIM]) {
    for (int i = 0; i < dimension; ++i) {
        printf("%c", a[i]);
    }
}

void swap(struct node *a, struct node *b) {
    char tempString[DIM];
    bool tempActive;
    my_strcpy(tempString, a->string);
    tempActive = a->active;
    my_strcpy(a->string, b->string);
    a->active = b->active;
    my_strcpy(b->string, tempString);
    b->active = tempActive;
}

void sort_list(struct node *l) {
    int swapped;
    struct node *node1;
    struct node *node2 = NULL;
    if (l == NULL)
        return;
    do {
        swapped = 0;
        node1 = l;
        while (node1->next != node2) {
            if (my_strcmp(node1->string, node1->next->string) > 0) {
                swap(node1, node1->next);
                swapped = 1;
            }
            node1 = node1->next;
        }
        node2 = node1;
    } while (swapped);
}


int search_char(char x, const char ref[DIM]) {
    for (int i = 0; i < DIM; ++i) {
        if (ref[i] == x)
            return 1;
    }
    return 0;
}

void delete_words_with_this_char(struct node *l, char c) { //the char does not belong to the string
    struct node *cur = l;
    while (cur != NULL) {
        if (cur->active == true)
            if (search_char(c, cur->string) == 1) {
                cur->active = false;
            }
        cur = cur->next;
    }
}


int count_char(char c, const char ref[DIM]) {
    int n = 0;
    for (int i = 0; i < DIM; ++i) {
        if (ref[i] == c)
            n++;
    }
    return n;
}


void print_list(struct node *l) {
    struct node *cur = l;
    printf("\nPRINT LIST\n");
    while (cur != NULL) {
        if (cur->active == true) {
            printf(" active = %d", cur->active);
            print_string(cur->string);
        }
        cur = cur->next;
    }
    printf("\nEND PRINT LIST\n");
}

struct node *list_insert(struct node *l, char s[DIM]) {
    struct node *new = (struct node *) malloc(sizeof(struct node));
    for (int i = 0; i < DIM; ++i) {
        new->string[i] = '*';
    }
    my_strcpy(new->string, s);
    new->active = true;
    new->next = l;
    return new;
}

int list_search(struct node *l, char s[DIM]) {
    struct node *cur = l;
    while (cur != NULL) {
        if (my_strcmp(s, cur->string) == 0) {
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}

int complex_search_char(int pos, const char p[DIM], const char r[DIM]) {
    int N = 0, C = 0, K = 0;
    for (int i = 0; i < DIM; ++i) {
        if (r[i] == p[pos])
            N++;
        if (p[pos] == p[i])
            if (p[i] == r[i])
                C++;
        if (i < pos)
            if (p[pos] == p[i])
                if (p[i] != r[i])
                    K++;
    }
    if (K >= N - C)
        return 1;
    return 0;
}

void print_active(struct node *l) {
    struct node *cur = l;
    while (cur != NULL) {
        if (cur->active == true) {
            print_string(cur->string);
            printf("\n");
        }
        cur = cur->next;
    }
}

void print_active_number(struct node *l) {
    int n = 0;
    struct node *cur = l;
    while (cur != NULL) {
        if (cur->active == true)
            n++;
        cur = cur->next;
    }
    printf("\n%d", n);
}

void all_words_must_have_this_char_here(struct node *l, char c, int pos) {
    struct node *cur = l;
    while (cur != NULL) {
        if (cur->active == true)
            if (cur->string[pos] != c)

                cur->active = false;
        cur = cur->next;
    }
}

char *read_string(char *s) {
    return fgets(s, DIM - 1, stdin);
}

void all_words_must_have_this_char_but_not_here(struct node *l, char c, int pos) {
    struct node *cur = l;
    while (cur != NULL) {
        if (cur->active == true) {
            if (cur->string[pos] == c || search_char(c, cur->string) == 0)
                cur->active = false;
        }
        cur = cur->next;
    }
}

void compare_char(struct node *l, char ref[DIM], char c) {
    int n = count_char(c, ref);
    struct node *cur = l;
    while (cur != NULL) {
        if (cur->active == true) {
            if (count_char(c, cur->string) != n)
                cur->active = false;
        }
        cur = cur->next;
    }
}


void print_result(struct node *l, char new_word[DIM], char ref[DIM]) {
    for (int i = 0; i < DIM; ++i) {
        if (new_word[i] == '\0' || new_word[i] == '\n') {
            break;
        } else if (new_word[i] == ref[i]) {
            printf("+");
            //all_words_must_have_this_char_here(new_word[i], i);
        } else if (search_char(new_word[i], ref) == 0) {
            printf("/");
            //delete_words_with_this_char(new_word[i]);
        } else if (complex_search_char(i, new_word, ref) == 1) {
            //all_words_must_have_this_char_but_not_here(new_word[i], i);
            printf("/");
        } else {
            printf("|");
        }
        compare_char(l, ref, new_word[i]);
    }
    print_active_number(l);
}

void word_not_found() {
    printf("not_exists");
}

struct node *insert_new_words(struct node *l) {
    char str_in[DIM];
    read_string(str_in);
    while (str_in[0] != '+' || str_in[1] != 'i') {
        l = list_insert(l, str_in);
        read_string(str_in);
    }
    //sort_list(l);
    return l;
}


int p_atoi(const char *s) {
    int result = 0;
    for (int i = 0; s[i] != '\0' && s[i] != '\n'; i++) {
        result = result * 10 + (s[i] - '0');
    }
    return result;
}

struct node *list_reset(struct node *l) {
    struct node *cur = l;
    while (cur != NULL) {
        cur->active = true;
        cur = cur->next;
    }
    return l;
}


struct node *nuova_partita(struct node *l) {
    l = list_reset(l);
    char ref[DIM];
    read_string(ref);
    char str_in[DIM];
    read_string(str_in);
    int max_words = p_atoi(str_in);
    while (read_string(str_in) != NULL) {
        if (max_words == 0) {
            printf("ko\n");
            return l;
        } else if (str_in[0] == '+' && str_in[1] == 'i') {
            l = insert_new_words(l);
        } else if (str_in[0] == '+' && str_in[1] == 's') {
            print_active(l);
        } else {
            max_words--;
            if (my_strcmp(str_in, ref) == 0) {
                printf("ok\n");
                return l;
            } else if (list_search(l, str_in) == 1) {
                print_result(l, str_in, ref);
                printf("\n");
            } else {
                word_not_found();
                printf("\n");
            }
        }
    }
    return l;
}


int main() {
    struct node *l = NULL;
    char str_in[DIM];
    read_string(str_in);
    dimension = p_atoi(str_in);
    while (read_string(str_in) != NULL) {
        if (str_in[0] == '+')
            break;
        l = list_insert(l, str_in);
    }

    l = nuova_partita(l);
    while (read_string(str_in) != NULL) {
        if (str_in[0] == '+') {
            if (str_in[1] == 'n')
                l = nuova_partita(l);
            else if (str_in[1] == 'i')
                l = insert_new_words(l);
            else if (str_in[1] == 's')
                print_active(l);
        }
    }
    return 0;
}