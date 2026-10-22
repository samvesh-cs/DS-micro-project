#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

struct Node {
    int medicineID;
    char name[50];
    float price;
    int quantity;
    struct Node *left;
    struct Node *right;
};

// reads one complete line
// returns 1 for success, 0 for end of input, -1 for input that is too long
int readLine(char text[], int size) {
    size_t len;
    int ch;

    if (fgets(text, size, stdin) == NULL) {
        return 0;
    }

    len = strlen(text);

    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
        return 1;
    }

    // Check whether the line exactly filled the buffer
    // or contains extra characters
    ch = getchar();

    if (ch == '\n' || ch == EOF) {
        return 1;
    }

    while (ch != '\n' && ch != EOF) {
        ch = getchar();
    }

    return -1;
}

// reads an integer safely
int readInt(const char prompt[], int *value) {
    char input[100];
    char *end;
    long number;
    int status;

    printf("%s", prompt);
    status = readLine(input, sizeof(input));

    if (status == 0) {
        return 0;
    }

    if (status == -1) {
        printf("Input is too long.\n");
        return -1;
    }

    errno = 0;
    number = strtol(input, &end, 10);

    while (isspace((unsigned char)*end)) {
        end++;
    }

    if (input[0] == '\0' || end == input || *end != '\0' ||
        errno == ERANGE || number < INT_MIN || number > INT_MAX) {
        printf("Invalid input. Please enter a whole number.\n");
        return -1;
    }

    *value = (int)number;
    return 1;
}

// reads a valid, finite, non-negative price
int readPrice(float *price) {
    char input[100];
    char *end;
    float number;
    int status;

    printf("Enter Price: ");
    status = readLine(input, sizeof(input));

    if (status == 0) {
        return 0;
    }

    if (status == -1) {
        printf("Price input is too long.\n");
        return -1;
    }

    errno = 0;
    number = strtof(input, &end);

    while (isspace((unsigned char)*end)) {
        end++;
    }

    if (input[0] == '\0' || end == input || *end != '\0' ||
        errno == ERANGE || !isfinite(number) || number < 0.0f) {
        printf("Invalid price. Enter a finite, non-negative number.\n");
        return -1;
    }

    *price = number;
    return 1;
}

// validates medicine name: letters only, no spaces or numbers
int isValidName(char name[]) {
    int i;

    if (name[0] == '\0') {
        return 0;
    }

    for (i = 0; name[i] != '\0'; i++) {
        if (!isalpha((unsigned char)name[i])) {
            return 0;
        }
    }

    return 1;
}

// reads and validates the complete medicine name
int readMedicineName(char name[], int size) {
    int status;

    printf("Enter Medicine Name (letters only, no spaces): ");
    status = readLine(name, size);

    if (status == 0) {
        return 0;
    }

    if (status == -1) {
        printf("Invalid name. The name is too long.\n");
        return -1;
    }

    if (!isValidName(name)) {
        printf("Invalid name! Use letters only, with no spaces, numbers, or special characters.\n");
        return -1;
    }

    return 1;
}

// creates a new medicine node and returns it
struct Node* createNode(int medicineID, char name[], float price, int quantity) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed. Medicine was not added.\n");
        return NULL;
    }
    newNode->medicineID = medicineID;
    strcpy(newNode->name, name);
    newNode->price = price;
    newNode->quantity = quantity;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// inserts a medicine and updates isInserted
struct Node* insert(struct Node *root, int medicineID, char name[],float price, int quantity, int *isInserted) {
    if (root == NULL) {
        struct Node *newNode = createNode(medicineID, name, price, quantity);

        if (newNode != NULL) {
            *isInserted = 1;
        }
        return newNode;
    }

    if (medicineID < root->medicineID) {
        root->left = insert(root->left, medicineID, name,price, quantity, isInserted);
    }
    else if (medicineID > root->medicineID) {
        root->right = insert(root->right, medicineID, name,price, quantity, isInserted);
    }
    else {
        *isInserted = 0;
        printf("Duplicate Medicine ID. Medicine was not added.\n");
    }

    return root;
}

// searches for a medicine by ID
struct Node* search(struct Node *root, int medicineID) {
    if (root == NULL || root->medicineID == medicineID) {
        return root;
    }

    if (medicineID < root->medicineID) {
        return search(root->left, medicineID);
    }
    return search(root->right, medicineID);
}

// displays the table heading and top border
void displayHeader(void) {
    printf("\n");
    printf("| Medicine ID| Medicine Name        | Price (Rs.)| Quantity   |\n");
    printf("---------------------------------------------------------------\n");
}

// displays one medicine record
void displayMedicine(struct Node *root) {
    if (root == NULL) {
        return;
    }

    printf("| %-10d | %-20.20s | %10.2f | %10d |\n",root->medicineID, root->name, root->price, root->quantity);
}


// updates quantity of an existing medicine
void updateQuantity(struct Node *root, int medicineID, int newQuantity) {
    struct Node *temp = search(root, medicineID);

    if (temp == NULL) {
        printf("Medicine not found. Quantity was not updated.\n");
        return;
    }

    if (newQuantity < 0) {
        printf("Quantity cannot be negative.\n");
        return;
    }

    temp->quantity = newQuantity;
    printf("Quantity updated successfully.\n");
}

// displays medicines in sorted ID order
void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        displayMedicine(root);
        inorder(root->right);
    }
}

// displays medicines below the selected stock threshold
void lowStockAlert(struct Node *root, int threshold, int *found) {
    if (root != NULL) {
        lowStockAlert(root->left, threshold, found);

        if (root->quantity < threshold) {
            if (*found == 0) {
                printf("\nMedicines with low stock (quantity below %d):\n",
                       threshold);
                displayHeader();
            }

            displayMedicine(root);
            *found = 1;
        }

        lowStockAlert(root->right, threshold, found);
    }
}

