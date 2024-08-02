[![CodeScene general](https://codescene.io/images/analyzed-by-codescene-badge.svg)](https://codescene.io/projects/56597)
[![CodeScene Code Health](https://codescene.io/projects/56597/status-badges/code-health)](https://codescene.io/projects/56597)

# KoiScript
A simple scripting language designed for extending C++ applications at runtime, specifically with video game scripting
in mind. Not to be mistaken for the stunning koilang (tsevhu): https://www.reddit.com/r/tsevhu/.


## Very WIP
# TODO::
- ...

## Datatypes
- bool
- int
- float
- text
- key
- array (of bool, int, float, text, or key)


## Meta Functions
These act on the runtime environment.
### makes stuff
- var
- arr
- fun
- lib
### does stuff
- val
- ref
- asn
- exe
- imp
### removes stuff
- rem

## Built-In Functions
These are part of the runtime environment.
### control
- if
- while
### logical
- land
- lor
- lnot
- eq
- gt
- lt
- ge
- le
### arithmetic
#### unary
- abs
- neg
- flr
- rnd
- ceil
#### multary
- add
- sub
- mul
- div
- mod
### bitwise
#### unary
- bshl
- bshr
#### multary
- bor
- bxor
- band
- bnot
### arrays
- append
- insert
### variable and function info
- size
### special
- print
