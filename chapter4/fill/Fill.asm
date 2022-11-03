// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

(LOOP)

@KBD
D=M
@COLOR
D;JGT

@value
M=0
@START
0;JMP

(COLOR)
@value
M=1

(START)
@i
M=0

(PUTSCREEN)
@i
D=M
@8191
D=D-A
@LOOP
D;JGT

@SCREEN
D=A
@i
D=D+M
@addr
M=D

@value
D=M
@PUTCOLOR
D;JGT

@addr
A=M
M=0
@END
0;JMP

(PUTCOLOR)
@addr
A=M
M=0
M=M-1

(END)

@i
M=M+1

@PUTSCREEN
0;JMP

@LOOP
0;JMP