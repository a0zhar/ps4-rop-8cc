# 8CC (A PS4 Targeted C Compiler)

This is not the original **8CC** (*Toy C Compiler*), this is a port of **Shinh's [ELVM branch](https://github.com/shinh/8cc/tree/eir)** of the **8CC Compiler**.
It has been modified to instead of compiling C code for Linux Systems, it instead compiles C code in a way that's compatible with the PS4 Target System.

## 8CC Details/Design
The ***Toy C Compiler* 8CC** was designed to be **lightweight**, and the **Source Code** focused on simplicity.
Meant to support the all C11 standard feaures (**Not fully accomplished yet!**).

It demonstrates key stages of C code compilation, including: **Lexing**, **PReprocessing**, **Parsing**, etc. 
- making it an excellent resource for understanding compiler construction.

### Compiler Speed
**The `8CC Compiler` is no speed demon!** <br>
It compiles the C code onto a stack machine, and is is then run on a software-emulated stack. <br>
The use of PS4-specific ROP further slows things down by essentially disabling CPU branch prediction. 
- The end result is that an empty `for` loop does about 1e6 iterations per second.


### Optimizations
**The `8CC Compiler`** is not a optimizing Compiler. <br>
Currently, the generated code is approximately twice as slow, or more, as GCC output. 
- Future plans include introducing optimizations to improve performance.


### Memory Management Scheme
The memory management in 8CC is, unironically, **No Memory Management**. 
What this means is that all **Memory regions** that are allocated with `malloc` or `calloc` will never freed until the 8CC process terminates.  
- This design greatly simplifies the code and APIs because:
  - Developers can write code as if a garbage collector were present.
  - It eliminates **use-after-free bugs** entirely.

### Additional Details
In terms of **Memory Usage** The 8CC Compiler consumes about **100MB** of memory to compile a 10K-line C source file. 
But this isn't a issue, since modern computers have abundant memory, making this approach viable for most use cases.
- If needed, a garbage collector like the **Boehm GC** could be implemented, though it is not necessary at this time.



---

## Resources for Compiler Development
Developers interested in compiler construction may find the following resources helpful:
- **LCC: A Retargetable C Compiler**: [Book and GitHub](https://github.com/drh/lcc)
- **Tiny C Compiler (TCC)**: [Bellard.org](http://bellard.org/tcc/)
- **C Standards**: [C99 Draft](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1124.pdf), [C11 Draft](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf)
- **Dave Prosser's C Preprocessing Algorithm**: [Spinellis.gr](http://www.spinellis.gr/blog/20060626/)
- **x86-64 ABI Reference**: [Documentation](http://www.x86-64.org/documentation/abi.pdf)
