# Corewar
Lem-in is a School 21(Ecole 42) project. 

## Description
The purpose of this project is an implementation of the programming game “Core War”.

Breakdown of the project’s objectives
This project can be broken down into three distinctive parts:
### The assembler
This is the program that will compile your champions and translate them from the language you will
write them in (assembly language) into “Bytecode”. Bytecode is a machine code, which will be directly
interpreted by the virtual machine.
### The virtual machine
It’s the “arena” in which your champions will be executed.
It offers various functions, all of which will be useful for the battle of the champions.
Obviously, the virtual machine should allow for numerous simultaneous processes;
we are asking you for a gladiator fight, not a one-man show simulator.
### The visualisation
Displaying the entire battle process in graphical form.

## Instructions
* You have to handle errors in a sensitive manner. In no way can your program quit
in an unexpected manner (Segmentation fault, bus error, double free, etc).
* Your program cannot have memory leaks.
* You are allowed to use **only** the following libc functions.
```
◦ open
◦ read
◦ lseek
◦ write
◦ close
◦ malloc
◦ realloc
◦ free
◦ perror
◦ strerror
◦ exit
```

You can find a detailed description of the task [here](https://github.com/VBrazhnik/Corewar/blob/master/corewar.en.pdf).

## Project Structure

* Assembler
* Virtual machine
* Visualisation (ncurses, web)
* Libft - A library that contains useful native functions (`ft_printf`, `ft_split`, `ft_atoi`, `ft_itoa`, varios `str`
functions (`ft_strcpy`, `ft_strdub`, `ft_strcmp` etc.))
* Testing_suite - part for test this project.

## Installation

Clone repository and then go into the created directory and run the following command:

```
make
```

## Usage

### Assembler
```
assembler:    ./asm -a file.s
disassembler: ./asm -d file.cor
```
### Virtual machine
```
./corewar [-dump nbr_cycles -v N | -nc | -w] [-o] [-l] [[-n number] champion1.cor] ...

          -dump nbr_cycles  : Dump the memory on the standard output and quit the game
          -n number         : Sets the number of the next player
          -v N              : Verbosity levels, can be added together to enable several
                              - 0   Show only essentials
                              - 1   Show lives
                              - 2   Show cycles
                              - 4   Show operations (Params are NOT literal ...)
                              - 8   Show deaths\n"
                              - 16  Show PC movements (Except for jumps)
          -nc               : Ncurses output mode
          -w                : Web output mode
          -l                : Hide display live instruction
          -o                : Original behaviour
```
### Test

```
./runtest
```
Before execution `./runtest` the project must be compiled.

## Visualisation
For `-nc` flag. The best visualizer performance is with iTerm2.

![corewar](/readme_resources/visu.png)

For `-w` flag. The browser tab will be open in your default browser.

![corewar](/readme_resources/visu_web.png)
