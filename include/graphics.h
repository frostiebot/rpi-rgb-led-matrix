// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
// Very simple graphics library to do simple things.
//
// Might be useful to consider using Cairo instead and just have an interface
// between that and the Canvas. Well, this is a quick set of things to get
// started (and nicely self-contained).
#ifndef RPI_GRAPHICS_H
#define RPI_GRAPHICS_H

#include "canvas.h"

#include <map>
#include <stdint.h>

namespace rgb_matrix {
  struct Color {
    Color(uint8_t rr, uint8_t gg, uint8_t bb) : r(rr), g(gg), b(bb) {}
    uint8_t r;
    uint8_t g;
    uint8_t b;
  };

  // Font loading bdf files. If this ever becomes more types, just make virtual
  // base class.
  class Font {
  public:
    // Initialize font, but it is only usable after LoadFont() has been called.
    Font();
    ~Font();

    bool LoadFont(const char *path);

    // Return height of font in pixels. Returns -1 if font has not been loaded.
    int height() const { return font_height_; }

    // Return baseline. Pixels from the topline to the baseline.
    int baseline() const { return base_line_; }

    // Return width of given character, or -1 if font is not loaded or character
    // does not exist.
    int CharacterWidth(uint32_t unicode_codepoint) const;

    // Draws the unicode character at position "x","y"
    // with "color" on "background_color" (background_color can be NULL for
    // transparency.
    // The "y" position is the baseline of the font.
    // If we don't have it in the font, draws the replacement character "�" if
    // available.
    // Returns how much we advance on the screen, which is the width of the
    // character or 0 if we didn't draw any chracter.
    int DrawGlyph(Canvas *c, int x, int y, const Color &color, const Color *background_color, uint32_t unicode_codepoint) const;

    // Create a new font from this font, which represents an outline of the
    // original font.
    Font *CreateOutlineFont() const;

  private:
    Font(const Font& x);  // No copy constructor. Use references or pointer instead.

    struct Glyph;
    typedef std::map<uint32_t, Glyph*> CodepointGlyphMap;

    const Glyph *FindGlyph(uint32_t codepoint) const;

    int font_height_;
    int base_line_;
    CodepointGlyphMap glyphs_;
  };

  // -- Some utility functions.

  // Draw text, a standard NUL terminated C-string encoded in UTF-8,
  // with given "font" at "x","y" with "color".
  // "color" always needs to be set (hence it is a reference),
  // "background_color" is a pointer to optionally be NULL for transparency.
  // "kerning_offset" allows for additional spacing between characters (can be
  // negative)
  // Returns how many pixels we advanced on the screen.
  int DrawText(Canvas *c, const Font &font, int x, int y, const Color &color, const Color *background_color, const char *utf8_text, int kerning_offset = 0);

  // Draw text, a standard NUL terminated C-string encoded in UTF-8,
  // with given "font" at "x","y" with "color".
  // Draw text as above, but vertically (top down).
  // The text is a standard NUL terminated C-string encoded in UTF-8.
  // "font, "x", "y", "color" and "background_color" are same as DrawText().
  // "kerning_offset" allows for additional spacing between characters (can be
  // negative).
  // Returns font height to advance up on the screen.
  int VerticalDrawText(Canvas *c, const Font &font, int x, int y, const Color &color, const Color *background_color, const char *utf8_text, int kerning_offset = 0);

  // Draw a line from "x0", "y0" to "x1", "y1" and with "color"
  void DrawLine(Canvas *c, int x0, int y0, int x1, int y1, const Color &color);

  // Draw a circle centered at "x0", "y0", with a radius of "radius" and with "color"
  void DrawCircle(Canvas *c, int x0, int y0, int radius, const Color &color);

  // Draw a filled circle centered at "x0", "y0", with a radius of "radius" and with "color"
  void DrawFilledCircle(Canvas *c, int x0, int y0, int radius, const Color &color);

  // Draw a rectangle from "x0", "y0" to "x1", "y1" and with "color"
  void DrawRectangle(Canvas *c, int x0, int y0, int x1, int y1, const Color &color);

  // Draw a filled rectangle from "x0", "y0" to "x1", "y1" and with "color"
  void DrawFilledRectangle(Canvas *c, int x0, int y0, int x1, int y1, const Color &color);

}  // namespace rgb_matrix

#endif  // RPI_GRAPHICS_H
