# Low-Cost Medicine Inventory — PS 02

## Problem statement
Develop a searchable inventory of generic medicines for a small community pharmacy using medicine ID as the key.

## SDG connection
**SDG 3 — Good Health and Well-being.** A basic inventory can help a community pharmacy keep track of medicine stock. This is a classroom simulation, not a real pharmacy system.

## Language and data structure
- Language: C
- Data structure: Binary Search Tree (BST)
- Key: Medicine ID
- Each node stores medicine ID, medicine name, price, quantity, and left/right pointers.
- Smaller IDs are stored in the left subtree; larger IDs are stored in the right subtree.
- Inorder traversal displays medicines in ascending ID order.

## Required functionality from the assignment
1. Insert medicine.
2. Search by medicine ID.
3. Update quantity.
4. List medicines in sorted ID order.
5. Demonstrate 8 medicines and one unavailable ID.

The program starts with eight fictional sample medicines. You can insert additional medicines using the menu.

## Assumptions
- Medicine IDs are positive integers and unique.
- Medicine names are entered as one word (no spaces), matching the simple `scanf` input style.
- Price and quantity cannot be negative.
- Updating quantity replaces the current quantity with the new quantity.
- Data is stored in memory and is lost when the program exits.
- No database, external API, authentication, GUI, or hardware integration is used.

## Compile
```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o medicine_inventory
```

Run in Windows PowerShell:
```powershell
.\medicine_inventory.exe
```

## Time complexity
Let `n` be the number of medicines.

| Operation | Average case | Worst case |
|---|---:|---:|
| Insert | O(log n) | O(n) |
| Search | O(log n) | O(n) |
| Update quantity, including search | O(log n) | O(n) |
| Display sorted inventory | O(n) | O(n) |

A normal BST can become skewed, so the average-case logarithmic time is not guaranteed in the worst case.

## Project files
- `main.c` — source code
- `README.md` — project description and assumptions
- `sample-input.txt` — example menu inputs
- `sample-output.txt` — representative output
- `test-cases.md` — normal, boundary, invalid and unavailable-ID tests
