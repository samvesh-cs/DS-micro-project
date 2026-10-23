# Low-Cost Medicine Inventory System (C + Binary Search Tree)

## 1. Project Overview

The **Low-Cost Medicine Inventory System** is a menu-driven C program
that manages medicine records using a **Binary Search Tree (BST)**. Each
medicine is identified by a unique Medicine ID. The BST keeps records
organized by ID, allowing the program to search for, insert, delete, and
display medicine records.

This is an educational data structures project. It demonstrates how a
BST can be used in a practical inventory-management scenario.

## 2. Project Objectives

-   Store medicine details in dynamically allocated BST nodes.
-   Insert new medicine records while preventing duplicate IDs.
-   Search for a medicine using its ID.
-   Update the quantity of an existing medicine.
-   Delete a medicine record while preserving BST ordering.
-   Display all medicines in ascending Medicine ID order.
-   Identify medicines whose stock is below a chosen threshold.
-   Calculate the total value of the inventory.
-   Validate user input and release dynamically allocated memory before
    exit.

## 3. Technology Used

-   **Programming language:** C
-   **Data structure:** Binary Search Tree (BST)
-   **Memory management:** `malloc()` and `free()`
-   **Standard libraries:** `stdio.h`, `stdlib.h`, `string.h`,
    `ctype.h`, `errno.h`, `limits.h`, and `math.h`
-   **Compiler:** GCC (MinGW on Windows can also be used)

## 4. Medicine Record Structure

Each BST node stores the following information:

  Field          Purpose
  -------------- -------------------------------
  `medicineID`   Unique ID used as the BST key
  `name`         Medicine name
  `price`        Price per unit
  `quantity`     Number of units available
  `left`         Pointer to the left child
  `right`        Pointer to the right child

### BST ordering rule

-   IDs smaller than a node's ID are stored in its left subtree.
-   IDs greater than a node's ID are stored in its right subtree.
-   Duplicate IDs are not allowed.

This ordering helps the program find records by comparing IDs as it
moves through the tree.

## 5. Features and Menu Options

  ------------------------------------------------------------------------
                        Option Feature               Description
  ---------------------------- --------------------- ---------------------
                             1 Insert Medicine       Adds a new record
                                                     after validating its
                                                     ID, name, price, and
                                                     quantity. Duplicate
                                                     IDs are rejected.

                             2 Search Medicine by ID Searches the BST and
                                                     displays the matching
                                                     record, if found.

                             3 Update Medicine       Changes the quantity
                               Quantity              of an existing
                                                     medicine. Negative
                                                     quantities are
                                                     rejected.

                             4 Display Medicines in  Uses inorder
                               Sorted ID Order       traversal to display
                                                     records in ascending
                                                     ID order.

                             5 Low-Stock Alert       Displays medicines
                                                     whose quantity is
                                                     strictly less than
                                                     the entered
                                                     threshold.

                             6 Total Inventory Value Calculates the sum of
                                                     `price × quantity`
                                                     for all records.

                             7 Delete Medicine       Removes a medicine by
                                                     ID and maintains the
                                                     BST structure.

                             8 Exit                  Frees the BST nodes
                                                     and exits the
                                                     program.
  ------------------------------------------------------------------------

## 6. How Deletion Works

The `deleteMedicine()` function handles the three standard BST deletion
cases:

1.  **Node has no children:** Free the node and return `NULL`.
2.  **Node has one child:** Save the child pointer, free the node being
    deleted, and return the child so it takes the deleted node's place.
3.  **Node has two children:** Find the smallest node in the right
    subtree using `findMin()`. Copy that successor's medicine details
    into the current node, then delete the successor from the right
    subtree.

The caller assigns the returned pointer back to `root` or to the
appropriate child pointer. This is important because deleting the root
or a subtree root may change which node is at that position.

Before calling `deleteMedicine()`, menu option 7 checks whether the ID
exists using `search()`. If it does not exist, the program reports that
nothing was deleted.

## 7. Sample Data Loaded at Startup

The program automatically inserts these eight sample records each time
it starts:

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

These are sample records for demonstration, not a real pharmacy
database.

## 8. Input Validation

The program includes input checks to reduce invalid input problems:

-   Integer input is checked for malformed values and values outside the
    `int` range.
-   Price input must be finite and non-negative.
-   Medicine names must contain letters only, with no spaces, digits, or
    special characters.
-   Medicine IDs must be positive when adding a new record.
-   Duplicate Medicine IDs are rejected.
-   Quantity and low-stock threshold must not be negative.
-   Overlong input lines are detected and rejected.

