# Code Review Updates

## Changes in `rodcut.c`
- **Filename Handling:** The piece values file is now passed as `argv[1]`, not read interactively from stdin.
- **Proper File Processing Order:** Piece values are loaded from the file before handling rod lengths.
- **Rod Length Handling:** Rod lengths are processed one per line, only after piece values are successfully loaded.
- **Error Handling:**
  - The program displays an error message and terminates if the specified file is not present.
  - If the file is empty or does not contain valid length-value pairs, an error message is displayed, and execution stops.
- **User Input Validation:** The program prompts the user for a rod length, validates the input, notifies of errors, and requests another input if is invalid.

## Changes in `cutlist.c`
- **JSON Output:** The functionality for printing the cutlist to JSON has been updated to support multiple rod length results.

## Changes in `piece_values.c`
- **File Parsing:**
  - Blank lines and lines starting with `#` in the piece values file are ignored.
  
## Addition of `test.sh`