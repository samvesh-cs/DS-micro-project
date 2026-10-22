# Low-Cost Medicine Inventory System

A beginner-friendly, console-based medicine inventory management project
written in C. The project uses a **Binary Search Tree (BST)** to store
and search medicine records by their unique medicine ID.

## Project Overview

Small community pharmacies need a simple way to keep track of medicine
stock, find medicine records quickly, identify medicines running low,
and estimate the value of the inventory they currently hold.

This project demonstrates how a data structure can help organize and
manage inventory records without requiring a database, external API, or
graphical interface.

## Objectives

-   Store medicine records using a unique medicine ID.
-   Insert new medicines into the inventory.
-   Search for a medicine by its ID.
-   Update the quantity of an existing medicine.
-   Display medicines in ascending order of medicine ID.
-   Alert the user when medicine quantity is below a chosen threshold.
-   Calculate the total value of the inventory using `price × quantity`.
-   Validate user input and reject invalid medicine names and values.

## Features

### 1. Insert Medicine

The user enters a medicine ID, name, price, and quantity. The program
checks that: - The ID is positive and is not already present. - The name
contains alphabetic letters only; spaces, numbers, and special
characters are rejected. - The price is numeric, finite, and
non-negative. - The quantity is a whole number and is not negative.

The program uses an `isInserted` flag to report whether the BST
insertion succeeded.

### 2. Search Medicine by ID

The program searches the BST using the medicine ID. If a matching record
is found, its details are displayed; otherwise, the program reports that
the medicine was not found.

### 3. Update Medicine Quantity

The user provides a medicine ID and a new quantity. The program updates
the quantity only if the medicine exists and the new quantity is not
negative. A quantity of zero is allowed.

### 4. Display Inventory in Sorted Order

The program uses **inorder traversal**---left subtree, current node,
right subtree---to display medicines in ascending order of medicine ID.

### 5. Low-Stock Alert

The user chooses a stock threshold. The program displays medicines whose
quantity is **strictly less than** the threshold. For example, with a
threshold of `30`, a medicine with quantity `29` is displayed, but a
medicine with quantity `30` is not.

### 6. Total Inventory Value

The program calculates the total value of all medicine stock using:

`Total Inventory Value = Σ (Medicine Price × Quantity)`

For example, if one medicine costs Rs. 25 per unit and the inventory
contains 100 units, that medicine contributes Rs. 2,500 to the total.

### 7. Exit and Memory Cleanup

Before exiting, the program traverses the tree and frees the dynamically
allocated nodes.

## Data Structure Used: Binary Search Tree (BST)

A **Binary Search Tree** is a tree in which each node has at most two
children. For this project:

-   IDs smaller than a node's ID are stored in its left subtree.
-   IDs larger than a node's ID are stored in its right subtree.
-   Duplicate medicine IDs are not allowed.

Each node stores:

  Field          Description
  -------------- --------------------------------------------
  `medicineID`   Unique key used for ordering and searching
  `name`         Medicine name
  `price`        Price per unit
  `quantity`     Current stock quantity
  `left`         Pointer to the left child
  `right`        Pointer to the right child

### Why use a BST?

A BST organizes records by medicine ID and supports searching and
insertion without needing to shift array elements. Inorder traversal
also gives sorted output naturally.

BST performance depends on its shape. A reasonably balanced BST can
support search and insertion in approximately `O(log n)` time on
average. In the worst case, when the tree becomes skewed, these
operations can take `O(n)` time.

## Sample Medicines

The program loads eight sample records at startup so the features can be
demonstrated immediately.

    Medicine ID Medicine Name       Price (Rs.)   Quantity
  ------------- ----------------- ------------- ----------
            104 Paracetamol               25.00        100
            101 Cetirizine                18.00         60
            108 ORS                       22.00         45
            103 Antacid                   35.00         30
            106 VitaminC                  40.00         25
            102 AntisepticCream           55.00         20
            110 CoughSyrup                85.00         15
            105 ORSSachetPack             12.00         70

These are synthetic demonstration records, not medical recommendations.

## Requirements

-   A C compiler such as GCC.
-   A terminal or command prompt.
-   Standard C library support for the functions used by the program.

The source uses standard headers including `stdio.h`, `stdlib.h`,
`string.h`, `ctype.h`, `errno.h`, `limits.h`, and `math.h`.

## How to Compile and Run

Save the source code as `main.c`.

### Windows PowerShell (GCC / MinGW)

