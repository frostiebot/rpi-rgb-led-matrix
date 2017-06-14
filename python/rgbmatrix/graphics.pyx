# distutils: language = c++

from libcpp cimport bool
from libc.stdint cimport uint8_t, uint32_t

cimport core

cdef class Color:
  def __init__(self, uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0):
    self.__color.r = red
    self.__color.g = green
    self.__color.b = blue

  property red:
    def __get__(self): return self.__color.r
    def __set__(self, uint8_t value): self.__color.r = value

  property green:
    def __get__(self): return self.__color.g
    def __set__(self, uint8_t value): self.__color.g = value

  property blue:
    def __get__(self): return self.__color.b
    def __set__(self, uint8_t value): self.__color.b = value

cdef class Font:
  def CharacterWidth(self, uint32_t char):
    return self.__font.CharacterWidth(char)

  def LoadFont(self, file):
    if (not self.__font.LoadFont(file.encode('utf-8'))):
      raise Exception("Couldn't load font " + file)

  def DrawGlyph(self, core.Canvas c, int x, int y, Color color, Color background_color, uint32_t char):
    return self.__font.DrawGlyph(c.__getCanvas(), x, y, color.__color, background_color.__color_ptr, char)

  property height:
    def __get__(self): return self.__font.height()

  property baseline:
    def __get__(self): return self.__font.baseline()

# cdef __createOutlineFont(cppinc.Font* newFont):
#  font = Font()
#  font.__font = newFont
#  return font

def DrawText(core.Canvas c, Font f, int x, int y, Color color, Color background_color, text):
  return cppinc.DrawText(c.__getCanvas(), f.__font, x, y, color.__color, background_color.__color_ptr, text.encode('utf-8'))

def DrawLine(core.Canvas c, int x1, int y1, int x2, int y2, Color color):
  cppinc.DrawLine(c.__getCanvas(), x1, y1, x2, y2, color.__color)

def DrawCircle(core.Canvas c, int x, int y, int r, Color color):
  cppinc.DrawCircle(c.__getCanvas(), x, y, r, color.__color)

def DrawFilledCircle(core.Canvas c, int x, int y, int r, Color color):
  cppinc.DrawFilledCircle(c.__getCanvas(), x, y, r, color.__color)

def DrawRectangle(core.Canvas c, int x1, int y1, int x2, int y2, Color color):
  cppinc.DrawRectangle(c.__getCanvas(), x1, y1, x2, y2, color.__color)

def DrawFilledRectangle(core.Canvas c, int x1, int y1, int x2, int y2, Color color):
  cppinc.DrawFilledRectangle(c.__getCanvas(), x1, y1, x2, y2, color.__color)

# Local Variables:
# mode: python
# End:
