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
fw fileadd
```

Prints first word of every line in the given file

### highRepeat()

```bash
hr fileadd
```

Prints the most repeated word in the given file

### nonComment()

```bash
nc fileadd
```

Prints lines which do not start with # in the given file

### lineCounter()

```bash
lc fileadd
```

Counts number of lines in the given file

### tenLine()

```bash
tl fileadd
```

Prints first ten line in the given file

## Authors

- Ghazale Chakane
- Mohammad Hesam Imani