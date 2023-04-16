# PS4-ROP-8cc

## Overview
PS4-ROP-8cc is a toy C compiler that is a fork of sleirsgoevy's 8cc repository. This (version) of his project is maintained by me i guess and will receive frequent updates and changes.


# Changelog
### 16/04/23:
#### gen.c
- `static void emit_lload(Type* ty, char* base, int off)`
  - use switch statement instead of if-else if in function 
- `static char** read_source_file(char* file)`
  - Added error handling: New version includes error handling to check for errors in opening the file and allocating memory for the buffer. If any errors occur, the function will properly free memory and close the file then return NULL.
  - Improved error reporting: New version includes nlprintf (printf macro which does newline by default) calls to report any errors encountered during file reading and memory allocation. This provides more detailed information for debugging purposes.
  - Code readability: New version has more structured code and is easier to read as compared to previous version which is condensed and not as readable.

### 15/04/23:
#### parse.c
- use switch statement instead of if-else if in function `make_numtype()`


# Potential Bugs/Issues
#### map.c
- There is a possible memory leak issue in the `map_remove()` function of the eir version. When an element is removed, the key is set to an empty string, but the memory allocated for the string is not freed. This may result in a memory leak if this function is called frequently

