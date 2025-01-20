from array import array
from ctypes import CDLL, c_size_t

allstrings = "Hellö\nmyfriend"
allstrings_list = []
allstrings_list_size_and_address = []
for s in allstrings.splitlines():
    allstrings_list.append(array("b", s.encode()))
    allstrings_list_size_and_address.extend(allstrings_list[-1].buffer_info())

a3 = array("Q", allstrings_list_size_and_address)
a4 = array("b", "llö".encode())

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
