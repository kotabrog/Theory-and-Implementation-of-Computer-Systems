@256
D=A
@SP
M=D
@RETURNADDRESS0
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M-1
D=D-1
D=D-1
D=D-1
@ARG
M=D-1
@SP
D=M
@LCL
M=D
@Sys.init
0;JMP
(RETURNADDRESS0)
(Sys.init)
@4000
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
@3
M=D
@5000
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
@4
M=D
@RETURNADDRESS1
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M-1
D=D-1
D=D-1
D=D-1
@ARG
M=D-1
@SP
D=M
@LCL
M=D
@Sys.main
0;JMP
(RETURNADDRESS1)
@SP
M=M-1
A=M
D=M
@6
M=D
(Sys.init$LOOP)
@Sys.init$LOOP
0;JMP
(Sys.main)
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@4001
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
@3
M=D
@5001
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
@4
M=D
@200
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
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
@40
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
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
@6
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@3
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
@123
D=A
@SP
A=M
M=D
@SP
M=M+1
@RETURNADDRESS2
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M-1
D=D-1
D=D-1
D=D-1
D=D-1
@ARG
M=D-1
@SP
D=M
@LCL
M=D
@Sys.add12
0;JMP
(RETURNADDRESS2)
@SP
M=M-1
A=M
D=M
@5
M=D
@LCL
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
@1
A=A+D
D=M
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@2
A=A+D
D=M
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@3
A=A+D
D=M
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@4
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
@SP
M=M-1
A=M
M=D+M
@SP
M=M+1
@LCL
D=M
@R13
M=D
@R13
A=M-1
A=A-1
A=A-1
A=A-1
A=A-1
D=M
@R14
M=D
@SP
M=M-1
A=M
D=M
@ARG
A=M
M=D
@ARG
D=M+1
@SP
M=D
@R13
A=M-1
D=M
@THAT
M=D
@R13
A=M-1
A=A-1
D=M
@THIS
M=D
@R13
A=M-1
A=A-1
A=A-1
D=M
@ARG
M=D
@R13
A=M-1
A=A-1
A=A-1
A=A-1
D=M
@LCL
M=D
@R14
A=M
0;JMP
(Sys.add12)
@4002
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
@3
M=D
@5002
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
@12
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
@LCL
D=M
@R13
M=D
@R13
A=M-1
A=A-1
A=A-1
A=A-1
A=A-1
D=M
@R14
M=D
@SP
M=M-1
A=M
D=M
@ARG
A=M
M=D
@ARG
D=M+1
@SP
M=D
@R13
A=M-1
D=M
@THAT
M=D
@R13
A=M-1
A=A-1
D=M
@THIS
M=D
@R13
A=M-1
A=A-1
A=A-1
D=M
@ARG
M=D
@R13
A=M-1
A=A-1
A=A-1
A=A-1
D=M
@LCL
M=D
@R14
A=M
0;JMP
