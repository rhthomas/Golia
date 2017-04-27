# Golia libraries

Custom avr-libc libraries for the Golia board; similar to the Arduino platform.

### Doxygen commenting



### Directory structure

All new libraries must adhere to the following directory structure. Each
library must also include *at least* one example program to demonstrate its
functionality.

```
golia/lbr/
├── Makefile.in
└── lib_name/
    ├── examples/
    │   ├── example_1.cpp
    │   ├── example_2.cpp
    │   ├── ...
    │   ├── example_n.cpp
    │   └── Makefile
    ├── lib_name.cpp
    └── lib_name.h
```
