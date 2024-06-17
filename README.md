# fdmj_compiler
a simple compiler for Fudan Mini-Java, a very simple programming language

# How to use
You can use the instructions in a shell as below:

1. “make build”: this builds the compiler.
2. “make compile”: this compiles each fmj source file in the test 
directory.
3. “make run-llvm”: this executes the LLVM code after converting to SSA form.
4. “make run-rpi”: this executes the RPi code after register allocation