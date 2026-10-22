# Test cases for PS 02

The assignment requires a demonstration with eight medicines and one unavailable ID, plus at least three test categories: normal, boundary, and invalid/empty.

## Test 1 — Sorted listing (normal)
- Choose option `4`.
- Expected: all eight medicines display in ascending medicine ID order.

## Test 2 — Search existing ID (normal)
- Choose option `2`, enter `104`.
- Expected: Paracetamol details are displayed.

## Test 3 — Search unavailable ID (required)
- Choose option `2`, enter `999`.
- Expected: `Medicine not found.`

## Test 4 — Update quantity (normal)
- Choose option `3`, enter ID `101`, then quantity `75`.
- Expected: `Quantity updated successfully.`
- Search ID `101` afterward to verify quantity is 75.

## Test 5 — Quantity zero (boundary)
- Choose option `3`, enter ID `103`, then quantity `0`.
- Expected: update succeeds. Zero is accepted as a valid stock quantity.

## Test 6 — Negative quantity (invalid)
- Choose option `3`, enter ID `103`, then quantity `-5`.
- Expected: `Quantity cannot be negative.`

## Test 7 — Duplicate medicine ID (invalid)
- Choose option `1`, enter ID `101`.
- Expected: `A medicine with this ID already exists.`

## Test 8 — Negative ID (invalid)
- Choose option `1`, enter ID `-2`.
- Expected: `Medicine ID must be positive.`

## Test 9 — Invalid menu choice
- Enter `9`.
- Expected: `Invalid choice. Select 1 to 5.`

## Empty inventory branch
The program loads eight sample records at startup, so the inventory is not empty during the normal demo. To test the empty-tree message, temporarily comment out `root = loadSampleData(root);` in `main()`, compile again, and select option 4. Restore the sample-data call before the final demo.
