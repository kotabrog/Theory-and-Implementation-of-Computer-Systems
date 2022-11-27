# VMtranslator

This is a program that converts from the intermediate language created to assembly in the exercise.

## Exsample

```
push constant 0    
pop local 0         // initializes sum = 0
label LOOP_START
push argument 0    
push local 0
add
pop local 0	        // sum = sum + counter
push argument 0
push constant 1
sub
pop argument 0      // counter--
push argument 0
if-goto LOOP_START  // If counter != 0, goto LOOP_START
push local 0

```

to

```
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@0
A=A+D
D=A
@R13
M=D
@SP
M=M-1
A=M
D=M
@R13
A=M
M=D
(BasicLoop.vm$LOOP_START)
@ARG
D=M
@0
A=A+D
D=M
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
...
```
