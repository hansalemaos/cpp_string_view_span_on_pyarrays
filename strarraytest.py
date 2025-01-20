from array import array
from ctypes import CDLL, c_size_t


string1 = "Hello"
string2 = "My friend"
a1 = array("b", string1.encode())
a2 = array("b", string2.encode())

a3 = array("Q", [*a1.buffer_info(), *a2.buffer_info()])
a4 = array("b", "llo".encode())

testlib = CDLL(r"C:\ProgramData\anaconda3\envs\strarraytest\mytest.dll")
add_vecs_int = testlib.add_vecs_int
add_vecs_int.argtypes = [
    c_size_t,
    c_size_t,
    c_size_t,
    c_size_t,
]
add_vecs_int.restype = None
add_vecs_int(*a3.buffer_info(), *a4.buffer_info())
