# Guess the number

Current status: **OK**

## Description (How to play)
1. Type maximum possible number `max_number` to be guessed. `max_number` must be integer and be not less than `1`.
Program will generate random number in range `[0; max_number]`.
2. Type your guesses of number.  
You will get `< (generated number is less)` if generated number is less than the one you typed in.  
You will get `> (generated number is greater)` if generated number is greater than the one you typed in.  
If you guess the number you will be get score of `(1 - <number of guesses> / log[2](max(max_number, 2))) * 10` rounded by two digits after the decimal point.  
(`log[2](max_number)` is logarithm of `max_number` to base `2`).

Note: `log[2](max_number)` and not `log[2](max_number + 1)` in score calculation is done on purpose.

## Compilation
```
make
```

## Clean-up
```
make clean
```

## Requirements
You need `make` and `g++` to compile this game.
