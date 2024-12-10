# PS4-ROP-8CC

This is a port of shinh's [ELVM branch of 8cc](https://github.com/shinh/8cc/tree/eir) to the PS4 return-oriented programming. 
It runs C code on OFW 6.51 (EDIT: 6.72 confirmed to be working too) via [Fire30's WebKit exploit](https://github.com/Fire30/bad_hoist).


## Running
A reference script, `scripts/run.py`, is provided. 
- Example: `python3 scripts/run.py file1.c [file2.c]...`


## **Custom ABI**

ELVM register mappings for x64 are adjusted for PS4 compatibility:

| **ELVM Register** | **x64 Register** | **Notes**                       |
|--------------------|------------------|----------------------------------|
| A                  | rax              | Primary accumulator             |
| B                  | rcx              | Return value register           |
| C                  | r10              | General-purpose register        |
| D                  | --               | Not used by the compiler        |
| SP                 | rdi              | Emulated stack pointer          |
| BP                 | r8               | Emulated base pointer           |

- The stack (`rsp`) is used for the ROP chain, requiring stack emulation in user code.
- Function calls follow a modified **cdecl** convention: `push next ; jmp func ; next:`. The return value resides in `B` (`rcx`).

### **Calling Conventions**

The compiler supports mixed ROP-to-ROP and ROP-to-native calls, converting conventions as needed. <br>
Native-to-ROP calls require explicit handling, typically with the provided `librop` utilities:

```c
#include <librop/extcall.h>
...
void native_func(..., void(*)(...), void* opaque, ...);
void my_very_func(void* opaque, ...);  // Supported format
...
extcall_t ec;
char stack[8192];  // Emulated stack for my_very_func
create_extcall(ec, my_very_func, stack + 8192, opaque);
native_func(..., extcall_gadget, ec, ...);
```

To invoke a native function pointer, use the `rop_call_funcptr` utility or equivalent:

```c
rop_call_funcptr(ptr_to_printf, "Hello, %s!\n", "world");
```

For threading support, `librop/pthread_create.h` includes a ready-to-use wrapper for `pthread_create`.


# Credits
- [Sleirsgoevy](https://github.com/Sleirsgoevy/ps4-rop-8cc)