// calculates the total value of all medicines
double totalInventoryValue(struct Node *root) {
    if (root == NULL) {
        return 0.0;
    }

    return ((double)root->price * root->quantity) + totalInventoryValue(root->left) + totalInventoryValue(root->right);
}

// adds the eight sample medicines
struct Node* loadSampleData(struct Node *root) {
    int isInserted;

    isInserted = 0;
    root = insert(root, 104, "Paracetamol", 25.00f, 100, &isInserted);
    isInserted = 0;
    root = insert(root, 101, "Cetirizine", 18.00f, 60, &isInserted);
    isInserted = 0;
    root = insert(root, 108, "ORS", 22.00f, 45, &isInserted);
    isInserted = 0;
    root = insert(root, 103, "Antacid", 35.00f, 30, &isInserted);
    isInserted = 0;
    root = insert(root, 106, "VitaminC", 40.00f, 25, &isInserted);
    isInserted = 0;
    root = insert(root, 102, "AntisepticCream", 55.00f, 20, &isInserted);
    isInserted = 0;
    root = insert(root, 110, "CoughSyrup", 85.00f, 15, &isInserted);
    isInserted = 0;
    root = insert(root, 105, "ORSSachetPack", 12.00f, 70, &isInserted);

    return root;
}

// frees all nodes before the program exits
void freeTree(struct Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main(void) {
    struct Node *root = NULL;
    int choice, medicineID, quantity;
    int isInserted, threshold, found;
    int inputStatus;
    char name[50];
    float price;
    struct Node *temp;

    root = loadSampleData(root);

    printf("===============================================\n");
    printf("          LOW-COST MEDICINE INVENTORY\n");
    printf("===============================================\n");

    while (1) {
        printf("\n--------------- MENU ---------------\n");
        printf("1. Insert Medicine\n");
        printf("2. Search Medicine by ID\n");
        printf("3. Update Medicine Quantity\n");
        printf("4. Display Medicines in Sorted ID Order\n");
        printf("5. Low-Stock Alert\n");
        printf("6. Total Inventory Value\n");
        printf("7. Exit\n");
        printf("------------------------------------\n");

        inputStatus = readInt("Enter your choice: ", &choice);

        if (inputStatus == 0) {
            printf("\nEnd of input. Exiting program.\n");
            freeTree(root);
            return 0;
        }

        if (inputStatus == -1) {
            continue;
        }

        switch (choice) {
            case 1:
                inputStatus = readInt("Enter Medicine ID: ", &medicineID);

                if (inputStatus == 0) {
                    freeTree(root);
                    return 0;
                }

                if (inputStatus == -1) {
                    break;
                }

                if (medicineID <= 0) {
                    printf("Medicine ID must be positive.\n");
                    break;
                }

                if (search(root, medicineID) != NULL) {
                    printf("A medicine with this ID already exists.\n");
                    break;
                }

                inputStatus = readMedicineName(name, sizeof(name));

                if (inputStatus == 0) {
                    freeTree(root);
                    return 0;
                }

                if (inputStatus == -1) {
                    break;
                }

                inputStatus = readPrice(&price);

                if (inputStatus == 0) {
                    freeTree(root);
                    return 0;
                }

                if (inputStatus == -1) {
                    break;
                }

                inputStatus = readInt("Enter Quantity: ", &quantity);

                if (inputStatus == 0) {
                    freeTree(root);
                    return 0;
                }

                if (inputStatus == -1) {
                    break;
                }

                if (quantity < 0) {
                    printf("Quantity cannot be negative.\n");
                    break;
                }

                isInserted = 0;
                root = insert(root, medicineID, name, price,quantity, &isInserted);

                if (isInserted == 1) {
                    printf("Medicine inserted successfully!\n");
                }
                else {
                    printf("Medicine insertion failed.\n");
                }

                break;

            case 2:
                inputStatus = readInt("Enter Medicine ID to search: ",&medicineID);

                if (inputStatus == 0) {
                    freeTree(root);
                    return 0;
                }

                if (inputStatus == -1) {
                    break;
                }

                temp = search(root, medicineID);

                if (temp != NULL) {
                    displayHeader();
                    displayMedicine(temp);
                }
                else {
                    printf("Medicine not found.\n");
                }

                break;

            case 3:
                inputStatus = readInt("Enter Medicine ID to update: ",&medicineID);

                if (inputStatus == 0) {
                    freeTree(root);
                    return 0;
                }

                if (inputStatus == -1) {
                    break;
                }

                inputStatus = readInt("Enter new quantity: ", &quantity);

                if (inputStatus == 0) {
                    freeTree(root);
                    return 0;
                }

                if (inputStatus == -1) {
                    break;
                }

                updateQuantity(root, medicineID, quantity);
                break;

            case 4:
                if (root == NULL) {
                    printf("Inventory is empty.\n");
                }
                else {
                    printf("\n                    MEDICINE INVENTORY\n");
                    displayHeader();
                    inorder(root);
                }

                break;

            case 5:
                inputStatus = readInt("Enter low-stock threshold: ",&threshold);

                if (inputStatus == 0) {
                    freeTree(root);
                    return 0;
                }

                if (inputStatus == -1) {
                    break;
                }

                if (threshold < 0) {
                    printf("Threshold cannot be negative.\n");
                    break;
                }

                found = 0;
                lowStockAlert(root, threshold, &found);

                if (found == 0) {
                    printf("No medicines are below this threshold.\n");
                }
                

                break;

            case 6:
                printf("\nTotal Inventory Value: Rs. %.2f\n",
                       totalInventoryValue(root));
                break;

            case 7:
                freeTree(root);
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice. Select 1 to 7.\n");
        }
    }
}
