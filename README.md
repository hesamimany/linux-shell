# linux-shell

My own linux shell programmed in c

## Description

A simple program for running linux and some of my own commands

## Getting Started

### Dependencies

- readline library
- linux

### Installing

```bash
sudo apt-get install libreadline-dev
```

### Executing program

```bash
gcc main.c -lreadline ./a.out
```

## Help

My own commands

### firstWord()

```bash
fw fileaddress
```

Prints first word of every line in the given file

### highRepeat()

```bash
hr fileaddress
```

Prints the most repeated word in the given file

### removeSpace()

```bash
rs fileaddress
```

Removes whitespase from file

### nonComment()

```bash
nc fileaddress
```

Prints lines which do not start with # in the given file

### lineCounter()

```bash
lc fileaddress
```

Counts number of lines in the given file

### tenLine()

```bash
tl fileaddress
```

Prints first ten line in the given file

Use following command to close the programm because you can not use ctrl + c to terminate the bash (signal handling)

```bash
exit
``` 

You can see command instruction by using follosing command

```bash
help
```

## Authors

- Ghazale Chakane
- Mohammad Hesam Imani