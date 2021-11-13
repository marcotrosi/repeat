# repeat

Commandline program that prints a string repeatedly.

## Background

In our Unix chat group the question "how can a string be printed repeatedly?" came up, and after some investigations on
the internet we had to admit that there was no satisfying POSIX-like solution available as we know it from tools like
cut, tr, grep, tac, wc, and so on. So we brought this topic to our C-coding group to have a nice practicing playground for
our beginners.

So currently this is under development and will be released when the group says the tool is ready.

## Building

    make

## Usage

    repeat 3 foo # prints foofoofoo
