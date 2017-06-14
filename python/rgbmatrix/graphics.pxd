cimport cppinc

cdef class Color:
    cdef cppinc.Color __color
    cdef cppinc.Color *__color_ptr

cdef class Font:
    cdef cppinc.Font __font

# Local Variables:
# mode: python
# End:
