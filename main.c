#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define DIM 30
#define DIM_CHAR_COUNTER 300

enum nodeColor {
    RED,
    BLACK
};

struct rbNode {
    int color;
    char *string;
    bool active;
    struct rbNode *link[2];
};

struct char_node {
    char c;
    int pos;
    struct char_node *next;
};

int dimension;
struct char_node *char_list = NULL;
char *filter_word;

void char_node_insert (char c, int pos){
    struct char_node *new = malloc(sizeof(struct char_node));
    new->c = c;
    new->pos = pos;
    new->next = char_list;
    char_list = new;
};

bool search_char_list(char c){
    struct char_node *cur = char_list;
    while (cur != NULL){
        if (cur->c == c && cur->pos == -1)
            return true;
        cur = cur->next;
    }
    return false;
}

void my_strcpy(char *a, const char *b) {
    for (int i = 0; i < dimension; ++i) {
        a[i] = b[i];
    }
    a[dimension] = '*';
}


int my_strcmp(const char *a, const char *b) {
    for (int i = 0; i < dimension; ++i) {
        if (a[i] > b[i])
            return 1;
        if (a[i] < b[i])
            return -1;
    }
    return 0;
}


struct rbNode *filter(struct rbNode *node) {
    if (node->active == true) {
        node->active = false;
    }
    return node;
}


struct rbNode *createNode(char *string, bool active) {
    struct rbNode *newnode;
    newnode = (struct rbNode *) malloc(sizeof(struct rbNode));
    newnode->string = (char *) malloc(dimension * sizeof(char));
    my_strcpy(newnode->string, string);
    newnode->color = RED;
    newnode->active = active;
    newnode->link[0] = newnode->link[1] = NULL;
    return newnode;
}


struct rbNode *insertion(struct rbNode *root, char *string, bool active) {
    struct rbNode *stack[98], *ptr, *newnode, *xPtr, *yPtr;
    int dir[98], ht = 0, index;
    ptr = root;
    if (!root) {
        root = createNode(string, active);
        return root;
    }
    stack[ht] = root;
    dir[ht++] = 0;
    while (ptr != NULL) {
        if (my_strcmp(ptr->string, string) == 0) {
            printf("Duplicates Not Allowed!!\n");
            return root;
        }
        if (my_strcmp(string, ptr->string) > 0)
            index = 1;
        else
            index = 0;
        stack[ht] = ptr;
        ptr = ptr->link[index];
        dir[ht++] = index;
    }
    newnode = createNode(string, active);
    stack[ht - 1]->link[index] = newnode;
    while ((ht >= 3) && (stack[ht - 1]->color == RED)) {
        if (dir[ht - 2] == 0) {
            yPtr = stack[ht - 2]->link[1];
            if (yPtr != NULL && yPtr->color == RED) {
                stack[ht - 2]->color = RED;
                stack[ht - 1]->color = yPtr->color = BLACK;
                ht = ht - 2;
            } else {
                if (dir[ht - 1] == 0) {
                    yPtr = stack[ht - 1];
                } else {
                    xPtr = stack[ht - 1];
                    yPtr = xPtr->link[1];
                    xPtr->link[1] = yPtr->link[0];
                    yPtr->link[0] = xPtr;
                    stack[ht - 2]->link[0] = yPtr;
                }
                xPtr = stack[ht - 2];
                xPtr->color = RED;
                yPtr->color = BLACK;
                xPtr->link[0] = yPtr->link[1];
                yPtr->link[1] = xPtr;
                if (xPtr == root) {
                    root = yPtr;
                } else {
                    stack[ht - 3]->link[dir[ht - 3]] = yPtr;
                }
                break;
            }
        } else {
            yPtr = stack[ht - 2]->link[0];
            if ((yPtr != NULL) && (yPtr->color == RED)) {
                stack[ht - 2]->color = RED;
                stack[ht - 1]->color = yPtr->color = BLACK;
                ht = ht - 2;
            } else {
                if (dir[ht - 1] == 1) {
                    yPtr = stack[ht - 1];
                } else {
                    xPtr = stack[ht - 1];
                    yPtr = xPtr->link[0];
                    xPtr->link[0] = yPtr->link[1];
                    yPtr->link[1] = xPtr;
                    stack[ht - 2]->link[1] = yPtr;
                }
                xPtr = stack[ht - 2];
                yPtr->color = BLACK;
                xPtr->color = RED;
                xPtr->link[1] = yPtr->link[0];
                yPtr->link[0] = xPtr;
                if (xPtr == root) {
                    root = yPtr;
                } else {
                    stack[ht - 3]->link[dir[ht - 3]] = yPtr;
                }
                break;
            }
        }
    }
    root->color = BLACK;
    return root;
}


void print_string(char *a) {
    for (int i = 0; i < dimension; ++i) {
        printf("%c", a[i]);
    }
}


bool search_char(char x, const char ref[DIM]) {
    for (int i = 0; i < dimension; ++i) {
        if (ref[i] == x)
            return true;
    }
    return false;
}


bool search(struct rbNode *l, char s[DIM]) {
    if (l) {
        if (my_strcmp(s, l->string) == 0)
            return true;
        if (my_strcmp(s, l->string) > 0)
            return search(l->link[1], s);
        if (my_strcmp(s, l->string) < 0)
            return search(l->link[0], s);
    }
    return false;
}

bool complex_search_char(int pos, const char p[DIM], const char r[DIM]) {
    int N = 0, C = 0, K = 0;
    for (int i = 0; i < dimension; ++i) {
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
        return true;
    return false;
}

void print_active(struct rbNode *l) {
    if (l) {
        if (my_strcmp(l->string, "AAbmN") == 0)
            printf("");
        print_active(l->link[0]);
        if (l->active == true) {
            print_string(l->string);
            printf("\n");
        }
        print_active(l->link[1]);
    }
}

void print_tree(struct rbNode *l) {
    if (l) {
        print_tree(l->link[0]);
        printf("%s, %d\n", l->string, l->active);
        print_tree(l->link[1]);
    }
}

int count_active_number(struct rbNode *l) {
    if (l) {
        if (l->active == true)
            return 1 + count_active_number(l->link[0]) +
                   count_active_number(l->link[1]);
        else
            return count_active_number(l->link[0]) +
                   count_active_number(l->link[1]);
    }
    return 0;
}


char *read_string(char *s) {
    return fgets(s, DIM, stdin);
}


int count_char(char c, const char ref[DIM]) {
    int n = 0;
    for (int i = 0; i < dimension; ++i) {
        if (ref[i] == c)
            n++;
    }
    return n;
}

struct rbNode *delete_words_with_this_char(struct rbNode *l, char wrong_char) {
    if (l) {
        if (l->active)
            if (count_char(wrong_char, l->string) > 0)
                l = filter(l);
        l->link[0] = delete_words_with_this_char(l->link[0], wrong_char);
        l->link[1] = delete_words_with_this_char(l->link[1], wrong_char);
    }
    return l;
}

struct rbNode *delete_words_without_this_char_here(struct rbNode *l, char right_char, int pos) {
    if (l) {
        if (l->active)
            if (l->string[pos] != right_char)
                l = filter(l);
        l->link[0] = delete_words_without_this_char_here(l->link[0], right_char, pos);
        l->link[1] = delete_words_without_this_char_here(l->link[1], right_char, pos);
    }
    return l;
}

struct rbNode *print_result(struct rbNode *l, char *new_word, char *ref) {
    printf("inserted word = ");
    print_string(new_word);
    printf(": \t");
    for (int i = 0; i < dimension; ++i) {
        if (new_word[i] == '\0' || new_word[i] == '\n') {
            break;
        } else if (new_word[i] == ref[i]) {
            printf("+");
            l = delete_words_without_this_char_here(l, new_word[i], i);
        } else if (search_char(new_word[i], ref) == false) {
            printf("/");
            l = delete_words_with_this_char(l, new_word[i]);
            char_node_insert(new_word[i], -1);
        } else if (complex_search_char(i, new_word, ref) == true) {
            printf("/");
        } else {
            printf("|");
            char_node_insert(new_word[i], -2);
        }
    }
    printf("\n%d", count_active_number(l));
    return l;
}

void word_not_found() {
    printf("not_exists");
}


bool to_filter(char *s){
    for (int i = 0; i < dimension; ++i) {
        if (search_char_list(s[i]) == true)
            return true;
    }
    return false;
}


struct rbNode *insert_new_words(struct rbNode *l) {
    char str_in[DIM];
    read_string(str_in);
    while (str_in[0] != '+' && str_in[1] != 'i') {
        l = insertion(l, str_in, !to_filter(str_in));
        read_string(str_in);
    }
    return l;
}

void free_s(struct rbNode *l) {
    if (l) {
        free_s(l->link[0]);
        free_s(l->link[1]);
        free(l->string);
        free(l);
    }
}

int p_atoi(const char *s) {
    int result = 0;
    for (int i = 0; s[i] != '\0' && s[i] != '\n'; i++) {
        result = result * 10 + (s[i] - '0');
    }
    return result;
}

struct rbNode *reset(struct rbNode *l) {
    if (l != NULL) {
        reset(l->link[0]);
        l->active = true;
        reset(l->link[1]);
    }
    return l;
}


struct rbNode *nuova_partita(struct rbNode *l) {

    l = reset(l);

    char ref[DIM];
    read_string(ref);
    printf("\nnew match with ref = %s\n", ref);
    char str_in[DIM];
    read_string(str_in);
    int max_words = p_atoi(str_in);
    while (read_string(str_in) != NULL) {
        if (str_in[0] == '+' && str_in[1] == 'n') {
            l = nuova_partita(l);
            return l;
        }
        if (str_in[0] == '+' && str_in[1] == 'i') {
            l = insert_new_words(l);
        } else if (str_in[0] == '+' && str_in[1] == 's') {
            print_active(l);
        } else {
            if (my_strcmp(str_in, ref) == 0) {
                printf("ok\n");
                return l;
            } else if (search(l, str_in) == true) {
                max_words--;
                l = print_result(l, str_in, ref);
                printf("\n");
            } else {
                word_not_found();
                printf("\n");
            }
            if (max_words == 0) {
                printf("ko\n");
                return l;
            }
        }
    }
    return l;
}


int main() {
    struct rbNode *l = NULL;
    char str_in[DIM];
    read_string(str_in);
    dimension = p_atoi(str_in);
    while (read_string(str_in) != NULL) {
        if (str_in[0] == '+')
            break;
        l = insertion(l, str_in, true);
    }
    l = nuova_partita(l);
    while (read_string(str_in) != NULL) {
        if (str_in[0] == '+') {
            if (str_in[1] == 'n') {
                l = nuova_partita(l);
            } else if (str_in[1] == 'i')
                l = insert_new_words(l);
            else if (str_in[1] == 's')
                print_active(l);
        }
    }
    free_s(l);
    return 0;
}