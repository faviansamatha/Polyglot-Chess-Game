# SWIG Example

The goal here is to use the code in `example.c` (and accompanying `example.h`) from another language using [SWIG](http://www.swig.org/). The `example.i` defines the interface for SWIG.

We can build the whole thing for Python with these commands:
```
swig -python -py3 -modern example.i
gcc -fPIC -c example.c example_wrap.c -I/usr/include/python3.6
ld -shared example.o example_wrap.o -o _example.so
```

The the included `fact.py` and `mandel.py` can use these functions:
```
python3 fact.py
python3 mandel.py
```
