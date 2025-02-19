# Tests

## Test 1: Argument Count Tests
* 1.1: Missing Length Argument
* 1.2: Help Option (-h) Works
* 1.3: Extra Parameters Not Allowed

Expected output: 
```console
Usage:
./rodcut [-h] length
length = integer > 0
```

## Test 2: Invalid Length Tests
* 2.1: Non-Integer Length
* 2.2: Length Less Than 1
* 2.3: Length Greater Than MAX_INT

Expected output: 
```console
Usage:
./rodcut [-h] length
length = integer > 0
```

## Test 3: Length/Cost Input Tests
* 3.1: At Least One Length/Cost Pair
* 3.2: No Duplicate Lengths
* 3.3: Both Length and Cost Must Be Integers ≥ 1
* 3.4: Proper Formatting (num, num Only on Each Line)
* Note: Optional space after comma (Valid Input)

Expected output: 
```console
Error in value list.
```

## Test 4: Output Verification Tests
* 4.1: length < any piece: len 10, 100/1, 50/2 -> 0, remainder 10

## Test 5: No Remainder (Optimal Cut Exactly Matches Rod Length)
* 5.1: No Duplicates, Exact Fit: len 8, 5/4 + 3/2 -> 1@5, 3@2
* 5.2: Single Length Fitting Exactly: len 20, 20/5, 10/2 -> 1@20
* 5.3: Composed Instead of Single, Based on Value: len 20, 20/2, 10/3, 6/4, 4/4 -> 1@10, 1@6, 1@4
* 5.4: Handling Duplicate Lengths: len 20, 10/4, 5/3 -> 4@5

## Test 6: Cases with Remainder
* 6.1: One Piece with Remainder: len 10, 8/4 -> 1 @8, rem 2
* 6.2: Multiple Pieces with Remainder: len 20, 7@3, 6@4 -> 3@6, rem 2

## Test 7: Not Value-Based (Even Split Instead of Max Profit)
* 7.1: Equal Length Preference Instead of Value: len 8, 6/5, 4/4 -> 2@4, rem 0

## Test 8: Same Tests with Different Length Order
