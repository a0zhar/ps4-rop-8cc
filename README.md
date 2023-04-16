# PS4-ROP-8cc

## Overview
PS4-ROP-8cc is a toy C compiler that is a fork of sleirsgoevy's 8cc repository. This (version) of his project is maintained by me i guess and will receive frequent updates and changes.


# Potential Bugs/Issues
### Files:

#### map.c
- There is a possible memory leak issue in the `map_remove()` function of the eir version. When an element is removed, the key is set to an empty string, but the memory allocated for the string is not freed. This may result in a memory leak if this function is called frequently
