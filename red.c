#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

int dimension = 10;

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
        root = createNode(string, true);
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
    stack[ht - 1]->link[index] = newnode = createNode(string, true);
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


void inorderTraversal(struct rbNode *node) {
    if (node) {
        inorderTraversal(node->link[0]);
        printf("%s  ", node->string);
        inorderTraversal(node->link[1]);
    }
}

int main() {
    struct rbNode *root = NULL;
    root = insertion(root, "aaaa", true);
    root = insertion(root, "bbb", true);
    root = insertion(root, "0", true);
    root = insertion(root, "3", true);
    root = insertion(root, "dsa", true);
    inorderTraversal(root);
    return 0;
}