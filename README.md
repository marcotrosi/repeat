# repeat

Commandline program that repeats a string by a given amount. Supports a separator string, reversing the input string and
can be used in pipes.


## Background

In our Unix chat group the question "how can a string be printed repeatedly?" came up, and after some investigations on
the internet we had to admit that
[there was no satisfying POSIX-like solution available](https://superuser.com/questions/86340/linux-command-to-repeat-a-string-n-times)
as we know it from tools like cut, tr, grep, tac, wc, and so on. Here some possibilities ...

    $ yes foo | head -n 3 | tr -d '\n'
    foofoofoo

    $ printf 'foo%.0s' {1..3}
    foofoofoo

    $ for i in `seq 3`; do echo -n 'foo'; done
    foofoofoo

So we brought this topic to our C-coding group to have a nice practicing playground for our beginners.


## Building

    make


## Examples

    $ repeat 3 foo
    foofoofoo

    $ echo 'foo' | repeat 3
    foofoofoo

    $ repeat -s ',' 3 foo
    foo,foo,foo

    $ repeat -- -2 foo
    oofoof

    $ repeat -e -s '\t' 3 foo
    foo   foo   foo


## Usage

    repeat [-v] [-h] [-n] [-e] [-s <sep>] repetitions [string]


## Options

    -s <sep>  optional separator string
    -n        do not output the trailing newline
    -e        interpret some few escape sequences (\\,\t,\n)
    -v        print version info
    -h        print help text

