# JackAnalyzer

This program converts from the high layer language to an intermediate language created in the exercise.

## Exsample

```
class Main {

   function void main() {
      do Output.printInt(1 + (2 * 3));
      return;
   }

}
```

to

```
function Main.main 0
push constant 1
push constant 2
push constant 3
call Math.multiply 2
add
call Output.printInt 1
pop temp 0
return
```
