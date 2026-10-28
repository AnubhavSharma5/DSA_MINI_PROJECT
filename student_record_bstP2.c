#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int id;
    char name[50], department[30];
    struct Node *left, *right;
} Node;

Node *createNode(int id, char name[], char department[]) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) { printf("Memory allocation failed.\n"); exit(1); }
    n->id = id; strcpy(n->name, name); strcpy(n->department, department);
    n->left = n->right = NULL;
    return n;
}

Node *search(Node *root, int id) {
    if (root == NULL || root->id == id) return root;
    if (id < root->id) return search(root->left, id);
    return search(root->right, id);
}

Node *insert(Node *root, int id, char name[], char department[]) {
    if (root == NULL) return createNode(id, name, department);
    if (id < root->id) root->left = insert(root->left, id, name, department);
    else if (id > root->id) root->right = insert(root->right, id, name, department);
    else printf("Duplicate ID not allowed.\n");
    return root;
}

Node *minimum(Node *root) {
    while (root && root->left) root = root->left;
    return root;
}

Node *deleteNode(Node *root, int id) {
    Node *temp;
    if (root == NULL) return NULL;
    if (id < root->id) root->left = deleteNode(root->left, id);
    else if (id > root->id) root->right = deleteNode(root->right, id);
    else {
        if (root->left == NULL) { temp = root->right; free(root); return temp; }
        if (root->right == NULL) { temp = root->left; free(root); return temp; }
        temp = minimum(root->right);
        root->id = temp->id;
        strcpy(root->name, temp->name);
        strcpy(root->department, temp->department);
        root->right = deleteNode(root->right, temp->id);
    }
    return root;
}

void inorder(Node *root) {
    if (!root) return;
    inorder(root->left);
    printf("ID: %d | Name: %s | Department: %s\n", root->id, root->name, root->department);
    inorder(root->right);
}
void preorder(Node *root) { if (root) { printf("%d ", root->id); preorder(root->left); preorder(root->right); } }
void postorder(Node *root) { if (root) { postorder(root->left); postorder(root->right); printf("%d ", root->id); } }
void freeTree(Node *root) { if (root) { freeTree(root->left); freeTree(root->right); free(root); } }

int main(void) {
    Node *root = NULL, *found;
    int choice, id;
    char name[50], department[30];
    do {
        printf("\n===== STUDENT RECORD BST =====\n1. Insert student\n2. Search student by ID\n3. Delete student by ID\n4. Display sorted records (Inorder)\n5. Preorder traversal\n6. Postorder traversal\n7. Insert 10 sample records\n0. Exit\nEnter choice: ");
        if (scanf("%d", &choice) != 1) { printf("Invalid input.\n"); freeTree(root); return 0; }
        if (choice == 1) {
            printf("Enter enrolment ID: "); if (scanf("%d", &id) != 1) break;
            if (search(root, id)) { printf("Duplicate ID not allowed.\n"); continue; }
            printf("Enter student name (one word): "); scanf("%49s", name);
            printf("Enter department (one word): "); scanf("%29s", department);
            root = insert(root, id, name, department); printf("Record inserted.\n");
        } else if (choice == 2) {
            printf("Enter ID to search: "); if (scanf("%d", &id) != 1) break;
            found = search(root, id);
            if (!found) printf("Student not found.\n");
            else printf("ID: %d | Name: %s | Department: %s\n", found->id, found->name, found->department);
        } else if (choice == 3) {
            printf("Enter ID to delete: "); if (scanf("%d", &id) != 1) break;
            if (!search(root, id)) printf("Student not found.\n");
            else { root = deleteNode(root, id); printf("Record deleted.\n"); }
        } else if (choice == 4) {
            if (!root) printf("Tree is empty.\n"); else inorder(root);
        } else if (choice == 5) {
            if (!root) printf("Tree is empty.\n"); else { printf("Preorder IDs: "); preorder(root); printf("\n"); }
        } else if (choice == 6) {
            if (!root) printf("Tree is empty.\n"); else { printf("Postorder IDs: "); postorder(root); printf("\n"); }
        } else if (choice == 7) {
            int ids[] = {50,30,70,20,40,60,80,10,35,65};
            char *names[] = {"Aarav","Diya","Kabir","Meera","Arjun","Isha","Vivaan","Anaya","Reyansh","Saanvi"};
            char *deps[] = {"CSE","ECE","CSE","IT","CSE","ME","ECE","IT","CSE","ME"};
            int i;
            for (i = 0; i < 10; i++) if (!search(root, ids[i])) root = insert(root, ids[i], names[i], deps[i]);
            printf("Sample records loaded; existing IDs were skipped.\n");
        } else if (choice == 0) printf("Program ended.\n");
        else printf("Invalid choice. Try again.\n");
    } while (choice != 0);
    freeTree(root);
    return 0;
}
