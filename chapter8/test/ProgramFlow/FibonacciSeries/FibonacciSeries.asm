@ARG
D=M
@1
A=A+D
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@4
M=D
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@THAT
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
@1
D=A
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@1
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
@2
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M-D
@SP
M=M+1
@ARG
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
(FibonacciSeries.vm$MAIN_LOOP_START)
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
@SP
M=M-1
A=M
D=M
@FibonacciSeries.vm$COMPUTE_ELEMENT
D;JNE
@FibonacciSeries.vm$END_PROGRAM
0;JMP
(FibonacciSeries.vm$COMPUTE_ELEMENT)
@THAT
D=M
@0
A=A+D
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@1
A=A+D
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=D+M
@SP
M=M+1
@THAT
D=M
@2
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
@4
D=M
@SP
A=M
M=D
@SP
M=M+1
@1
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=D+M
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@4
M=D
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
@1
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M-D
@SP
M=M+1
@ARG
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
@FibonacciSeries.vm$MAIN_LOOP_START
0;JMP
(FibonacciSeries.vm$END_PROGRAM)
