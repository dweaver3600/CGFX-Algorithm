
///////////////////////////////////////////////////////////////////////////////
// gfxrasterize.hpp
//
// Line segment rasterization.
//
// This file builds upon gfximage.hpp, so you may want to familiarize
// yourself with that header before diving into this one.
//
// Students: all of your work should go in this file, and the only files that
// you need to modify in project 1 are this file, and README.md.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>

#include "gfximage.hpp"
#include "gfxpng.hpp"

namespace gfx {

// Draw a line segment from (x0, y0) to (x1, y1) inside image target, all
// with color.
//
// target must be non-empty.
// (x0, y0) and (x1, y1) must be valid coordinates in target.
// There is no restriction on how (x0, y0) and (x1, y1) must be oriented
// relative to each other.
//
void rasterize_line_segment(hdr_image& target,
                            unsigned x0, unsigned y0,
                            unsigned x1, unsigned y1,
                            const hdr_rgb& color) {

  assert(!target.is_empty());
  assert(target.is_xy(x0, y0));
  assert(target.is_xy(x1, y1));

  unsigned temp;

// ----- BOOK 12 / 16
  if (y0 > y1){
    temp = y0;
    y0 = y1;
    y1 = temp;
  }

  // vertical case
   if (x0 == x1){
     for (int y = y0; y <= y1; y++){
       target.pixel(x0,y,color);
     }
     return;
   }

   if (x0 > x1) {
     temp = x0;
     x0 = x1;
     x1 = temp;
   }



   int y = y0;

   int dx = (int) (x1 - x0);
   int dy = (int) (y0 - y1);

   int d = (int) (dy * (int) ( x0 + 1)) +
                (dx * (int) ( y0 + 0.5)) +
                (int) (x0 * y1) -
                (int) (x1 * y0);

  for (int x = x0; x <= x1; x++){

    target.pixel(x,y,color);

    if (d < 0){
      y++;
      d += dx + dy;
    }

    else {
      d += dy;
    } // end if statement
  } // end for loop


// ------ Backup idea
  /*
  int steps;

  if (dx > dy) {steps = dx;}
  else steps = dy;

  int x = x0;
  unsigned true_x = x0;
  unsigned true_y = y0;

  for (int i = 0; i < steps; i++){
    target.pixel(x, y, color);

    true_x += dx/steps;
    x = round(true_x);

    true_y += dy/steps;
    y = round(true_y);
  }
  */

  // TODO: Rewrite the body of this function so that it actually works. After
  // you do that, delete this comment.
}

// Convenience function to create many images, each containing one rasterized
// line segment, and write them to PNG files, for the purposes of unit testing.
bool write_line_segment_cases(const std::string& filename_prefix) {
  for (unsigned end_x = 0; end_x <= 10; ++end_x) {
    for (unsigned end_y = 0; end_y <= 10; ++end_y) {
      hdr_image img(11, 11, gfx::SILVER);
      rasterize_line_segment(img, 5, 5, end_x, end_y, gfx::RED);
      std::string filename = (filename_prefix
                              + "-" + std::to_string(end_x)
                              + "-" + std::to_string(end_y)
                              + ".png");
      if (!write_png(img, filename)) {
        return false;
      }
    }
  }
  return true;
}

} // namespace gfx
