import ctypes
import numpy
import glob

libfile = glob.glob('build/*/engine*.so')[0]


lib = ctypes.CDLL(libfile)



lib.hello.argtypes = (ctypes.c_char_p,)
lib.hello.restype = (ctypes.c_char_p)

def hello(name):
    pResult = lib.hello(name)
    result = pResult.decode("utf-8")
    return result


frank = "Frank"
pName = ctypes.c_char_p(frank.encode('utf-8'))

for i in range(1):
    print(hello(pName))