## 9. Important Functions

  -----------------------------------------------------------------------
  Function                            Responsibility
  ----------------------------------- -----------------------------------
  `readLine()`                        Reads a complete line and detects
                                      overlong input.

  `readInt()`                         Reads and validates an integer.

  `readPrice()`                       Reads and validates a finite,
                                      non-negative price.

  `isValidName()`                     Checks that a medicine name
                                      contains letters only.

  `readMedicineName()`                Reads and validates a medicine
                                      name.

  `createNode()`                      Allocates and initializes a BST
                                      node.

  `insert()`                          Inserts a medicine into the BST.

  `search()`                          Finds a medicine by ID.

  `findMin()`                         Finds the smallest ID in a subtree
                                      by following left pointers.

  `deleteMedicine()`                  Deletes a medicine while preserving
                                      BST ordering.

  `updateQuantity()`                  Updates the quantity of an existing
                                      medicine.

  `inorder()`                         Displays records in ascending ID
                                      order.

  `lowStockAlert()`                   Displays records below the selected
                                      stock threshold.

  `totalInventoryValue()`             Calculates the total value of all
                                      stock.

  `loadSampleData()`                  Loads the sample records at
                                      startup.

  `freeTree()`                        Frees all allocated nodes before
                                      the program exits.
  -----------------------------------------------------------------------

## 10. Time Complexity

Let `h` be the height of the BST and `n` be the number of medicine
records.

  Operation                         Time Complexity
  --------------------------------- --------------------------
  Search                            `O(h)`
  Insert                            `O(h)`
  Delete                            `O(h)`
  Find minimum in a subtree         `O(h)` in the worst case
  Display all medicines             `O(n)`
  Low-stock alert                   `O(n)`
  Calculate total inventory value   `O(n)`

In a reasonably balanced BST, search, insertion, and deletion take
approximately `O(log n)` time. In a skewed BST, the height can become
`n`, making these operations `O(n)`. This implementation is a regular
BST, not a self-balancing BST.

## 11. How to Compile and Run

### Windows (GCC / MinGW)

Open a terminal in the directory containing `main.c`:

``` bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o medicine_inventory.exe
.\medicine_inventory.exe
```

### Linux

``` bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o medicine_inventory
./medicine_inventory
```

If your compiler reports a math-library linking error for `isfinite()`,
try adding `-lm` at the end of the compile command.

## 12. Suggested Test Cases

  -----------------------------------------------------------------------
  Test                    Action                  Expected result
  ----------------------- ----------------------- -----------------------
  Insert a new ID         Add a medicine with a   Record is added
                          unique positive ID and  
                          valid details           

  Insert duplicate ID     Add a medicine using an Duplicate is rejected
                          ID already present      

  Search existing ID      Search for ID `104`     Paracetamol record is
                                                  displayed

  Search missing ID       Search for an unused ID "Medicine not found"
                                                  message

  Update quantity         Set an existing         Quantity is updated
                          medicine's quantity to  
                          a non-negative value    

  Delete a leaf           Delete a node with no   Node is removed
                          children                

  Delete a node with one  Delete a node with one  Child takes its place
  child                   child                   

  Delete a node with two  Delete a node with two  Inorder-successor
  children                children                method preserves BST
                                                  ordering

  Delete missing ID       Delete an ID not in the Program reports that
                          tree                    nothing was deleted

  Sorted display          Display all medicines   IDs appear in ascending
                                                  order

  Low-stock alert         Enter a threshold       Only records with
                                                  quantity below the
                                                  threshold are shown

  Exit                    Select option 8         Nodes are freed and the
                                                  program exits
  -----------------------------------------------------------------------

## 13. Limitations

-   **No permanent storage:** Records are stored in RAM. Changes,
    including deletions and quantity updates, are lost when the program
    exits. The sample records are loaded again on the next run.
-   **No self-balancing:** The BST can become skewed, which can make
    operations slower.
-   **Basic name rules:** Names containing spaces, hyphens, or digits
    are not accepted by the current validation.
-   **Floating-point price:** `float` is used for the unit price; real
    financial software should use a suitable fixed-point or integer
    representation for currency.
-   **Educational use:** This program is a learning project, not a
    production-ready pharmacy management system.

## 14. Possible Future Improvements

-   Save and load records using files or a database.
-   Add medicine expiry dates and batch numbers.
-   Support medicine names containing spaces.
-   Use a self-balancing BST, such as an AVL tree, for more consistent
    operation times.
-   Add confirmation before deleting a record.
-   Improve currency handling and add more comprehensive tests.

## 15. Conclusion

The Low-Cost Medicine Inventory System demonstrates how a Binary Search
Tree can organize and manage medicine records in C. It combines
insertion, searching, quantity updates, deletion, inorder traversal,
low-stock alerts, and inventory-value calculation. The delete operation
is particularly useful for learning how a BST maintains its ordering
when nodes with zero, one, or two children are removed.