``` bash
gcc main.c -o medicine_inventory.exe
.\medicine_inventory.exe
```

### Linux / macOS

``` bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o medicine_inventory
./medicine_inventory
```

If your compiler reports that math functions require a separate math
library, try adding `-lm` at the end of the compile command.

## Menu Options

When the program starts, it displays the following menu:

1.  Insert Medicine
2.  Search Medicine by ID
3.  Update Medicine Quantity
4.  Display Medicines in Sorted ID Order
5.  Low-Stock Alert
6.  Total Inventory Value
7.  Exit

Choose an option by entering its number and follow the prompts.

## Function Overview

  -----------------------------------------------------------------------
  Function                            Responsibility
  ----------------------------------- -----------------------------------
  `readLine()`                        Reads a complete line and detects
                                      overlong input

  `readInt()`                         Converts input into a checked
                                      integer

  `readPrice()`                       Reads and validates a finite,
                                      non-negative price

  `isValidName()`                     Checks that a name contains letters
                                      only

  `readMedicineName()`                Reads and validates the full
                                      medicine name

  `createNode()`                      Allocates and initializes a
                                      medicine node

  `insert()`                          Inserts a medicine into the BST and
                                      reports insertion status

  `search()`                          Finds a medicine by ID

  `displayHeader()`                   Prints inventory table headings

  `displayMedicine()`                 Prints one medicine record

  `updateQuantity()`                  Updates stock for an existing
                                      medicine

  `inorder()`                         Displays medicines in sorted ID
                                      order

  `lowStockAlert()`                   Displays medicines below a chosen
                                      threshold

  `totalInventoryValue()`             Calculates the total stock value

  `loadSampleData()`                  Inserts the eight sample medicines

  `freeTree()`                        Releases the dynamically allocated
                                      tree nodes

  `main()`                            Loads sample data and runs the menu
  -----------------------------------------------------------------------

## Time Complexity

Let `n` be the number of medicines and `h` be the height of the BST.

  Operation                             Typical / average case   Worst case
  ----------------------------------- ------------------------ ------------
  Search by ID                                      `O(log n)`       `O(n)`
  Insert                                            `O(log n)`       `O(n)`
  Display all medicines (`inorder`)                     `O(n)`       `O(n)`
  Low-stock alert                                       `O(n)`       `O(n)`
  Total inventory value                                 `O(n)`       `O(n)`
  Free the tree                                         `O(n)`       `O(n)`

The BST is not self-balancing, so its height depends on the order in
which IDs are inserted.

## Suggested Test Cases

  -----------------------------------------------------------------------
  Test                    Input / action          Expected result
  ----------------------- ----------------------- -----------------------
  Search existing         Search ID `101`         Cetirizine record is
  medicine                                        displayed

  Search missing medicine Search ID `999`         "Medicine not found"
                                                  message

  Duplicate ID            Try inserting ID `101`  Insertion is rejected

  Invalid ID              Enter `-5`              ID is rejected because
                                                  it must be positive

  Invalid name with       Enter `Vitamin C`       Name is rejected
  spaces                                          

  Invalid name with       Enter `Para123`         Name is rejected
  digits                                          

  Valid name              Enter `Paracetamol`     Name passes validation

  Negative price          Enter `-10`             Price is rejected

  Non-finite price        Enter `nan` or `inf`    Price is rejected

  Negative quantity       Enter `-4`              Quantity is rejected

  Update quantity         Update ID `101` to `0`  Quantity becomes zero

  Low-stock alert         Use threshold `30`      Only quantities below
                                                  30 are shown

  Sorted display          Select option `4`       IDs are shown in
                                                  ascending order

  Total value             Select option `6`       Total of price
                                                  multiplied by quantity
                                                  is displayed
  -----------------------------------------------------------------------


## Possible Future Improvements

-   Store records in a file or database so changes persist after exit.
-   Add expiry-date tracking and alerts.
-   Add a delete-medicine operation.
-   Allow common medicine names containing spaces or hyphens while
    validating them safely.
-   Balance the tree or use another data structure if the inventory
    becomes large.
-   Improve table borders and add inventory summaries.

## Conclusion

The Low-Cost Medicine Inventory System demonstrates how a Binary Search
Tree can organize medicine records and support insertion, search,
quantity updates, sorted display, low-stock alerts, and inventory
valuation. It also practices recursion, pointers, dynamic memory
allocation, string handling, and input validation in C.
